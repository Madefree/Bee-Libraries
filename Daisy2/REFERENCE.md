# Daisy2()

Create an object Daisy2

### Syntax

Daisy2 stepper(wing, conf)

### Parameters

wing: Wing where you connected Dasiy2
conf: Dip Switch Configuration (A or B)

### Returns

stepper: an object Daisy2

# begin()

Initialize pin modes

### Syntax

stepper.begin()

### Parameters

Nothing

### Returns

Nothing

# setSpeed()

Set step speed in MicroSeconds

### Syntax

stepper.setSpeed(delay)

### Parameters

delay: microseconds interval between step

### Returns

Nothing

# direction()

Set motor direction

### Syntax

stepper.direction(dir)

### Parameters

dir: 1 for clockwise and 0 for counterclockwise

### Returns

Nothing

# invertDirection()

Invert motor direction

### Syntax

steppr.invertDirection()

### Parameters

Nothing

### Returns

Nothing

# motorEN()

Enable motor encoder

### Syntax

stepper.motorEN(en)

### Parameters

en: 1 to enable and 0 to disable encoder

### Returns

Nothing

# step()

Perform steps

### Syntax

stepper.step(nstep)

### Parameters

nstep: number of steps to be performed

### Returns

Nothing

# Notes

You can connect up to 2 stepper motor to W3 (Configuration 'A' and 'B') and one stepper motor to W4 (configuration 'A').
