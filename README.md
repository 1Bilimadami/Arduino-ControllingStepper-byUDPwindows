# Arduino-ControllingStepper-byUDPwindows
This is pre software so it is not including advanced improvments of final version.

Readme:

Receiving data order request from client-user is similar to earlier code but this new software converts them to integer for finding step size.
First char of data order request is type of movement, rest of data is size of steps of stepper motor.

Hardware:
Arduino + ethernet module /feather
stepper motor + driver
proximity sensor
