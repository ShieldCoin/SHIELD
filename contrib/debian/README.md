
Debian
====================
This directory contains files used to package shieldd/shield-qt
for Debian-based Linux systems. If you compile shieldd/shield-qt yourself, there are some useful files here.

## shield: URI support ##


shield-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install shield-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your shield-qt binary to `/usr/bin`
and the `../../share/pixmaps/shield128.png` to `/usr/share/pixmaps`

shield-qt.protocol (KDE)

