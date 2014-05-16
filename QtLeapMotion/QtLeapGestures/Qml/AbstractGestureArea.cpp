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

#include "AbstractGestureArea.h"
#include "QtLeapMotionQQuickView.h"
#include "QtLeapMotionController.h"

namespace QtLeapMotion
{

AbstractGestureArea::AbstractGestureArea(QQuickItem *parent)
    : QQuickItem(parent)
{
}

AbstractGestureArea::~AbstractGestureArea()
{
}

QSGNode *AbstractGestureArea::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *data)
{
    Q_UNUSED(data);
    qDebug() << "Update Paint Node";
    QSGSimpleRectNode *rectangle = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!rectangle)
        rectangle = new QSGSimpleRectNode();
    rectangle->setRect(QRectF(0, 0, width(), height()));
    rectangle->setColor(QColor(255, 0, 0, 50));
    this->update();
    return rectangle;
}

void AbstractGestureArea::itemChange(QQuickItem::ItemChange, const QQuickItem::ItemChangeData &)
{
    QtLeapMotionQQuickView *win = Q_NULLPTR;

    if ((win = qobject_cast<QtLeapMotionQQuickView *>(this->window())) != Q_NULLPTR)
        win->getLeapController()->registerGestureListener(this);
}

//void AbstractGestureArea::append_gesture(QQmlListProperty<QtLeapMotion::QtLeapGesture> *list, QtLeapMotion::QtLeapGesture *a)
//{
//    AbstractGestureArea *gestureArea = static_cast<AbstractGestureArea *>(list->object);
//    gestureArea->getGesturesHash()[a->getId()] = a;
//}

//int AbstractGestureArea::gestures_count(QQmlListProperty<QtLeapMotion::QtLeapGesture> *list)
//{
//    AbstractGestureArea *gestureArea = static_cast<AbstractGestureArea *>(list->object);
//    return gestureArea->getGesturesHash().values().count();
//}

//QtLeapMotion::QtLeapGesture *AbstractGestureArea::gesture_at(QQmlListProperty<QtLeapMotion::QtLeapGesture> *list, int pos)
//{
//    AbstractGestureArea *gestureArea = static_cast<AbstractGestureArea *>(list->object);
//    return gestureArea->getGesturesHash().values().at(pos);
//}

//void AbstractGestureArea::clear_gestures(QQmlListProperty<QtLeapMotion::QtLeapGesture> *list)
//{
//    AbstractGestureArea *gestureArea = static_cast<AbstractGestureArea *>(list->object);
//    gestureArea->getGesturesHash().clear();
//}

} // QtLeapMotion
