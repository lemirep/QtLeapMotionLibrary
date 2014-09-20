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

#ifndef HANDSMOTIONAREA_H
#define HANDSMOTIONAREA_H

#include <QQuickItem>
#include <QtLeapHandsListenerInterface.h>
#include <QtLeapGlobal.h>


namespace QtLeapMotion
{

class QtLeapHand;

class QTLEAPMOTION_EXPORT HandsMotionArea :
        public QQuickItem,
        public QtLeapHandsListenerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapHandsListenerInterface)
    Q_PROPERTY(QList<QtLeapMotion::QtLeapHand *> hands READ getHands NOTIFY handsChanged)
public:
    HandsMotionArea(QQuickItem *parent = 0);

    // Have a bounding box in 3D to detect if hand is inside

    // QtLeapHandsListenerInterface interface
    void updateHands(QList<QtLeapHand *> handsList);
    QList<QtLeapHand *> getHands() const;

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    void itemChange(ItemChange, const ItemChangeData &);

signals:
    void handUpdated(QtLeapMotion::QtLeapHand *hand);
    void handAdded(QtLeapMotion::QtLeapHand *hand);
    void handRemoved(QtLeapMotion::QtLeapHand *hand);
    void handsChanged();

private:
    QHash<int, QtLeapMotion::QtLeapHand *> m_hands;
};

}

#endif // HANDSMOTIONAREA_H
