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

#include "DefaultQtLeapTapGestureHandler.h"
#include "QtLeapGestureListenerInterface.h"
#include "QtLeapGesture.h"
#include "QtLeapKeyTapGesture.h"
#include "QtLeapScreenTapGesture.h"

namespace QtLeapMotion
{

DefaultQtLeapTapGestureHandler::DefaultQtLeapTapGestureHandler(QObject *parent)
    : QObject(parent)
{
}

DefaultQtLeapTapGestureHandler::~DefaultQtLeapTapGestureHandler()
{
}

void DefaultQtLeapTapGestureHandler::onInit(const Leap::Controller &controller)
{
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP, true);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP, true);
}

void DefaultQtLeapTapGestureHandler::setMotionListeners(QList<QtLeapGestureListenerInterface *> listeners)
{
    this->listeners = listeners;
}

void DefaultQtLeapTapGestureHandler::onFrame(const Leap::Frame &frame)
{
    if (frame.isValid() && !this->listeners.empty())
    {
        QList<int> validKEntries;
        QList<int> validSEntries;

        for (int i = 0; i < frame.gestures().count(); i++)
        {
            Leap::Gesture gesture = frame.gestures()[i];
            if (gesture.isValid())
            {
                if (gesture.type() == Leap::Gesture::TYPE_KEY_TAP)
                {
                    if (this->kGestures.contains(gesture.id()))
                        qobject_cast<QtLeapKeyTapGesture*>(this->kGestures[gesture.id()])->update(gesture);
                    else
                        this->kGestures[gesture.id()] = QtLeapKeyTapGesture::fromLeapGesture(gesture);
                    validKEntries << gesture.id();
                }
                else if (gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP)
                {
                    if (this->sGestures.contains(gesture.id()))
                        qobject_cast<QtLeapScreenTapGesture*>(this->sGestures[gesture.id()])->update(gesture);
                    else
                        this->sGestures[gesture.id()] = QtLeapScreenTapGesture::fromLeapGesture(gesture);
                    validSEntries << gesture.id();
                }
            }
        }
        foreach (const int idx, this->sGestures.keys())
            if (!validSEntries.contains(idx))
                this->sGestures.remove(idx);
        foreach (const int idx, this->kGestures.keys())
            if (!validKEntries.contains(idx))
                this->kGestures.remove(idx);
        QList<QObject *> gestures = this->sGestures.values() + this->kGestures.values();
        foreach (QtLeapGestureListenerInterface *listener, this->listeners)
            listener->updateGestures(gestures);
    }
}

void DefaultQtLeapTapGestureHandler::onCleanup()
{
    this->kGestures.clear();
    this->sGestures.clear();
}

} // QtLeapMotion
