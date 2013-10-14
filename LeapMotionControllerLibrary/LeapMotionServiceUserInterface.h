#ifndef LEAPMOTIONSERVICEUSERINTERFACE_H
#define LEAPMOTIONSERVICEUSERINTERFACE_H

#include <QObject>
#include <QVector3D>
#include <QPointF>

namespace Services
{

class LeapMotionServiceInputUserInterface
{
public :
    // REGISTER SIGNAL
    virtual void    registerToLeapMotionInputs(QObject *listener) = 0;
    virtual void    unregisterFromLeapMotionInputs(QObject *listener) = 0;
};

class LeapMotionServiceGestureUserInterface
{
    // CALLBACK METHOD
public :
    enum GestureState
    {
        StartState = 0,
        UpdateState,
        DoneState
    };


    virtual void    onCircleGestureCallBack(int gestureId,
                                            const QVector3D cicrcleCenter,
                                            const QVector3D circleNormal,
                                            const float circleRadius,
                                            const float circleTurns,
                                            const bool clockwise,
                                            const GestureState circleGestureState) = 0;
    virtual void    onScreenTapGestureCallBack(int gestureId,
                                               const QVector3D screenTapDirection,
                                               const QVector3D screenTapPosition,
                                               const GestureState screenTapGestureState = DoneState) = 0;
    virtual void    onKeyTapGestureCallBack(int gestureId,
                                            const QVector3D keyTapDirection,
                                            const QVector3D keyTapPosition,
                                            const GestureState keyTapGestureState = DoneState) = 0;
    virtual void    onSwipeGestureCallBack(int gestureId,
                                           const QVector3D swipeDirection,
                                           const QVector3D swipePosition,
                                           const QVector3D swipeStartPosition,
                                           const float swipeSpeed,
                                           const GestureState swipeGestureState) = 0;

public :
    // REGISTER SIGNAL
    virtual void    registerToLeapMotionGestures(QObject *listener) = 0;
    virtual void    unregisterFromLeapMotionGestures(QObject *listener) = 0;
};

}
Q_DECLARE_INTERFACE(Services::LeapMotionServiceInputUserInterface, "com.tepee3d.Services.LeapMotionServiceInputUserInterface/1.0")
Q_DECLARE_INTERFACE(Services::LeapMotionServiceGestureUserInterface, "com.tepee3d.Services.LeapMotionServiceGestureUserInterface/1.0")

#endif // LEAPMOTIONSERVICEUSERINTERFACE_H
