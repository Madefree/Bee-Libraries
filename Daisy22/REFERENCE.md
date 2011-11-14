# Daisy22()

Create a Daisy22 object.

### Syntax

Daisy22 expander(address)

### Parameters

address: I2C address

### Returns

expander: an object Daisy22

# begin()

Initialize I2C bus

### Syntax

expander.begin()

### Parameters

Nothing

### Returns

Nothing

# digiatlWrite()

Write a HIGH or a LOW value to a pin.

### Syntax

expander.digitalWrite(pin, value)

### Parameters

pin: Number of pin you write (e.g. P0, P1, P2, etc.)

value: HIGH or LOW

### Returns

Nothing

# digitalRead()

Reads the value from a specified digital pin, either HIGH or LOW

### Syntax

expander.digitalRead(pin)

### Parameters

pin: Number of pin you read (e.g. P0, P1, P2, etc.)

### Returns

int (HIGH or LOW)

# Notes

digitalWrite() accepts as a parameter 1Byte to write the all P0-P7 pins (e.g. *expander.digitalWrite(0xFF)*)

digitalRead() returns a byte corresponding to the state of all pins (e.g. *int value = expander.digitalRead()*)
