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

#include "DefaultQtLeapCircleGestureHandler.h"
#include "QtLeapGestureListenerInterface.h"
#include "QtLeapCircleGesture.h"
#include <QDebug>

namespace QtLeapMotion
{

DefaultQtLeapCircleGestureHandler::DefaultQtLeapCircleGestureHandler(QObject *parent)
    : QObject(parent)
{

}

DefaultQtLeapCircleGestureHandler::~DefaultQtLeapCircleGestureHandler()
{

}

void DefaultQtLeapCircleGestureHandler::onInit(const Leap::Controller &controller)
{
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE, true);
}

void DefaultQtLeapCircleGestureHandler::setMotionListeners(QList<QtLeapGestureListenerInterface *> listeners)
{
    this->listeners = listeners;
}

void DefaultQtLeapCircleGestureHandler::onFrame(const Leap::Frame &frame)
{
    if (frame.isValid() && !this->listeners.empty())
    {
        QList<int> validEntries;
        for (int i = 0; i < frame.gestures().count(); i++)
        {
            Leap::Gesture gesture = frame.gestures()[i];
            if (gesture.isValid() &&
                    gesture.type() == Leap::Gesture::TYPE_CIRCLE)
            {
                // Store gestures in a hash to check if they are new or updated
                if (this->gestures.contains(gesture.id()))
                    qobject_cast<QtLeapCircleGesture *>(this->gestures[gesture.id()])->update(gesture);
                else
                    this->gestures[gesture.id()] = QtLeapCircleGesture::fromLeapGesture(gesture);
                validEntries << gesture.id();
            }
        }
        foreach (const int idx, this->gestures.keys())
            if (!validEntries.contains(idx))
                this->gestures.remove(idx);
        foreach (QtLeapGestureListenerInterface *listener, this->listeners)
            listener->updateGestures(this->gestures.values());
    }
}

void DefaultQtLeapCircleGestureHandler::onCleanup()
{
    this->gestures.clear();
}

} // QtLeapMotion
