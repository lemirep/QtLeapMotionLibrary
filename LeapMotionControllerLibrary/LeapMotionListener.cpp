/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
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

#include "LeapMotionListener.h"
#include <QDebug>



LeapMotionListener::LeapMotionListener() : QObject(), Leap::Listener()
{
    this->savedMousePointableId = -1;
    this->touchPoints = QList<QTouchEvent::TouchPoint>();
    this->mousePressed = false;
    this->previousPos = QPoint();
    this->primaryScreen = QGuiApplication::primaryScreen();
    this->inputListeners = QList<QObject *>();
    this->gesturesListeners = QList<QObject *>();
    this->gestureStateMatcher[Leap::Gesture::STATE_START] = Services::LeapMotionServiceGestureUserInterface::StartState;
    this->gestureStateMatcher[Leap::Gesture::STATE_UPDATE] = Services::LeapMotionServiceGestureUserInterface::UpdateState;
    this->gestureStateMatcher[Leap::Gesture::STATE_STOP] = Services::LeapMotionServiceGestureUserInterface::DoneState;
}

LeapMotionListener::~LeapMotionListener()
{
    this->inputListeners.clear();
    this->gesturesListeners.clear();
}

void LeapMotionListener::swipeGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::SwipeGesture swipe = gesture;
    QVector3D swipeDirection(swipe.direction().x, swipe.direction().y, swipe.direction().z);
    QVector3D swipeGlobalPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), swipe.position());
    QVector3D swipeStartPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), swipe.startPosition());
    Services::LeapMotionServiceGestureUserInterface::GestureState state = this->gestureStateMatcher[gesture.state()];

    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
    foreach (QObject *listener, this->gesturesListeners)
        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
                onSwipeGestureCallBack(swipe.id(),
                                       swipeDirection,
                                       swipeGlobalPos,
                                       swipeStartPos,
                                       swipe.speed(),
                                       state);
}

void LeapMotionListener::circleGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::CircleGesture circle = gesture;
    QVector3D circleCenter = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), circle.center());
    QVector3D circleNormal = QVector3D(circle.normal().x, circle.normal().y, circle.normal().z);
    Services::LeapMotionServiceGestureUserInterface::GestureState state = this->gestureStateMatcher[gesture.state()];


    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
    foreach (QObject *listener, this->gesturesListeners)
    {
//        qDebug() << "Circle";
        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
                onCircleGestureCallBack(circle.id(),
                                        circleCenter,
                                        circleNormal,
                                        circle.radius(),
                                        circle.progress(),
                                        circle.pointable().direction().angleTo(circle.normal()) <= M_PI / 2,
                                        state);
    }
}

void LeapMotionListener::keyTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::KeyTapGesture keyTap = gesture;
    QVector3D tapPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), keyTap.pointable().stabilizedTipPosition());
    QVector3D tapDirection(keyTap.direction().x, keyTap.direction().y, keyTap.direction().z);
    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
    foreach (QObject *listener, this->gesturesListeners)
        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
                onKeyTapGestureCallBack(keyTap.id(), tapDirection, tapPos);
}

void LeapMotionListener::screenTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    qDebug() << "ScreenTap Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    Leap::ScreenTapGesture screenTap = gesture;
    QVector3D tapDirection = QVector3D(screenTap.direction().x, screenTap.direction().y, screenTap.direction().z);
    QVector3D screenTap3DPos = this->convertVectorToNormalizedScreenVector(frame.interactionBox(), screenTap.pointable().stabilizedTipPosition());
    //    QCursor ::setPos(globalPointerPos.toPoint());
    // IF SWIPE IS CONTAINED IN THE LISTENER AREA, THIS IS CHECKED BY LeapGestureArea IF THIS IS THE LISTENER
    foreach (QObject *listener, this->gesturesListeners)
        qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(listener)->
                onScreenTapGestureCallBack(screenTap.id(), tapDirection, screenTap3DPos);
}

