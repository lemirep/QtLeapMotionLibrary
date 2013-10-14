QtLeapMotionLibrary
===================

Qt LeapMotion library adding inputs and gestures to a Qt application

In order to run this example, you have to download the Leap SDK for your
platorm and copy the 'include' folder in the Leap subdirectory of the
LeapMotionControllerLibrary.

The redistributable libraries are bundled in but to respect the Leap SDK
agreement licence, I cannot provide the headers.

The SDK can be obtained here : https://www.leapmotion.com/developers (you have
to sign up)

It should give you :

QtLeapMotionLibrary/LeapMotionControllerLibrary/Leap/include/Leap.h
QtLeapMotionLibrary/LeapMotionControllerLibrary/Leap/include/Leap.i
QtLeapMotionLibrary/LeapMotionControllerLibrary/Leap/include/LeapMath.h

To run the project you need to have Qt 5.* installed.

To build the project open it in QtCreator.
In the project tab uncheck shadow build.
Add an extra make step with install as the argument

Build the project and enjoy !
