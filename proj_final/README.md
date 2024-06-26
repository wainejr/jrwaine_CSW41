# README

Source code for project PacMan for embedded systems.

## Folder structure

It's important to notice that documentation and comments are mostly in `.h` files

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

### Constant values and parameters

Most of constant values and parameters can be found in the files `models/consts.h` and `view/globals.h`.
There are some defines for threads in `threads/` folder as well.

## Format files

Install `clang-format` and run 

```bash
find src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
```

make sure you use a terminal that supports the Linux commands above