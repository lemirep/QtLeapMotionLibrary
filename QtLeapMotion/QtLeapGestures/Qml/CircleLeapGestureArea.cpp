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

#include "CircleLeapGestureArea.h"

namespace QtLeapMotion
{

CircleLeapGestureArea::CircleLeapGestureArea(QQuickItem *parent)
    : AbstractGestureArea(parent)
{
}

void CircleLeapGestureArea::updateGestures(QList<QObject *> gestures)
{
    foreach (QObject *gesture, gestures)
    {
        QtLeapMotion::QtLeapCircleGesture *circleGesture = qobject_cast<QtLeapMotion::QtLeapCircleGesture*>(gesture);

        if (circleGesture &&
                circleGesture->getState() !=
                QtLeapMotion::QtLeapCircleGesture::GestureInvalid)
            switch (circleGesture->getState())
            {
            case QtLeapMotion::QtLeapCircleGesture::GestureUpdated:
                emit gestureUpdated(circleGesture);
                break;
            case QtLeapMotion::QtLeapCircleGesture::GestureStarted:
                this->gesturesHash[circleGesture->getId()] = circleGesture;
                emit gestureStarted(circleGesture);
                break;
            case QtLeapMotion::QtLeapCircleGesture::GestureDone:
                this->gesturesHash.remove(circleGesture->getId());
                emit gestureEnded(circleGesture);
                break;
            default:
                return;
            };
    }
}

QList<QtLeapMotion::QtLeapCircleGesture *> CircleLeapGestureArea::getGesturesList() const
{
    return this->gesturesHash.values();
}

} // QtLeapMotion
