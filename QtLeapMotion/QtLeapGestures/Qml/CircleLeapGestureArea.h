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

#ifndef CIRCLELEAPGESTUREAREA_H
#define CIRCLELEAPGESTUREAREA_H

#include <QtLeapCircleGesture.h>
#include <AbstractGestureArea.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QTLEAPMOTION_EXPORT CircleLeapGestureArea
        :
        public AbstractGestureArea
{
    Q_OBJECT
    Q_PROPERTY(QList<QtLeapMotion::QtLeapCircleGesture*> gesturesList READ getGesturesList NOTIFY gesturesListChanged)

public:
    CircleLeapGestureArea(QQuickItem *parent = 0);

    // Have a bounding box in 3D to detect if hand is inside
    void updateGestures(QList<QObject *> gestures);
    QList<QtLeapMotion::QtLeapCircleGesture *> getGesturesList() const;

protected:
    QHash<int, QtLeapMotion::QtLeapCircleGesture *> gesturesHash;


signals :
    void    gesturesListChanged();
    void    gestureStarted(QtLeapMotion::QtLeapCircleGesture *gesture);
    void    gestureUpdated(QtLeapMotion::QtLeapCircleGesture *gesture);
    void    gestureEnded(QtLeapMotion::QtLeapCircleGesture *gesture);


};

} // QtLeapMotion

#endif // CIRCLELEAPGESTUREAREA_H
