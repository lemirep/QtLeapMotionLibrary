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

namespace QtLeapMotion
{

QtLeapPointable::QtLeapPointable(Leap::Pointable *pointable,
                                 QtLeapHand *parent)
    : QObject(parent)
{
    this->m_hand = parent;

}

QtLeapPointable::~QtLeapPointable()
{
}

int QtLeapPointable::getId() const
{
    return this->m_id;
}

bool QtLeapPointable::isHovering() const
{
    return this->m_hovering;
}

bool QtLeapPointable::isTouching() const
{
    return this->m_touching;
}

float QtLeapPointable::getWidth() const
{
    return this->m_width;
}

float QtLeapPointable::getLength() const
{
    return this->m_length;
}

float QtLeapPointable::getTouchDistance() const
{
    return this->m_touchDistance;
}

float QtLeapPointable::getTimeVisible() const
{
    return this->m_timeVisible;
}

QVector3D QtLeapPointable::getPosition() const
{
    return this->m_position;
}

QVector3D QtLeapPointable::getDirection() const
{
    return this->m_direction;
}

QVector3D QtLeapPointable::getStabilizedPosition() const
{
    return this->m_stabilizedPosition;
}

QVector3D QtLeapPointable::getVelocity() const
{
    return this->m_velocity;
}

QVector3D QtLeapPointable::getTipPosition() const
{
    return this->m_tipPosition;
}

QVector3D QtLeapPointable::getTipVelocity() const
{
    return this->m_tipVelocity;
}

QVector3D QtLeapPointable::getStabilizedTipPosition() const
{
    return this->m_stabilizedTipPosition;
}

QtLeapHand *QtLeapPointable::getHand() const
{
    return this->m_hand;
}

void QtLeapPointable::setHovering(bool hovering)
{
    if (this->m_hovering != hovering)
    {
        this->m_hovering = hovering;
        emit hoveringChanged();
    }
}

void QtLeapPointable::setTouching(bool touching)
{
    if (this->m_touching != touching)
    {
        this->m_touching = touching;
        emit touchingChanged();
    }
}

void QtLeapPointable::setWidth(float width)
{
    if (this->m_width != width)
    {
        this->m_width = width;
        emit widthChanged();
    }
}

void QtLeapPointable::setLength(float length)
{
    if (this->m_length != length)
    {
        this->m_length = length;
        emit lengthChanged();
    }
}

void QtLeapPointable::setTouchDistance(float touchDistance)
{
    if (this->m_touchDistance != touchDistance)
    {
        this->m_touchDistance = touchDistance;
        emit touchDistanceChanged();
    }
}

void QtLeapPointable::setTimeVisible(float timeVisible)
{
    if (this->m_timeVisible != timeVisible)
    {
        this->m_timeVisible = timeVisible;
        emit timeVisibleChanged();
    }
}

void QtLeapPointable::setPosition(const QVector3D &position)
{
    if (this->m_position != position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void QtLeapPointable::setDirection(const QVector3D &direction)
{
    if (this->m_direction != direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapPointable::setStabilizedPosition(const QVector3D &stabilizedPosition)
{
    if (this->m_stabilizedPosition != stabilizedPosition)
    {
        this->m_stabilizedPosition = stabilizedPosition;
        emit stabilizedPositionChanged();
    }
}

void QtLeapPointable::setVelocity(const QVector3D &velocity)
{
    if (this->m_velocity != velocity)
    {
        this->m_velocity = velocity;
        emit velocityChanged();
    }
}

void QtLeapPointable::setTipPosition(const QVector3D &tipPosition)
{
    if (this->m_tipPosition != tipPosition)
    {
        this->m_tipVelocity = tipPosition;
        emit tipPositionChanged();
    }
}

void QtLeapPointable::setTipVelocity(const QVector3D &tipVelocity)
{
    if (this->m_tipVelocity != tipVelocity)
    {
        this->m_tipVelocity = tipVelocity;
        emit tipVelocityChanged();
    }
}

void QtLeapPointable::setTipStabilizedPosition(const QVector3D &stabilizedTipPosition)
{
    if (this->m_stabilizedTipPosition != stabilizedTipPosition)
    {
        this->m_stabilizedPosition = stabilizedTipPosition;
        emit stabilizedTipPositionChanged();
    }
}

}   // QtLeapMotion
