# Daisy4()

Create a Daisy4 object.

### Syntax

Daisy4 relay(wing, dip)

### Parameters

wing: Wing where you connected Daisy4

dip: Number of DIP ON (e.g. DIP1, DIP2, etc.)

### Returns

relay: an object Daisy4

# begin()

Initialize pin modes.

### Syntax

relay.begin()

### Parameters

Nothing

### Returns

Nothing

# relayOn()

Switch relay On

### Syntax

relay.relayOn()

### Parameters

Nothing

### Returns

Nothing

# relayOff()

Switch relay Off

### Syntax

relay.relayOff()

### Parameters

Nothing

### Returns

Nothing

# readState()

return the state of relay

### Syntax

relay.readState()

### Parameters

Nothing

### Returns

int (HIGH or LOW)

# Notes

DIP8 are not available, it corrensponds to 5V pin! (see pinout for more info).

Wing W2 accept just DIP4 to DIP7.

A total of 18 relays can be used simultaneously.
