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

#include "QtLeapPointable.h"
#include "QtLeapHand.h"
#include "Leap.h"

namespace QtLeapMotion
{

class QtLeapPointablePrivate
{
public:
    QtLeapPointablePrivate(QtLeapPointable *qq)
        : q_ptr(qq)
    {
    }

    Q_DECLARE_PUBLIC(QtLeapPointable)

    int m_id;
    bool m_hovering;
    bool m_touching;
    float m_width;
    float m_length;
    float m_touchDistance;
    float m_timeVisible;
    QVector3D m_position;
    QVector3D m_direction;
    QVector3D m_stabilizedPosition;
    QVector3D m_velocity;
    QtLeapHand *m_hand;
    QtLeapPointable *q_ptr;
};

QtLeapPointable::QtLeapPointable(Leap::Pointable *pointable,
                                 QtLeapHand *parent)
    : QObject(parent)
    , d_ptr(new QtLeapPointablePrivate(this))
{
    Q_D(QtLeapPointable);
    d->m_hand = parent;
    d->m_id = pointable->id();
    update(pointable);
}

QtLeapPointable::~QtLeapPointable()
{
    delete d_ptr;
}

int QtLeapPointable::getId() const
{
    Q_D(const QtLeapPointable);
    return d->m_id;
}

bool QtLeapPointable::isHovering() const
{
    Q_D(const QtLeapPointable);
    return d->m_hovering;
}

bool QtLeapPointable::isTouching() const
{
    Q_D(const QtLeapPointable);
    return d->m_touching;
}

float QtLeapPointable::getWidth() const
{
    Q_D(const QtLeapPointable);
    return d->m_width;
}

float QtLeapPointable::getLength() const
{
    Q_D(const QtLeapPointable);
    return d->m_length;
}

float QtLeapPointable::getTouchDistance() const
{
    Q_D(const QtLeapPointable);
    return d->m_touchDistance;
}

float QtLeapPointable::getTimeVisible() const
{
    Q_D(const QtLeapPointable);
    return d->m_timeVisible;
}

QVector3D QtLeapPointable::getPosition() const
{
    Q_D(const QtLeapPointable);
    return d->m_position;
}

QVector3D QtLeapPointable::getDirection() const
{
    Q_D(const QtLeapPointable);
    return d->m_direction;
}

QVector3D QtLeapPointable::getStabilizedPosition() const
{
    Q_D(const QtLeapPointable);
    return d->m_stabilizedPosition;
}

QVector3D QtLeapPointable::getVelocity() const
{
    Q_D(const QtLeapPointable);
    return d->m_velocity;
}

QtLeapHand *QtLeapPointable::getHand() const
{
    Q_D(const QtLeapPointable);
    return d->m_hand;
}

void QtLeapPointable::update(Leap::Pointable *pointable)
{
    this->setDirection(QVector3D(pointable->direction().x,
                                 pointable->direction().y,
                                 pointable->direction().z));
    this->setVelocity(QVector3D(pointable->tipVelocity().x,
                                pointable->tipVelocity().y,
                                pointable->tipVelocity().z));
    this->setPosition(QVector3D(pointable->tipPosition().x,
                                pointable->tipPosition().y,
                                pointable->tipPosition().z));
    this->setStabilizedPosition(QVector3D(pointable->stabilizedTipPosition().x,
                                          pointable->stabilizedTipPosition().y,
                                          pointable->stabilizedTipPosition().z));
    this->setLength(pointable->length());
    this->setWidth(pointable->width());
    this->setHovering(pointable->touchDistance() >= 0);
    this->setTouching(!isHovering());
    this->setTouchDistance(pointable->touchDistance());
}

void QtLeapPointable::setHovering(bool hovering)
{
    Q_D(QtLeapPointable);
    if (d->m_hovering != hovering)
    {
        d->m_hovering = hovering;
        emit hoveringChanged();
    }
}

void QtLeapPointable::setTouching(bool touching)
{
    Q_D(QtLeapPointable);
    if (d->m_touching != touching)
    {
        d->m_touching = touching;
        emit touchingChanged();
    }
}

void QtLeapPointable::setWidth(float width)
{
    Q_D(QtLeapPointable);
    if (d->m_width != width)
    {
        d->m_width = width;
        emit widthChanged();
    }
}

void QtLeapPointable::setLength(float length)
{
    Q_D(QtLeapPointable);
    if (d->m_length != length)
    {
        d->m_length = length;
        emit lengthChanged();
    }
}

void QtLeapPointable::setTouchDistance(float touchDistance)
{
    Q_D(QtLeapPointable);
    if (d->m_touchDistance != touchDistance)
    {
        d->m_touchDistance = touchDistance;
        emit touchDistanceChanged();
    }
}

void QtLeapPointable::setTimeVisible(float timeVisible)
{
    Q_D(QtLeapPointable);
    if (d->m_timeVisible != timeVisible)
    {
        d->m_timeVisible = timeVisible;
        emit timeVisibleChanged();
    }
}

void QtLeapPointable::setPosition(const QVector3D &position)
{
    Q_D(QtLeapPointable);
    if (d->m_position != position)
    {
        d->m_position = position;
        emit positionChanged();
    }
}

void QtLeapPointable::setDirection(const QVector3D &direction)
{
    Q_D(QtLeapPointable);
    if (d->m_direction != direction)
    {
        d->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapPointable::setStabilizedPosition(const QVector3D &stabilizedPosition)
{
    Q_D(QtLeapPointable);
    if (d->m_stabilizedPosition != stabilizedPosition)
    {
        d->m_stabilizedPosition = stabilizedPosition;
        emit stabilizedPositionChanged();
    }
}

void QtLeapPointable::setVelocity(const QVector3D &velocity)
{
    Q_D(QtLeapPointable);
    if (d->m_velocity != velocity)
    {
        d->m_velocity = velocity;
        emit velocityChanged();
    }
}

}   // QtLeapMotion
