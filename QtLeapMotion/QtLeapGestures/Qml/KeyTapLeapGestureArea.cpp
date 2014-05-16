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

#include "KeyTapLeapGestureArea.h"

namespace QtLeapMotion
{

KeyTapLeapGestureArea::KeyTapLeapGestureArea(QQuickItem *parent)
    : AbstractGestureArea(parent)
{
}

void KeyTapLeapGestureArea::updateGestures(QList<QObject *> gestures)
{
    foreach (QObject *gesture, gestures)
    {
        QtLeapMotion::QtLeapTapGesture *keyTapGesture = qobject_cast<QtLeapMotion::QtLeapTapGesture*>(gesture);

        if (keyTapGesture &&
                keyTapGesture->getState() !=
                QtLeapMotion::QtLeapTapGesture::GestureInvalid)
        {
            switch (keyTapGesture->getState())
            {
            case QtLeapMotion::QtLeapTapGesture::GestureUpdated:
                emit gestureUpdated(keyTapGesture);
                break;
            case QtLeapMotion::QtLeapTapGesture::GestureStarted:
                this->gesturesHash[keyTapGesture->getId()] = keyTapGesture;
                emit gestureStarted(keyTapGesture);
                break;
            case QtLeapMotion::QtLeapTapGesture::GestureDone:
                this->gesturesHash.remove(keyTapGesture->getId());
                emit gestureEnded(keyTapGesture);
                break;
            default:
                return ;
            };
        }
    }
}

QList<QtLeapMotion::QtLeapTapGesture *> KeyTapLeapGestureArea::getGesturesList() const
{
    return this->gesturesHash.values();
}

} // QtLeapMotion
