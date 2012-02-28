#include "Daisy23.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>


#include "mpr121.h"
#include "types.h"
#include "defs.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define ADDR 0xB4

Daisy23::Daisy23(int irq_pin) {
	pinMode(irq_pin,INPUT);
	irq_pin_ = irq_pin;

	
}

void Daisy23::begin() {
	DDRC |= 0b00010011;
	PORTC = 0b00110000;  // Pull-ups on I2C Bus
	i2cInit();
	mpr_config();
	mpr_lcd_init();	
	delay(100);
	mpr_config();
}

// I2C Communication


uint8_t Daisy23::mpr_read(uint8_t address)
{
	byte data;
	
	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(0xB4);	// write 0xB4
	i2cWaitForComplete();
	
	i2cSendByte(address);	// write register address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(0xB5);	// write 0xB5
	i2cWaitForComplete();
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();
	
	data = i2cGetReceivedByte();	// Get MSB result
	i2cWaitForComplete();
	i2cSendStop();
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	return data;
}

void Daisy23::mpr_send(unsigned char address, unsigned char data)
{
	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ADDR);// write 0xB4
	i2cWaitForComplete();
	
	i2cSendByte(address);	// write register address
	i2cWaitForComplete();
	
	i2cSendByte(data);
	i2cWaitForComplete();
	
	i2cSendStop();
}

//MPR121 Function

void Daisy23::mpr_config(void)
{
	// Section A
	// This group controls filtering when data is > baseline.
	mpr_send(MHD_R, 0x01);
	mpr_send(NHD_R, 0x01);
	mpr_send(NCL_R, 0x00);
	mpr_send(FDL_R, 0x00);
	
	// Section B
	// This group controls filtering when data is < baseline.
	mpr_send(MHD_F, 0x01);
	mpr_send(NHD_F, 0x01);
	mpr_send(NCL_F, 0xFF);
	mpr_send(FDL_F, 0x02);
	
	// Section C
	// This group sets touch and release thresholds for each electrode
	mpr_send(ELE0_T, TOU_THRESH);
	mpr_send(ELE0_R, REL_THRESH);
	mpr_send(ELE1_T, TOU_THRESH);
	mpr_send(ELE1_R, REL_THRESH);
	mpr_send(ELE2_T, TOU_THRESH);
	mpr_send(ELE2_R, REL_THRESH);
	mpr_send(ELE3_T, TOU_THRESH);
	mpr_send(ELE3_R, REL_THRESH);
	mpr_send(ELE4_T, TOU_THRESH);
	mpr_send(ELE4_R, REL_THRESH);  
	// Section D
	// Set the Filter Configuration
	// Set ESI2
	mpr_send(FIL_CFG, 0x04);
	
	// Section E
	// Electrode Configuration
	// Enable 6 Electrodes and set to run mode
	// Set ELE_CFG to 0x00 to return to standby mode
	mpr_send(ELE_CFG, 0x05);	// Enables all 12 Electrodes
	mpr_send(GPIO_EN, 0xFE);
	mpr_send(GPIO_DIR, 0xFE);
	mpr_send(GPIO_CTRL0, 0x00);
	mpr_send(GPIO_CTRL1, 0x00);
	
}

void Daisy23::mpr_gpio_set(unsigned char data) {
	mpr_send(GPIO_SET,data);
}

void Daisy23::mpr_gpio_clear(unsigned char data) {
	mpr_send(GPIO_CLEAR,data);
}

void Daisy23::mpr_gpio_toggle(unsigned char data) {
	mpr_send(GPIO_TOGGLE,data);
}

//Low Level LCD Function

void Daisy23::mpr_lcd_send(unsigned char value,int mode) {
	if(mode==0)
		mpr_lcd_rsLow();
	else if(mode==1)
		mpr_lcd_rsHigh();
	mpr_lcd_write(value>>4);
	mpr_lcd_write(value);  
}

void Daisy23::mpr_lcd_enPulse(void) {
	mpr_lcd_enLow();
	mpr_lcd_enHigh();
	//mpr_lcd_enLow();
	//delayMicroseconds(100);
}

void Daisy23::mpr_lcd_write(unsigned char data) {
	unsigned char valueLow = 0x00;
	unsigned char valueHigh = 0x00;
	if(data & 0x01)
		valueHigh |= 0x10;
	else
		valueLow |= 0x10;
	if(data & 0x02)
		valueHigh |= 0x20;
	else
		valueLow |= 0x20;
	if(data & 0x04)
		valueHigh |= 0x40;
	else
		valueLow |= 0x40;
	if(data & 0x08)
		valueHigh |= 0x80;
	else
		valueLow |= 0x80;
	mpr_gpio_set(valueHigh);
	mpr_gpio_clear(valueLow);
	mpr_lcd_enPulse();
}

void Daisy23::mpr_lcd_rsHigh(void) {
	mpr_gpio_set(0x04);
}

