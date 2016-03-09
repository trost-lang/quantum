#!/usr/bin/python

from sys import platform as _platform
from os.path import realpath, exists
from os import makedirs
from shutil import copyfile
from subprocess import call


if _platform not in ["linux", "linux2", "darwin"]:
    print "Platform not supported by Trost"
    exit(-1)

print "Copying the quantum executable"
copyfile("quantum", "installer/quantum")

print "Copying the Qt libraries"
if _platform == "linux" or _platform == "linux2":
    copyfile(realpath("/usr/lib/x86_64-linux-gnu/libQt5Core.so.5"), "installer/libQt5Core.so.5")
elif _platform == "darwin":
    copyfile(realpath("/usr/local/opt/qt5/lib/QtCore.framework/Versions/5/QtCore"), "installer/QtCore")

call(["makeself", "--bzip2", "--notemp", "./installer", "./install_quantum.bz2.run", "SFX archive for Quantum", "./install.py"])
