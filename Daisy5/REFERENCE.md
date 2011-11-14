# Daisy5()

Create an object Daisy5.

### Syntax

Daisy5 button(wing)

### Parameters

wing: Wing where you connected Dasiy5

### Returns

button: an object Daisy5

# begin()

Initialize pin modes

### Syntax

button.begin()

### Parameters

Nothing

### Returns

Nothing

# readButton()

return the state of button

### Syntax

button.readButton(pin)

### Parameters

pin: Number of button you read (e.g. P1, P2, P3, etc.)

### Returns

int (High or Low)

# Notes

When these module are connected to W4, the I2C port is disabled!

Button P8 are not available, they correspond to the 5V pin. (see pinout for more info).
