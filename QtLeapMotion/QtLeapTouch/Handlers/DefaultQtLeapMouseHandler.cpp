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

#include "DefaultQtLeapMouseHandler.h"

namespace QtLeapMotion
{

DefaultQtLeapMouseHandler::DefaultQtLeapMouseHandler(QObject *parent) :
    QObject(parent),
    savedMousePointableId(-1),
    mousePressed(false)
{
}

DefaultQtLeapMouseHandler::~DefaultQtLeapMouseHandler()
{
}

void DefaultQtLeapMouseHandler::onInit(const Leap::Controller &controller)
{
}

void DefaultQtLeapMouseHandler::setMotionListeners(QList<QObject *> listeners)
{
    this->listeners = listeners;
}

void DefaultQtLeapMouseHandler::onFrame(const Leap::Frame &frame)
{
    /////// MOUSE EVENTS /////////
    // MOUSE BUTTON PRESSED
    // MOUSE BUTTON RELEASED
    // MOUSE MOVE

    if (this->listeners.empty())
        return ;

    Leap::Pointable pointer = frame.pointable(this->savedMousePointableId);
    if (!pointer.isValid())
    {
        pointer = frame.pointables().frontmost();
        this->savedMousePointableId = pointer.id();
    }

    bool forceRelease = (frame.pointables().count() == 0 && this->mousePressed);
    QMouseEvent::Type frameMouseEvent = QMouseEvent::None;
    QPointF globalPointerPos = QtLeapUtils::convertPointablePosToScreenPos(frame.interactionBox(), pointer);
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
        foreach (QObject *listener, this->listeners)
            QCoreApplication::postEvent(listener, new QMouseEvent(frameMouseEvent,
                                                                  QtLeapUtils::convertGlobalPosToLocalPos(listener, globalPointerPos),
                                                                  globalPointerPos,
                                                                  button,
                                                                  buttons,
                                                                  Qt::NoModifier));
}

void DefaultQtLeapMouseHandler::onCleanup()
{

}

} //QtLeapMotion
