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

#include "HandsMotionArea.h"
#include "QtLeapMotionQQuickView.h"
#include "QtLeapHand.h"
#include "QtLeapMotionController.h"
#include <QSGSimpleRectNode>

namespace QtLeapMotion
{

HandsMotionArea::HandsMotionArea(QQuickItem *parent) :
    QQuickItem(parent)
{
}

void HandsMotionArea::updateHands(QList<QtLeapHand *> handsList)
{
    QHash<int, QtLeapHand *> oldHands = m_hands;
    foreach (QtLeapHand *hand, handsList)
    {
        if (oldHands.contains(hand->getId()))
        {
            oldHands.remove(hand->getId());
            emit handUpdated(hand);
        }
        else
        {
            m_hands.insert(hand->getId(), hand);
            emit handAdded(hand);
        }
    }

    foreach (int id, oldHands.keys())
    {
        m_hands.remove(id);
        emit handRemoved(oldHands.value(id));
    }
    emit handsChanged();
}

QList<QtLeapHand *> HandsMotionArea::getHands() const
{
    return m_hands.values();
}

QSGNode *HandsMotionArea::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *data)
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

void HandsMotionArea::itemChange(QQuickItem::ItemChange, const QQuickItem::ItemChangeData &)
{
    QtLeapMotionQQuickView *win = Q_NULLPTR;

    if ((win = qobject_cast<QtLeapMotionQQuickView *>(this->window())) != Q_NULLPTR)
        win->getLeapController()->registerHandListener(this);
}

} // QtLeapMotion