void LeapMotionListener::handleMouseEvents(const Leap::Frame &frame)
{
    /////// MOUSE EVENTS /////////
    // MOUSE BUTTON PRESSED
    // MOUSE BUTTON RELEASED
    // MOUSE MOVE

    if (this->inputListeners.empty())
        return ;


    Leap::Pointable pointer = frame.pointable(this->savedMousePointableId);
    if (!pointer.isValid())
    {
        pointer = frame.pointables().frontmost();
        this->savedMousePointableId = pointer.id();
    }

    bool forceRelease = (frame.pointables().count() == 0 && this->mousePressed);
    QMouseEvent::Type frameMouseEvent = QMouseEvent::None;
    QPointF globalPointerPos = this->convertPointablePosToScreenPos(frame.interactionBox(), pointer);
    Qt::MouseButton button = Qt::NoButton;
    Qt::MouseButtons buttons = Qt::NoButton;

    // FINGER TOUCHING AND NO PREVIOUS PRESS -> SETTING BUTTON PRESS
    if (pointer.touchDistance() <= 0 &&
            pointer.touchZone() == Leap::Pointable::ZONE_TOUCHING &&
            !this->mousePressed)
    {
        this->mousePressed = true;
        frameMouseEvent = QMouseEvent::MouseButtonPress;
        button = Qt::LeftButton;
    }
    else if (this->mousePressed && (pointer.touchDistance() > 0 ||
                                    pointer.touchZone() == Leap::Pointable::ZONE_NONE ||
                                    forceRelease))         // FINGER NOT TOUCHING AND PREVIOUS PRESS -> RELEASING BUTTON PRESS
    {
        frameMouseEvent = QMouseEvent::MouseButtonRelease;
        this->mousePressed = false;
        button = Qt::LeftButton;
    }
    else if (frameMouseEvent == QMouseEvent::None &&     // FINGER IN TOUCHING OR HOVERING ZONE AND NO BUTTON PRESS / RELEASE CHANGE -> MouseMove
             pointer.touchZone() != Leap::Pointable::ZONE_NONE
             && globalPointerPos.toPoint() != this->previousPos)
    {
        frameMouseEvent = QMouseEvent::MouseMove;
        this->previousPos = globalPointerPos.toPoint();
        QCursor::setPos(this->previousPos);
    }

    if (this->mousePressed)
        buttons |= Qt::LeftButton;

    if (frameMouseEvent != QMouseEvent::None)
        foreach (QObject *listener, this->inputListeners)
            QCoreApplication::postEvent(listener, new QMouseEvent(frameMouseEvent,
                                                                  this->convertGlobalPosToLocalPos(listener, globalPointerPos),
                                                                  globalPointerPos,
                                                                  button,
                                                                  buttons,
                                                                  Qt::NoModifier));
}

void LeapMotionListener::handleTouchEvents(const Leap::Frame &frame)
{
    if (this->inputListeners.empty())
        return ;
    /////// TOUCH EVENTS /////////
    // TOUCHBEGIN
    // TOUCHUPDATE
    // TOUCHEND
    // TOUCHCANCEL

    QTouchEvent::Type frameTouchEvent = QTouchEvent::None;
    Qt::TouchPointStates touchPointState = 0;
    QList<Leap::Pointable> touchingPointables;

    // RETRIEVE ONLY VALID AND TOUCHING POINTS
    for (int i = 0; i < frame.pointables().count(); i++)
    {
        const Leap::Pointable pointer = frame.pointables()[i];
        if (pointer.touchDistance() <= 0.5 && // IF TOO SENSISBLE CHANGE 0 FOR A VALUE LIKE 0.5 OR 0.75
                pointer.touchZone() != Leap::Pointable::ZONE_NONE &&
                pointer.isValid())
            touchingPointables.append(pointer);
    }

    int pointCountDiff = touchingPointables.count() - this->touchPoints.size();

    if (pointCountDiff == 0 && !this->touchPoints.empty()) // SAME AMOUT OF POINTS AS PREVIOUS FRAME AND MORE THAN 0 POINTS
    {
        //        qDebug() << "Touch Update 1";
        frameTouchEvent = QTouchEvent::TouchUpdate;
    }
    else if (pointCountDiff < 0) // LESS POINTS PRESSED THAN PREVIOUS FRAME
    {
        if (touchingPointables.count() == 0) // NO MORE TOUCHING POINTS
        {
            //            qDebug() << "Touch End";
            frameTouchEvent = QTouchEvent::TouchEnd;
        }
        else
        {
//            qDebug() << "Touch Update 2";
            frameTouchEvent = QTouchEvent::TouchUpdate;
        }
        //        qDebug() << "Pointables " << touchingPointables.count() << " diff " << pointCountDiff;
    }
    else if (pointCountDiff > 0) // MORE POINTS IN CURRENT FRAME THAN PREVIOUS
    {
        if (this->touchPoints.empty())
        {
            frameTouchEvent = QTouchEvent::TouchBegin;
            //            qDebug() << "Touch Begin";
        }
        else
        {
            frameTouchEvent = QTouchEvent::TouchUpdate;
            //            qDebug() << "Touch Update 3";
        }
    }


    // ALL TOUCHPOINT ARE SET TO BE RELEASED, IF THEY ARE IN THE CURRENT FRAME, THERE STATE WILL BE UPDATED BELOW HENCE NO RELEASE
    for (int i = 0; i < this->touchPoints.size(); i++)
    {
        QTouchEvent::TouchPoint touchPoint = this->touchPoints.takeAt(i);
        touchPoint.setLastPos(touchPoint.pos());
        touchPoint.setLastScreenPos(touchPoint.screenPos());
        touchPoint.setLastNormalizedPos(touchPoint.normalizedPos());
        touchPoint.setState(Qt::TouchPointReleased);
        this->touchPoints.insert(i, touchPoint);
    }

    if (pointCountDiff < 0)
        touchPointState = Qt::TouchPointReleased;

    // SET TOUCH POINTS LIST IF TOUCHBEGIN OR TOUCHUPDATE
    if (frameTouchEvent != QTouchEvent::None) // NO NEED TO TEST FOR TOUCHEND AS touchPointables == 0 IN THAT CASE
        for (int i = 0; i < touchingPointables.count(); i++)
        {
            Leap::Pointable pointer = touchingPointables[i];
            Leap::Vector normalizedPointerPos = frame.interactionBox().normalizePoint(pointer.stabilizedTipPosition());
            QPointF globalPointerPos = this->convertPointablePosToScreenPos(normalizedPointerPos);
            QPointF localPointerPos = globalPointerPos;
            QTouchEvent::TouchPoint touchPoint(pointer.id());
            touchPoint.setState(Qt::TouchPointPressed);

            // RETRIEVE LAST TOUCH EVENT MATCHING POINTABLE ID IF IT EXISTS
            for (int j = 0; j < this->touchPoints.size(); j++)
                if (this->touchPoints[j].id() == pointer.id())
                {
                    touchPoint = this->touchPoints.takeAt(j);
                    touchPoint.setState(Qt::TouchPointMoved);
                    break;
                }
            // SET ALL ATTRIBUTES THAT NEED TO BE SET OR UPDATED
            touchPoint.setPos(localPointerPos);
            touchPoint.setScreenPos(globalPointerPos);
//            touchPoint.setPressure((pointer.touchDistance() - 1) / 2.0);
//            if (this->savedMousePointableId == touchPoint.id())
//                touchPoint.setPressure(1);
                            touchPoint.setPressure(0);
            touchPoint.setNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));

            if (touchPoint.state() == Qt::TouchPointMoved && touchPoint.pos() == touchPoint.lastPos())
                touchPoint.setState(Qt::TouchPointStationary);

            touchPointState |= touchPoint.state();

            // IF START OF MOUVEMENT, SET STARTING POS OF TOUCH EVENT
            if (touchPoint.state() == Qt::TouchPointPressed)
            {
                touchPoint.setStartPos(localPointerPos);
                touchPoint.setStartScreenPos(globalPointerPos);
                touchPoint.setStartNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));
            }
            // FIRST TOUCH POINT TRANSLATED TO MOUSE EVENT SO WE MAKE SURE THIS IS THE SAME POINTER AS THE MOUSE
