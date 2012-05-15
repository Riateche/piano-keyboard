piano-keyboard
==============

Program for using midi keyboard as computer keyboard.

Dependencies
------------

When using Ubuntu, the following packages are required to build the source:

    sudo apt-get install libqt4-dev libportmidi-dev libx11-dev x11proto-core-dev libxtst-dev
    
It should be possible to compile the source on another Linux distributions.

Compiling
---------

Compiling and running of program is quite simple:

    qmake && make && ./piano-keyboard
    
Using
-----

The program will send key events when you're pressing keys or combinations mentioned in `layout.ini` file.
You can find human-readable representation of the layout in `layout.pdf` file. Note that you should hold
`Shift` key to input upper case letters and symbols, just as on usual keyboard.

Configuring
-----------

### Choosing MIDI device

You can adjust the name of MIDI device being used by changing `#define MIDI_DEVICE_NAME` in 
[main.cpp](https://github.com/Riateche/piano-keyboard/blob/master/main.cpp#L8). 
It should be a string contained in your device name. The list of available MIDI devices with their names
appear in the program output on startup.

### Commit delay

Commit delay is the biggest time interval that can be passed between two notes for they to be considered as
a single chord. You can change the commit delay in 
[Midi_parser.h](https://github.com/Riateche/piano-keyboard/blob/master/Midi_parser.h#L28) file.

### Layout

Layout can be changed in `layout.ini` file. 
See [the comment in this file](https://github.com/Riateche/piano-keyboard/blob/master/layout.ini#L1-19) 
for more information.
