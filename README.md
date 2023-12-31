nihwm - dynamic window manager
============================
![Screenshot](https://github.com/FaranAiki/nihwm/blob/main/example_screenshot.png)

============================

nihwm is a modified version of dwm with the philosophy that ricing/modifying
the window manager. nih stands for nihilist (not the existential nor moral)
[artistic]

TODO:
	There are many todos here, such as modifying this README,d

Sources
-----------
	dwm & patches
    some PhyOS' fork of picom
    some InstantWM config and such

	Wallpaper (modified into 1920x1080) from Pinterest: https://id.pinterest.com/pin/609252655826084493/ 

Requirements
------------
In order to build nihwm you need the Xlib header files.
And please use Linux

Installation
------------
Edit config.mk to match your local setup (nihwm is installed into
the /usr/local namespace by default, to install in other namespace, do INSTALLTO=...).

Afterwards enter the following command to build and install nihwm (if
necessary as root):

    sudo make clean install

Running nihwm
-----------
Preferably, use 
    nih
    or startx $(which nih)

Add the following line to your .xinitrc to start nihwm using startx:

    exec nihwm

In order to connect nihwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec nihwm

(This will start nihwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of nihwm is done by creating a custom config.h
and (re)compiling the source code.

Or, do it in ~/.nihwm/config
where it is possible to use Python code, Lua code, or bash (please use bash)
and system call the `nihwmctl set`
