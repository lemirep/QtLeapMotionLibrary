/****************************************************************************
**
** Copyright (C) Paul Lemire
** Contact: paul.lemire@epitech.eu
**
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "QtLeapMotionListener.h"
#include "QtLeapHandsHandlerInterface.h"
#include "QtLeapGestureHandlerInterface.h"
#include "QtLeapMouseHandlerInterface.h"
#include "QtLeapTouchHandlerInterface.h"
#include "QtLeapGestureListenerInterface.h"
#include "QtLeapHandsListenerInterface.h"
#include "QtLeapFingersListenerInterface.h"
#include <QDebug>

namespace QtLeapMotion
{

QtLeapMotionListener::QtLeapMotionListener()
    : QObject(),
      Leap::Listener(),
      touchHandler(Q_NULLPTR),
      mouseHandler(Q_NULLPTR),
      handHandler(Q_NULLPTR)
{
}

QtLeapMotionListener::~QtLeapMotionListener()
{
    this->mouseListeners.clear();
    this->touchListeners.clear();
    this->handListeners.clear();
    this->gestureListeners.clear();

    delete this->touchHandler;
    delete this->mouseHandler;
    delete this->handHandler;

    for (int i = this->gestureHandlers.count(); i > 0; i--)
        delete this->gestureHandlers.takeLast();
}

//void QtLeapMotionListener::swipeGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
//{
//    Leap::SwipeGesture swipe = gesture;
//    QVector3D swipeDirection(swipe.direction().x, swipe.direction().y, swipe.direction().z);
//    QVector3D swipeGlobalPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), swipe.position());
//    QVector3D swipeStartPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), swipe.startPosition());

//    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
////    foreach (QObject *listener, this->gesturesListeners)
////        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
////                onSwipeGestureCallBack(swipe.id(),
////                                       swipeDirection,
////                                       swipeGlobalPos,
////                                       swipeStartPos,
////                                       swipe.speed(),
////                                       state);
//}

//void QtLeapMotionListener::circleGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
//{
//    Leap::CircleGesture circle = gesture;
//    QVector3D circleCenter = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), circle.center());
//    QVector3D circleNormal = QVector3D(circle.normal().x, circle.normal().y, circle.normal().z);


//    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
//    foreach (QObject *listener, this->gesturesListeners)
//    {
//        //        qDebug() << "Circle";
//        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
//                onCircleGestureCallBack(circle.id(),
//                                        circleCenter,
//                                        circleNormal,
//                                        circle.radius(),
//                                        circle.progress(),
//                                        circle.pointable().direction().angleTo(circle.normal()) <= M_PI / 2,
//                                        state);
//    }
//}

//void QtLeapMotionListener::keyTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
//{
//    Leap::KeyTapGesture keyTap = gesture;
//    QVector3D tapPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), keyTap.pointable().stabilizedTipPosition());
//    QVector3D tapDirection(keyTap.direction().x, keyTap.direction().y, keyTap.direction().z);
//    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
//    foreach (QObject *listener, this->gesturesListeners)
//        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
//                onKeyTapGestureCallBack(keyTap.id(), tapDirection, tapPos);
//}

//void QtLeapMotionListener::screenTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
//{
//    qDebug() << "ScreenTap Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
//    Leap::ScreenTapGesture screenTap = gesture;
//    QVector3D tapDirection = QVector3D(screenTap.direction().x, screenTap.direction().y, screenTap.direction().z);
//    QVector3D screenTap3DPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), screenTap.pointable().stabilizedTipPosition());
//    //    QCursor ::setPos(globalPointerPos.toPoint());
//    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
//    foreach (QObject *listener, this->gesturesListeners)
//        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
//                onScreenTapGestureCallBack(screenTap.id(), tapDirection, screenTap3DPos);
//}

//void QtLeapMotionListener::handleHandEvents(const Leap::Frame &frame)
//{
//    if (frame.isValid())
//    {
//        QList<Services::LeapMotionServiceGestureUserInterface::HandObject> handsList;
//        for (int i = 0; i < frame.hands().count(); i++)
//        {
//            Leap::Hand hand = frame.hands()[i];
//            Services::LeapMotionServiceGestureUserInterface::HandObject handObj;
//            handObj.id = hand.id();
//            handObj.direction = QVector3D(hand.direction().x, hand.direction().y, hand.direction().z);
//            handObj.pitch = hand.direction().pitch();
//            handObj.yaw = hand.direction().yaw();
//            handObj.roll = hand.palmNormal().roll();
//            handsList.append(handObj);
//        }
//        foreach (QObject *listener, this->gesturesListeners)
//        {
//            Services::LeapMotionServiceGestureUserInterface *serviceListener =
//                    qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener);
//            if (serviceListener != NULL)
//                serviceListener->onHandCallBack(handsList);
//        }
//    }
//}



void QtLeapMotionListener::onInit(const Leap::Controller &controller)
{
    qDebug() << Q_FUNC_INFO;
    if (this->mouseHandler)
        this->mouseHandler->onInit(controller);
    if (this->touchHandler)
        this->touchHandler->onInit(controller);
    if (this->handHandler)
        this->handHandler->onInit(controller);
    foreach (QtLeapGestureHandlerInterface *handler, this->gestureHandlers)
        handler->onInit(controller);
}

void QtLeapMotionListener::onConnect(const Leap::Controller &)
{
    qDebug() << Q_FUNC_INFO;
}

void QtLeapMotionListener::onDisconnect(const Leap::Controller &)
{
    qDebug() << Q_FUNC_INFO;
}

void QtLeapMotionListener::onExit(const Leap::Controller &)
{
    qDebug() << Q_FUNC_INFO;
}

void QtLeapMotionListener::onFrame(const Leap::Controller &controller)
{
    Leap::Frame frame = controller.frame();

    if (frame.isValid())
    {
        // RETRIEVE FINGER INFORMATIONS AND CONVERT THEM TO MOUSE AND TOUCH EVENTS

        // ANALYSE FRAME GESTURES AND CALL TARGETS THAT ARE QTQUICK PLUGINS
        // CREATE QTQUICK PLUGINS LeapGestureArea (FOR GESTURES)
        // FOR EACH GESTURE IN A FRAME, CHECK IF QTQUICK PLUGIN HAS IMPLEMENTED GESTURE TYPE AND IF GESTURE OCCURED WITHIN THE QTQUICK PLUGIN AREA
        // IF SO TRIGGER CALLBACK IN QTQUICK PLUGIN
        ///////// MOUSE //////////////////////////
        if (this->mouseHandler)
            this->mouseHandler->onFrame(frame);
        ////////// TOUCH /////////////////////////
        if (this->touchHandler)
            this->touchHandler->onFrame(frame);
        /////// LEAP MOTION BUILT-IN GESTURES ////////
        // SCREEN TAP
        // SWIPE
        // CIRCLE
        // KEY TAP
        /////// CUSTOM GESTURES DETECTION //////////
        // PINCH ...
        foreach (QtLeapGestureHandlerInterface *gestureHandler, this->gestureHandlers)
            gestureHandler->onFrame(frame);

        /////// HANDS //////////////////////////////
        if (this->handHandler)
            this->handHandler->onFrame(frame);
    }
}

void QtLeapMotionListener::onFocusGained(const Leap::Controller &)
{
    qDebug() << Q_FUNC_INFO;
}

void QtLeapMotionListener::onFocusLost(const Leap::Controller &)
{
    qDebug() << Q_FUNC_INFO;
}

void QtLeapMotionListener::registerMouseListener(QObject *motionListener)
{
    if ((qobject_cast<QQuickItem *>(motionListener) != Q_NULLPTR ||
         qobject_cast<QWindow*>(motionListener) != Q_NULLPTR) &&
            !this->mouseListeners.contains(motionListener))
    {
        this->mouseListeners << motionListener;
        qDebug() << Q_FUNC_INFO;
        if (this->mouseHandler)
            this->mouseHandler->setMotionListeners(this->mouseListeners);
    }
}

void QtLeapMotionListener::registerTouchListener(QObject *motionListener)
{
    if ((qobject_cast<QQuickItem *>(motionListener) != Q_NULLPTR ||
         qobject_cast<QWindow*>(motionListener) != Q_NULLPTR) &&
            !this->touchListeners.contains(motionListener))
    {
        qDebug() << Q_FUNC_INFO;
        this->touchListeners << motionListener;
        if (this->touchHandler)
            this->touchHandler->setMotionListeners(this->touchListeners);
    }
}

void QtLeapMotionListener::registerGestureListener(QtLeapGestureListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && !this->gestureListeners.contains(motionListener))
    {
        qDebug() << Q_FUNC_INFO << motionListener;
        this->gestureListeners << motionListener;
        foreach (QtLeapGestureHandlerInterface *handler, this->gestureHandlers) {
            qDebug() << Q_FUNC_INFO << " >>";
            handler->setMotionListeners(this->gestureListeners);
        }
    }
}

void QtLeapMotionListener::registerHandListener(QtLeapHandsListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && !this->handListeners.contains(motionListener))
    {
        qDebug() << Q_FUNC_INFO;
        this->handListeners << motionListener;
        if (this->handHandler)
            this->handHandler->setMotionListeners(this->handListeners);
    }
}

void QtLeapMotionListener::registerFingerListener(QtLeapFingersListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && !this->fingerListeners.contains(motionListener))
    {
        qDebug() << Q_FUNC_INFO;
        this->fingerListeners << motionListener;
    }
}

void QtLeapMotionListener::unregisterMouseListener(QObject *motionListener)
{
    if (motionListener != Q_NULLPTR && this->mouseListeners.contains(motionListener))
    {
        this->mouseListeners.removeAll(motionListener);
        if (this->mouseHandler)
            this->mouseHandler->setMotionListeners(this->mouseListeners);
    }
}

void QtLeapMotionListener::unregisterTouchListener(QObject *motionListener)
{
    if (motionListener != Q_NULLPTR && this->touchListeners.contains(motionListener))
    {
        this->touchListeners.removeAll(motionListener);
        if (this->touchHandler)
            this->touchHandler->setMotionListeners(this->touchListeners);
    }
}

void QtLeapMotionListener::unregisterGestureListener(QtLeapGestureListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && this->gestureListeners.contains(motionListener))
    {
        this->gestureListeners.removeAll(motionListener);
        foreach (QtLeapGestureHandlerInterface *handler, this->gestureHandlers)
            handler->setMotionListeners(this->gestureListeners);
    }
}

void QtLeapMotionListener::unregisterHandListener(QtLeapHandsListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && this->handListeners.contains(motionListener))
    {
        this->handListeners.removeAll(motionListener);
        if (this->handHandler)
            this->handHandler->setMotionListeners(this->handListeners);
    }
}

void QtLeapMotionListener::unregisterFingerListener(QtLeapFingersListenerInterface *motionListener)
{
    if (motionListener != Q_NULLPTR && this->fingerListeners.contains(motionListener))
        this->fingerListeners.removeAll(motionListener);
}

void QtLeapMotionListener::setTouchHandler(QtLeapTouchHandlerInterface *motionHandler)
{
    this->touchHandler = motionHandler;
}

void QtLeapMotionListener::setMouseHandler(QtLeapMouseHandlerInterface *motionHandler)
{
    this->mouseHandler = motionHandler;
}

void QtLeapMotionListener::addGestureHandler(QtLeapGestureHandlerInterface *motionHandler)
{
    if (motionHandler != Q_NULLPTR)
        this->gestureHandlers << motionHandler;
}

void QtLeapMotionListener::setHandHandler(QtLeapHandsHandlerInterface *motionHandler)
{
    this->handHandler = motionHandler;
}

} //QtLeapMotion

