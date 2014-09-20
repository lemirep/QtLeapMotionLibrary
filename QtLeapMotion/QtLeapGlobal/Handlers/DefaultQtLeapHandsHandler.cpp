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

#include "DefaultQtLeapHandsHandler.h"
#include "QtLeapHandsListenerInterface.h"
#include "QtLeapHand.h"

namespace QtLeapMotion
{

DefaultQtLeapHandsHandler::DefaultQtLeapHandsHandler(QObject *parent) : QObject(parent)
{

}

void DefaultQtLeapHandsHandler::onInit(const Leap::Controller &controller)
{
}

void DefaultQtLeapHandsHandler::setMotionListeners(QList<QtLeapHandsListenerInterface *> listeners)
{
    this->listeners = listeners;
}

void DefaultQtLeapHandsHandler::onFrame(const Leap::Frame &frame)
{
    // RETRIEVE HANDS FROM FRAME
    if (frame.isValid() && !this->listeners.empty())
    {
        QList<int> validEntries;
        for (int i = 0; i < frame.hands().count(); i++)
        {
            Leap::Hand hand = frame.hands()[i];
            if (hand.isValid())
            {
                if (this->hands.contains(hand.id()))
                    this->hands[hand.id()]->update(&hand);
                else
                    this->hands[hand.id()] = QtLeapHand::fromLeapHand(&hand);
                validEntries << hand.id();
            }
        }
        foreach (const int idx, this->hands.keys())
            if (!validEntries.contains(idx))
                this->hands.remove(idx);
        foreach (QtLeapHandsListenerInterface *listener, listeners)
            listener->updateHands(this->hands.values());
    }
}

void DefaultQtLeapHandsHandler::onCleanup()
{
    this->hands.clear();
}

} // QtLeapMotion
