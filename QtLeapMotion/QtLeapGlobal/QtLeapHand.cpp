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

#include "QtLeapHand.h"
#include "QtLeapPointable.h"
#include "QtLeapFinger.h"
#include "QtLeapTool.h"

namespace QtLeapMotion
{

QtLeapHand::QtLeapHand(QObject *parent)
    : QObject(parent),
      m_id(-1),
      m_pitch(0),
      m_roll(0),
      m_yaw(0),
      m_timeVisible(0),
      m_sphereRadius(0)
{
}

QtLeapHand::~QtLeapHand()
{
}

QtLeapHand *QtLeapHand::fromLeapHand(Leap::Hand *hand)
{
    QtLeapHand *nHand = new QtLeapHand();
    nHand->update(hand);
    nHand->m_id = hand->id();
    return nHand;
}

void QtLeapHand::update(Leap::Hand *hand)
{
    this->setPitch(hand->palmPosition().pitch());
    this->setRoll(hand->palmPosition().roll());
    this->setYaw(hand->palmPosition().yaw());
    this->setSphereRadius(hand->sphereRadius());
    this->setSphereCenter(QVector3D(hand->sphereCenter().x,
                                     hand->sphereCenter().y,
                                     hand->sphereCenter().z));
    this->setDirection(QVector3D(hand->direction().x,
                                  hand->direction().y,
                                  hand->direction().x));
    this->setNormal(QVector3D(hand->palmNormal().x,
                               hand->palmNormal().y,
                               hand->palmNormal().z));
    this->setVelocity(QVector3D(hand->palmVelocity().x,
                                 hand->palmVelocity().y,
                                 hand->palmVelocity().z));
    this->setStabilizedPosition(QVector3D(hand->palmPosition().x,
                                           hand->palmPosition().y,
                                           hand->palmPosition().z));
    this->setSphereCenter(QVector3D(hand->sphereCenter().x,
                                     hand->sphereCenter().y,
                                     hand->sphereCenter().z));
}

int QtLeapHand::getId() const
{
    return this->m_id;
}

float QtLeapHand::getPitch() const
{
    return this->m_pitch;
}

float QtLeapHand::getYaw() const
{
    return this->m_yaw;
}

float QtLeapHand::getRoll() const
{
    return this->m_roll;
}

float QtLeapHand::getTimeVisible() const
{
    return this->m_timeVisible;
}

float QtLeapHand::getSphereRadius() const
{
    return this->m_sphereRadius;
}

QVector3D QtLeapHand::getDirection() const
{
    return this->m_direction;
}

QVector3D QtLeapHand::getPosition() const
{
    return this->m_position;
}

QVector3D QtLeapHand::getNormal() const
{
    return this->m_normal;
}

QVector3D QtLeapHand::getVelocity() const
{
    return this->m_velocity;
}

QVector3D QtLeapHand::getStabilizedPosition() const
{
    return this->m_stabilizedPosition;
}

QVector3D QtLeapHand::getSphereCenter() const
{
    return this->m_sphereCenter;
}

QList<QtLeapPointable *> QtLeapHand::getPointables() const
{
    return this->m_pointables;
}

QList<QtLeapFinger *> QtLeapHand::getFingers() const
{
    return this->m_fingers;
}

QList<QtLeapTool *> QtLeapHand::getTools() const
{
    return this->m_tools;
}

void QtLeapHand::setPitch(float pitch)
{
    if (this->m_pitch != pitch)
    {
        this->m_pitch = pitch;
        emit pitchChanged();
    }
}

void QtLeapHand::setYaw(float yaw)
{
    if (this->m_yaw != yaw)
    {
        this->m_yaw = yaw;
        emit yawChanged();
    }
}

void QtLeapHand::setRoll(float roll)
{
    if (this->m_roll != roll)
    {
        this->m_roll = roll;
        emit rollChanged();
    }
}

void QtLeapHand::setTimeVisible(float timeVisible)
{
    if (this->m_timeVisible != timeVisible)
    {
        this->m_timeVisible = timeVisible;
        emit timeVisibleChanged();
    }
}

void QtLeapHand::setSphereRadius(float sphereRadius)
{
    if (this->m_sphereRadius != sphereRadius)
    {
        this->m_sphereRadius = sphereRadius;
        emit sphereRadiusChanged();
    }
}

void QtLeapHand::setDirection(const QVector3D &direction)
{
    if (this->m_direction != direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapHand::setPosition(const QVector3D &position)
{
    if (this->m_position != position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void QtLeapHand::setNormal(const QVector3D &normal)
{
    if (this->m_normal != normal)
    {
        this->m_normal = normal;
        emit normalChanged();
    }
}

void QtLeapHand::setVelocity(const QVector3D &velocity)
{
    if (this->m_velocity != velocity)
    {
        this->m_velocity = velocity;
        emit velocityChanged();
    }
}

void QtLeapHand::setStabilizedPosition(const QVector3D &stabilizedPosition)
{
    if (this->m_stabilizedPosition != stabilizedPosition)
    {
        this->m_stabilizedPosition = stabilizedPosition;
        emit stabilizedPositionChanged();
    }
}

void QtLeapHand::setSphereCenter(const QVector3D &sphereCenter)
{
    if (this->m_sphereCenter != sphereCenter)
    {
        this->m_sphereCenter = sphereCenter;
        emit sphereCenterChanged();
    }
}

} //QtLeapMotion