void Daisy23::mpr_lcd_rsLow(void) {
	mpr_gpio_clear(0x04);
}

void Daisy23::mpr_lcd_enHigh(void) {
	mpr_gpio_set(0x08);
}

void Daisy23::mpr_lcd_enLow(void) {
	mpr_gpio_clear(0x08);
}

void Daisy23::lightOn(void) {
	mpr_gpio_set(0x02);
}

void Daisy23::lightOff(void) {
	mpr_gpio_clear(0x02);
}

void Daisy23::setLight(int value) {
	mpr_send(0x81,value<<4);
}

//High Level LCD Function

void Daisy23::print(char *format, ...) {
	int i;
	
	va_list argptr;
	char buffer[1024];
	
	va_start(argptr,format);
	vsprintf(buffer,format,argptr);
	va_end(argptr);
	
	for (i=0;i<strlen(buffer);i++) {
		mpr_lcd_send(buffer[i],1);
	}
}

void Daisy23::printFloat(double number, uint8_t digits) 
{ 
	// Handle negative numbers
	if (number < 0.0)
	{
		print("-");
		number = -number;
	}
	
	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
		rounding /= 10.0;
	
	number += rounding;
	
	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	print("%d",int_part);
	
	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
		print("."); 
	
	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		int toPrint = int(remainder);
		print("%d",toPrint);
		remainder -= toPrint; 
	} 
}

void Daisy23::mpr_lcd_init(void) {
	mpr_lcd_rsLow();
	mpr_lcd_enLow();
	mpr_lcd_write(0x03);
	delay(4);
	mpr_lcd_write(0x03);
	delay(4);
	mpr_lcd_write(0x03);
	delay(4);
	mpr_lcd_write(0x02);
	delayMicroseconds(100);
	mpr_lcd_send(0x20 | 0x08  ,0);
	mpr_lcd_send(0x08 | 0x04 ,0);
	clear();
	mpr_lcd_send(0x04 | 0x02 ,0);
}

void Daisy23::clear(void) {
	mpr_lcd_send(0x01,0);
	delay(2);
}

void Daisy23::setCursor(int col,int row) {
	mpr_lcd_send(0x80+row*0x40+col ,0);
} 

int Daisy23::readButton(void) {
	int count=0;
	byte value = (mpr_read(0x01)<<8) | mpr_read(0x00);
	for(int i=0; i<6; i++) {
		if(value& (1<<i)) 
			count++;
	}
	if(count != 0 && count != 2) {
		if(value & (1<<0))
			return 0;
		else if(value & (1<<1))
			return 1;
		else if(value & (1<<2))
			return 2;
		else if(value & (1<<3))
			return 3;
		else if(value & (1<<4))
			return 4;
	} else 
		return -1;
}

/*********************
 ****I2C Functions****
 *********************/

void Daisy23::i2cInit(void)
{
	// set i2c bit rate to 40KHz
	i2cSetBitrate(100);
	// enable TWI (two-wire interface)
	sbi(TWCR, TWEN);	// Enable TWI
}

void Daisy23::i2cSetBitrate(unsigned short bitrateKHz)
{
	unsigned char bitrate_div;
	// set i2c bitrate
	// SCL freq = F_CPU/(16+2*TWBR))
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	
	//calculate bitrate division	
	bitrate_div = ((F_CPU/4000l)/bitrateKHz);
	if(bitrate_div >= 16)
		bitrate_div = (bitrate_div-16)/2;
	outb(TWBR, bitrate_div);
}

void Daisy23::i2cSendStart(void)
{
	WRITE_sda();
	// send start condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

void Daisy23::i2cSendStop(void)
{
	// transmit stop condition
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void Daisy23::i2cWaitForComplete(void)
{
	int i = 0;		//time out variable
	
	// wait for i2c interface to complete operation
    while ((!(TWCR & (1<<TWINT))) && (i < 90))
		i++;
}

void Daisy23::i2cSendByte(unsigned char data)
{
	delay_ms(1);
	//printf("sending 0x%x\n", data);
	WRITE_sda();
	// save data to the TWDR
	TWDR = data;
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);
}

void Daisy23::i2cReceiveByte(unsigned char ackFlag)
{
	// begin receive over i2c
	if( ackFlag )
	{
		// ackFlag = TRUE: ACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT)|BV(TWEA));
	}
	else
	{
		// ackFlag = FALSE: NACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT));
	}
}

unsigned char Daisy23::i2cGetReceivedByte(void)
{
	// retieve received data byte from i2c TWDR
	return( inb(TWDR) );
}

unsigned char Daisy23::i2cGetStatus(void)
{
	// retieve current i2c status from i2c TWSR
	return( inb(TWSR) );
}

void Daisy23::delay_ms(uint16_t x)
{
	uint8_t y, z;
	for ( ; x > 0 ; x--){
		for ( y = 0 ; y < 90 ; y++){
			for ( z = 0 ; z < 6 ; z++){
				asm volatile ("nop");
			}
		}
	}
}