//            if (this->savedMousePointableId != touchPoint.id())
                this->touchPoints.append(touchPoint);
        }


    // TRANSMIT EVENT TO TARGETLISTENER IF THE EVENT IS VALID
    if (frameTouchEvent != QTouchEvent::None)
        foreach (QObject *listener, this->inputListeners)
            QCoreApplication::postEvent(listener,
                                        new QTouchEvent(frameTouchEvent,
                                                        LeapMotionTouchDevice::getInstance(),
                                                        Qt::NoModifier,
                                                        touchPointState,
                                                        this->touchPoints));

    //    if (frameTouchEvent == QTouchEvent::TouchEnd || frameTouchEvent == QTouchEvent::TouchBegin)
    //    {
    //        qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>";
    //        foreach (QTouchEvent::TouchPoint point, this->touchPoints)
    //        {
    //            qDebug() << "--";
    //            qDebug() << "Id : " << point.id();
    //            QString state = (point.state() == Qt::TouchPointMoved) ? "moved" : ((point.state() == Qt::TouchPointPressed) ? "pressed" : "released");
    //            qDebug() << "State " << state;
    //            qDebug() << "--";

    //        }
    //        qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<";
    //    }

    // CLEAR TOUCH POINTS ON TOUCHEND OR TOUCHCANCEL
    if (frameTouchEvent == QTouchEvent::TouchEnd || frameTouchEvent == QTouchEvent::TouchCancel)
        this->touchPoints.clear();

    // CLEAR POINT FROM LIST THAT HAVE BEEN SET TO RELEASED
    for (int i = 0; i < this->touchPoints.size(); i++)
        if (this->touchPoints[i].state() == Qt::TouchPointReleased)
        {
//            qDebug() << "Removing Point =======================================";
            this->touchPoints.removeAt(i);
            i = 0;
        }
}

