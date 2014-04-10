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

#include <QCoreApplication>
#include "DefaultQtLeapTouchHandler.h"

namespace QtLeapMotion
{

DefaultQtLeapTouchHandler::DefaultQtLeapTouchHandler(QObject *parent)
    : QObject(parent)
{
}

DefaultQtLeapTouchHandler::~DefaultQtLeapTouchHandler()
{
}

void DefaultQtLeapTouchHandler::onInit(const Leap::Controller &controller)
{
}

void DefaultQtLeapTouchHandler::setMotionListeners(QList<QObject *> listeners)
{
    this->listeners = listeners;
}

void DefaultQtLeapTouchHandler::onFrame(const Leap::Frame &frame)
{
    if (this->listeners.empty())
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
        frameTouchEvent = QTouchEvent::TouchUpdate;
    else if (pointCountDiff < 0) // LESS POINTS PRESSED THAN PREVIOUS FRAME
    {
//        if (touchingPointables.count() == 0) // NO MORE TOUCHING POINTS
//            frameTouchEvent = QTouchEvent::TouchUpdate;
//        else
            frameTouchEvent = QTouchEvent::TouchUpdate;
    }
    else if (pointCountDiff > 0) // MORE POINTS IN CURRENT FRAME THAN PREVIOUS
    {
        if (this->touchPoints.empty())
            frameTouchEvent = QTouchEvent::TouchBegin;
        else
            frameTouchEvent = QTouchEvent::TouchUpdate;
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
            QPointF globalPointerPos = QtLeapUtils::convertNormalizedPointablePosToScreenPos(normalizedPointerPos);
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
            this->touchPoints.append(touchPoint);
        }

    // TRANSMIT EVENT TO TARGETLISTENER IF THE EVENT IS VALID
    if (frameTouchEvent != QTouchEvent::None)
        foreach (QObject *listener, this->listeners)
            QCoreApplication::postEvent(listener,
                                        new QTouchEvent(frameTouchEvent,
                                                        QtLeapMotionTouchDevice::getInstance(),
                                                        Qt::NoModifier,
                                                        touchPointState,
                                                        this->touchPoints));

    // CLEAR TOUCH POINTS ON TOUCHEND OR TOUCHCANCEL
    if (frameTouchEvent == QTouchEvent::TouchEnd || frameTouchEvent == QTouchEvent::TouchCancel)
        this->touchPoints.clear();

    // CLEAR POINT FROM LIST THAT HAVE BEEN SET TO RELEASED
    for (int i = 0; i < this->touchPoints.size(); i++)
        if (this->touchPoints[i].state() == Qt::TouchPointReleased)
        {
            this->touchPoints.removeAt(i);
            i = 0;
        }
}

void DefaultQtLeapTouchHandler::onCleanup()
{
}

} // QtLeapMotion
