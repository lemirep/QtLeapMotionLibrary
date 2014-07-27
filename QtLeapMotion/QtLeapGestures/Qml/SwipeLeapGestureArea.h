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

#ifndef SWIPELEAPGESTUREAREA_H
#define SWIPELEAPGESTUREAREA_H

#include <QQuickItem>
#include <QQmlListProperty>
#include <QHash>
#include <QSGSimpleRectNode>
#include <QtLeapSwipeGesture.h>
#include <AbstractGestureArea.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QTLEAPMOTION_EXPORT SwipeLeapGestureArea
        :
        public AbstractGestureArea
{
    Q_OBJECT
    Q_PROPERTY(QList<QtLeapMotion::QtLeapSwipeGesture*> gesturesList READ getGesturesList NOTIFY gesturesListChanged)

    // Have a bounding box in 3D to detect if gesture is inside

public:
    SwipeLeapGestureArea(QQuickItem *parent = 0);
    void updateGestures(QList<QObject *> gesture);
    QList<QtLeapMotion::QtLeapSwipeGesture *> getGesturesList() const;

protected:
    QHash<int, QtLeapMotion::QtLeapSwipeGesture *> gesturesHash;


signals :
    void    gesturesListChanged();
    void    gestureStarted(QtLeapMotion::QtLeapSwipeGesture *gesture);
    void    gestureUpdated(QtLeapMotion::QtLeapSwipeGesture *gesture);
    void    gestureEnded(QtLeapMotion::QtLeapSwipeGesture *gesture);

};

} // QtLeapMotion

#endif // SWIPELEAPGESTUREAREA_H
