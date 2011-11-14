# Daisy2()

Create an object Daisy11

### Syntax

Daisy11 leds(wing)

### Parameters

wing: Wing where you connected Dasiy2

### Returns

leds: an object Daisy11

# begin()

Initialize pin modes

### Syntax

leds.begin()

### Parameters

Nothing

### Returns

Nothing

# ledOn()

Turn ON theLED

### Syntax

leds.ledOn(pin)

### Parameters

pin: Number of led you turn on (e.g. P1, P2, P3, etc.)

### Returns

Nothing

# ledOff()

Turn OFF the LED

### Syntax

leds.ledOff(pin)

### Parameters

pin: Number of led you turn off (e.g. P1, P2, P3, etc.)

### Returns

Nothing

# ledSwitch()

Switch the LED

### Syntax

leds.ledSwitch(pin)

### Parameters

pin: Number of led you switch (e.g. P1, P2, P3, etc.)

### Returns

Nothing

# Notes

When these module are connected to W4, the I2C port is disabled!

Led P8 are not available, they correspond to the 5V pin. (see pinout for more info).
