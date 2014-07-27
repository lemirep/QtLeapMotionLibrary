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

#ifndef ABSTRACTGESTUREAREA_H
#define ABSTRACTGESTUREAREA_H

#include <QHash>
#include <QSGSimpleRectNode>
#include <QQuickItem>
#include <QObject>
#include <QtLeapGlobal.h>
#include <QtLeapGesture.h>
#include <QtLeapGestureListenerInterface.h>

namespace QtLeapMotion
{

class QtLeapMotionQQuickView;

class QTLEAPMOTION_EXPORT AbstractGestureArea
        :
        public QQuickItem,
        public QtLeapMotion::QtLeapGestureListenerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapGestureListenerInterface)

public:
    AbstractGestureArea(QQuickItem *parent = 0);
    virtual ~AbstractGestureArea();
    virtual void updateGestures(QList<QObject*> gestures) = 0;

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    void itemChange(ItemChange, const ItemChangeData &);

signals :
    void    gesturesListChanged();
    void    gestureStarted(QtLeapMotion::QtLeapGesture *gesture);
    void    gestureUpdated(QtLeapMotion::QtLeapGesture *gesture);
    void    gestureEnded(QtLeapMotion::QtLeapGesture *gesture);
};

} // QtLeapMotion

#endif // ABSTRACTGESTUREAREA_H
