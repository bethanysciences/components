# Python

Remove downloaded restrictions  
```$ sudo spctl --master-disable```  

Privacy and "Anywhere" is now added to the list  

Back to protected mode  
```$ sudo spctl --master-enable```


/Library/Frameworks/Python.framework/Versions/3.6/bin/pip3.6 install thonny
/Library/Frameworks/Python.framework/Versions/3.6/bin/python3.6 -m thonny

http://thonny.org/
/Library/Frameworks/Python.framework/Versions/3.5/bin/pip3.5 install thonny
/Library/Frameworks/Python.framework/Versions/3.5/bin/python3.5 -m thonny


Updating Tcl/Tk (optional). Thonny relies on something called Tcl/Tk. Your Python installation may use too old Tcl/Tk version, which means you may see Thonny crashing too often or doing weird things. (Python's IDLE has similar problems, see https://www.python.org/download/mac/tcltk). The solution is to install newer version. Go to http://www.activestate.com/activetcl/downloads and download and install the latest 8.5 version of ActiveTcl. (Most likely your Python is linked with Tk 8.5. If IDLE-s about dialog says it uses 8.6, then install latest ActiveTcl 8.6)
https://www.activestate.com/activetcl/downloads
http://docs.activestate.com/activetcl/8.5/at.install.html
ActiveTcl executables (wish, tclsh and tkcon) are installed in /usr/local/bin. If this directory is not in the user's PATH environment variable, it can be added manually to the .profile or .bash_ profile file in the user's home directory. For example:

    PATH=/usr/local/bin:$PATH
    export PATH



LiClipse http://www.liclipse.com/
Requirement: Eclipse 4.6

Note that to be installed, LiClipse requires Eclipse 4.6 (Neon) onwards.

Requirement: Java 8

The installed Eclipse MUST be running with a Java 8 VM, otherwise LiClipse may not show as being installed or you'll have errors such as:

java.lang.UnsupportedClassVersionError: SomeClass :
Unsupported major.minor version 51.0
at java.lang.ClassLoader.defineClass1(Native Method)
at java.lang.ClassLoader.defineClassCond(Unknown Source)

-- Note that the native LiClipse installers ship by default with a VM, so, the installed java version shouldn't be a concern.
