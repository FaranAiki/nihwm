nihwm - nihilist window manager 
============================
![Screenshot](https://github.com/FaranAiki/nihwm/blob/main/example_screenshot.png)

============================

nihwm is a modified version of dwm with the philosophy that ricing/modifying
the window manager is useless. nih stands for nihilist (not the existential nor moral)
but [artistic]

TODO:
*   Modify this README.md
*   Modify nihwm.1
*   Fix problems in TODO comments

Sources
*	dwm & patches
*   some PhyOS' fork of picom
*   some InstantWM config and such

*	Default Wallpaper (modified into 1920x1080) from Pinterest: https://id.pinterest.com/pin/609252655826084493/ 


Another name
------------
If you, for some reason, do not like the name nihwm, then this window manager can be
called lazywm, because this window manager is the epitome of laziness and dynamic

Documentation
------------
It is not rtfm but rtfc lol

Requirements
------------
In order to build nihwm you need the Xlib header files.
And, please use Linux or Arch/Artix :3

Installation
------------
Edit config.mk to match your local setup (nihwm is installed into
the /usr/local namespace by default, to install in other namespace, do INSTALLTO=...).

Afterwards enter the following command to build and install nihwm (if
necessary as root):

    sudo make clean install

Floating
------------
nihwm will always stack floating from left to right, unless
the window type is splash, notification, or dialog

Running nihwm
-----------
Preferably, use 
    
    nih
    
or 
    
    startx $(which nih)

Add the following line to your .xinitrc to start nihwm using startx:

    exec nihwm

In order to connect nihwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec nihwm

(This will start nihwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of nihwm is done by creating a custom config.h
and (re)compiling the source code (preferred).

Or, do it in ~/.nihwm/config
where it is possible to use Python code, Lua code, or bash (please use bash)
and system call the `nihwmctl set`
