# README

Source code for project PacMan for embedded systems.

## Folder structure

### Models

Contains all models that will be used for the project, under namespace `models`.
Those models represent the logic for the game itself and the interface for its actions.

The models description can be found in files.

### Drivers

Contains all drivers interface, under namespace `drivers`.

The drivers interfaces are:

* `Buzzer`: driver for interacting with BoosterPack's buzzer
* `Joystick`: driver for reading from BoosterPack's joystick
* `LCD`: driver for interacting with BoosterPack's LCD
* `button`: driver for interacting with BoosterPack's buttons

### Threads

Contains all threads for the project, under namespace `threads`.

The threads descriptions can be found in files. 

### View

Contains all resources for displaying views in the interface.
Most instances are related to the ones in "Models". 

Each view description can be found in files.
