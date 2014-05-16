QtLeapMotionLibrary
===================

Qt LeapMotion library adds inputs and gestures to a Qt application

In order to run the examples, you have to download the Leap SDK.
Then in QtLeapMotion create a Leap directory in which you'll copy the
following directories from the LeapSDK :
include
x64 -> if on 64 bits architecture
x86 -> if on 32 bits architectue

Here what you should have on a Linux 64 bits machine :

QtLeapMotionLibrary/QtLeapMotion/Leap/include/Leap.h
QtLeapMotionLibrary/QtLeapMotion/Leap/include/Leap.i
QtLeapMotionLibrary/QtLeapMotion/Leap/include/LeapMath.h
QtLeapMotionLibrary/QtLeapMotion/Leap/x64/libLeap.so

The SDK can be obtained here : https://www.leapmotion.com/developers (you have
to sign up though)

Instructions :

* You need to have Qt 5.* installed.
* Open QtLeapMotionLibrary.pro in QtCreator.
* In the project tab uncheck shadow build.
* Build.

Enjoy !

Of course you're free to use the project any way you want under either the GPL 3.0
or LGPL 2.1 license which you'll find included with the sources.


