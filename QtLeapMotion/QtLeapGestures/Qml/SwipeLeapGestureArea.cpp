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

#include "SwipeLeapGestureArea.h"

namespace QtLeapMotion
{

SwipeLeapGestureArea::SwipeLeapGestureArea(QQuickItem *parent)
    : AbstractGestureArea(parent)
{
}

void SwipeLeapGestureArea::updateGestures(QList<QObject *> gestures)
{
    foreach (QObject *gesture, gestures)
    {
        QtLeapMotion::QtLeapSwipeGesture *swipeGesture = qobject_cast<QtLeapMotion::QtLeapSwipeGesture*>(gesture);
        if (swipeGesture &&
                swipeGesture->getState() !=
                QtLeapMotion::QtLeapSwipeGesture::GestureInvalid)
        {
            switch (swipeGesture->getState())
            {
            case QtLeapMotion::QtLeapSwipeGesture::GestureUpdated:
                emit gestureUpdated(swipeGesture);
                break;
            case QtLeapMotion::QtLeapSwipeGesture::GestureStarted:
                this->gesturesHash[swipeGesture->getId()] = swipeGesture;
                emit gestureStarted(swipeGesture);
                break;
            case QtLeapMotion::QtLeapSwipeGesture::GestureDone:
                this->gesturesHash.remove(swipeGesture->getId());
                emit gestureEnded(swipeGesture);
                break;
            default:
                return;
            };
        }
    }
}

QList<QtLeapMotion::QtLeapSwipeGesture *> SwipeLeapGestureArea::getGesturesList() const
{
    return this->gesturesHash.values();
}

} // QtLeapMotion