QPointF LeapMotionListener::convertHandPosToScreenPos(const Leap::InteractionBox &interactionBox,
                                                      const Leap::Hand &hand)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(hand.palmPosition());
    return this->convertPointablePosToScreenPos(normalizedPos);
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                                           const Leap::Pointable &pointable)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(pointable.stabilizedTipPosition());
    return this->convertPointablePosToScreenPos(normalizedPos);
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::Vector &normalizedPos)
{
    return QPointF(normalizedPos.x * this->primaryScreen->geometry().width(),
                   (1 - normalizedPos.y) * this->primaryScreen->geometry().height());
}

QVector3D LeapMotionListener::convertVectorToNormalizedScreenVector(const Leap::InteractionBox &interactionBox, const Leap::Vector &rawPos)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(rawPos);
    QPointF screenPos = this->convertPointablePosToScreenPos(normalizedPos);
    QVector3D ret = QVector3D(screenPos.x(), screenPos.y(), normalizedPos.z);
    return ret;
}

QPointF LeapMotionListener::convertGlobalPosToLocalPos(QObject *container, const QPointF &globalPos)
{
    QWindow *win = NULL;
    if ((win = qobject_cast<QWindow *>(container)) != NULL)
        return QPointF(win->mapFromGlobal(globalPos.toPoint()));
    return globalPos;
}

void LeapMotionListener::onInit(const Leap::Controller &controller)
{
    qDebug() << "On Listener Init";
    // SET SUPPORTED GESTURES WE WANT TO HANDLE
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE, true);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE, true);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP, true);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP, true);

    this->gestureHandlers[Leap::Gesture::TYPE_SWIPE] = &LeapMotionListener::swipeGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_CIRCLE] = &LeapMotionListener::circleGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_KEY_TAP] = &LeapMotionListener::keyTapGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_SCREEN_TAP] = &LeapMotionListener::screenTapGestureHandler;
}

void LeapMotionListener::onConnect(const Leap::Controller &)
{
    qDebug() << "On Listener Connect";
}

void LeapMotionListener::onDisconnect(const Leap::Controller &)
{
    qDebug() << "On Listener Disonnect";
}

void LeapMotionListener::onExit(const Leap::Controller &)
{
    qDebug() << "On Listener Exit";
}

void LeapMotionListener::onFrame(const Leap::Controller &controller)
{
    Leap::Frame frame = controller.frame();

    if (frame.isValid())
    {
        // RETRIEVE FINGER INFORMATIONS AND CONVERT THEM TO MOUSE AND TOUCH EVENTS
        this->handleMouseEvents(frame);
        this->handleTouchEvents(frame);
        // ANALYSE FRAME GESTURES AND CALL TARGETS THAT ARE QTQUICK PLUGINS
        // CREATE QTQUICK PLUGINS LeapGestureArea (FOR GESTURES)
        // FOR EACH GESTURE IN A FRAME, CHECK IF QTQUICK PLUGIN HAS IMPLEMENTED GESTURE TYPE AND IF GESTURE OCCURED WITHIN THE QTQUICK PLUGIN AREA
        // IF SO TRIGGER CALLBACK IN QTQUICK PLUGIN
        /////// LEAP MOTION BUILT-IN GESTURES ////////
        // SCREEN TAP
        // SWIPE
        // CIRCLE
        // KEY TAP
        for (int i = 0; i < frame.gestures().count(); i++)
        {
            Leap::Gesture gesture = frame.gestures()[i];
            if (gesture.isValid() && this->gestureHandlers.contains(gesture.type()))
                (this->*this->gestureHandlers[gesture.type()])(gesture, frame);
        }

        /////// TEPEE3D CUSTOM GESTURES DETECTION //////////
        // PINCH
    }
}

void LeapMotionListener::onFocusGained(const Leap::Controller &)
{
    qDebug() << "On Listener FocusGained";
}

void LeapMotionListener::onFocusLost(const Leap::Controller &)
{
    qDebug() << "On Listener FocusLost";
}

void LeapMotionListener::addInputListener(QObject *target)
{
    if ((qobject_cast<QQuickItem *>(target) != NULL ||
         qobject_cast<QWindow*>(target) != NULL) &&
            !this->inputListeners.contains(target))
        this->inputListeners.append(target);
}

void LeapMotionListener::removeInputListener(QObject *target)
{
    if (target != NULL && this->inputListeners.contains(target))
        this->inputListeners.removeAll(target);
}

void LeapMotionListener::addGestureListener(QObject *listener)
{
    if (qobject_cast<Services::LeapMotionServiceGestureUserInterface*>(listener) != NULL &&
            !this->gesturesListeners.contains(listener))
        this->gesturesListeners.append(listener);
}

void LeapMotionListener::removeGestureListener(QObject *listener)
{
    if (qobject_cast<Services::LeapMotionServiceGestureUserInterface*>(listener) != NULL &&
            this->gesturesListeners.contains(listener))
        this->gesturesListeners.removeAll(listener);
}


