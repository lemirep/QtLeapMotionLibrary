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
#include "Leap.h"
#include <QHash>

namespace QtLeapMotion
{

class QtLeapHandPrivate
{
public:
    QtLeapHandPrivate(QtLeapHand *qq)
        : m_id(-1)
        , m_pitch(0)
        , m_roll(0)
        , m_yaw(0)
        , m_timeVisible(0)
        , m_sphereRadius(0)
        ,q_ptr(qq)
    {
    }

    Q_DECLARE_PUBLIC(QtLeapHand)

    int m_id;
    float m_pitch;
    float m_roll;
    float m_yaw;
    float m_timeVisible;
    float m_sphereRadius;
    bool m_left;
    bool m_right;
    bool m_isFist;

    QVector3D m_direction;
    QVector3D m_position;
    QVector3D m_normal;
    QVector3D m_velocity;
    QVector3D m_stabilizedPosition;
    QVector3D m_sphereCenter;

    QHash<int, QtLeapPointable*> m_pointables;
    QHash<int, QtLeapFinger*> m_fingers;
    QHash<int, QtLeapTool*> m_tools;

    QtLeapHand *q_ptr;
};

QtLeapHand::QtLeapHand(QObject *parent)
    : QObject(parent)
    , d_ptr(new QtLeapHandPrivate(this))
{
}

QtLeapHand::~QtLeapHand()
{
    delete d_ptr;
}

QtLeapHand *QtLeapHand::fromLeapHand(Leap::Hand *hand)
{
    QtLeapHand *nHand = new QtLeapHand();
    nHand->update(hand);
    nHand->setId(hand->id());
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
    this->setLeft(hand->isLeft());
    this->setRight(hand->isRight());
    // if sphereradius < 50 mm, we have a fist
    this->setFist(hand->sphereRadius() <= 50.0f);

    Q_D(QtLeapHand);
    QList<int> pointablesRemoved = d->m_pointables.keys();
    for (int i = 0; i < hand->pointables().count(); i++) {
        Leap::Pointable pointable = hand->pointables()[i];
        if (pointable.isValid())
        {
            if (d->m_pointables.contains(pointable.id()))
            {
                pointablesRemoved.removeAll(pointable.id());
                d->m_pointables[pointable.id()]->update(&pointable);
            }
            else
            {
                if (pointable.isFinger())
                {
                    QtLeapFinger *leapPointable = new QtLeapFinger(&pointable, this);
                    d->m_pointables[pointable.id()] = leapPointable;
                    d->m_fingers[pointable.id()] = leapPointable;
                }
                else if (pointable.isTool())
                {
                    QtLeapTool *leapPointable = new QtLeapTool(&pointable, this);
                    d->m_pointables[pointable.id()] = leapPointable;
                    d->m_tools[pointable.id()] = leapPointable;
                }
            }
        }
    }

    Q_FOREACH (int id, pointablesRemoved)
    {
        d->m_fingers.remove(id);
        d->m_tools.remove(id);
        delete d->m_pointables.take(id);
    }
}

int QtLeapHand::getId() const
{
    Q_D(const QtLeapHand);
    return d->m_id;
}

float QtLeapHand::getPitch() const
{
    Q_D(const QtLeapHand);
    return d->m_pitch;
}

float QtLeapHand::getYaw() const
{
    Q_D(const QtLeapHand);
    return d->m_yaw;
}

float QtLeapHand::getRoll() const
{
    Q_D(const QtLeapHand);
    return d->m_roll;
}

float QtLeapHand::getTimeVisible() const
{
    Q_D(const QtLeapHand);
    return d->m_timeVisible;
}

float QtLeapHand::getSphereRadius() const
{
    Q_D(const QtLeapHand);
    return d->m_sphereRadius;
}

bool QtLeapHand::isLeft() const
{
    Q_D(const QtLeapHand);
    return d->m_right;
}

bool QtLeapHand::isRight() const
{
    Q_D(const QtLeapHand);
    return d->m_left;
}

bool QtLeapHand::isFist() const
{
    Q_D(const QtLeapHand);
    return d->m_isFist;
}

QVector3D QtLeapHand::getDirection() const
{
    Q_D(const QtLeapHand);
    return d->m_direction;
}

QVector3D QtLeapHand::getPosition() const
{
    Q_D(const QtLeapHand);
    return d->m_position;
}

QVector3D QtLeapHand::getNormal() const
{
    Q_D(const QtLeapHand);
    return d->m_normal;
}

QVector3D QtLeapHand::getVelocity() const
{
    Q_D(const QtLeapHand);
    return d->m_velocity;
}

QVector3D QtLeapHand::getStabilizedPosition() const
{
    Q_D(const QtLeapHand);
    return d->m_stabilizedPosition;
}

QVector3D QtLeapHand::getSphereCenter() const
{
    Q_D(const QtLeapHand);
    return d->m_sphereCenter;
}

QList<QtLeapPointable *> QtLeapHand::getPointables() const
{
    Q_D(const QtLeapHand);
    return d->m_pointables.values();
}

QList<QtLeapFinger *> QtLeapHand::getFingers() const
{
    Q_D(const QtLeapHand);
    return d->m_fingers.values();
}

QList<QtLeapTool *> QtLeapHand::getTools() const
{
    Q_D(const QtLeapHand);
    return d->m_tools.values();
}

void QtLeapHand::setId(int id)
{
    Q_D(QtLeapHand);
    d->m_id = id;
}

void QtLeapHand::setPitch(float pitch)
{
    Q_D(QtLeapHand);
    if (d->m_pitch != pitch)
    {
        d->m_pitch = pitch;
        emit pitchChanged();
    }
}

void QtLeapHand::setYaw(float yaw)
{
    Q_D(QtLeapHand);
    if (d->m_yaw != yaw)
    {
        d->m_yaw = yaw;
        emit yawChanged();
    }
}

void QtLeapHand::setRoll(float roll)
{
    Q_D(QtLeapHand);
    if (d->m_roll != roll)
    {
        d->m_roll = roll;
        emit rollChanged();
    }
}

void QtLeapHand::setLeft(bool left)
{
    Q_D(QtLeapHand);
    if (d->m_left != left)
    {
        d->m_left = left;
        emit isLeftChanged();
    }
}

void QtLeapHand::setRight(bool right)
{
    Q_D(QtLeapHand);
    if (d->m_right != right)
    {
        d->m_right = right;
        emit isRightChanged();
    }
}

void QtLeapHand::setTimeVisible(float timeVisible)
{
    Q_D(QtLeapHand);
    if (d->m_timeVisible != timeVisible)
    {
        d->m_timeVisible = timeVisible;
        emit timeVisibleChanged();
    }
}

void QtLeapHand::setSphereRadius(float sphereRadius)
{
    Q_D(QtLeapHand);
    if (d->m_sphereRadius != sphereRadius)
    {
        d->m_sphereRadius = sphereRadius;
        emit sphereRadiusChanged();
    }
}

void QtLeapHand::setDirection(const QVector3D &direction)
{
    Q_D(QtLeapHand);
    if (d->m_direction != direction)
    {
        d->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapHand::setPosition(const QVector3D &position)
{
    Q_D(QtLeapHand);
    if (d->m_position != position)
    {
        d->m_position = position;
        emit positionChanged();
    }
}

void QtLeapHand::setNormal(const QVector3D &normal)
{
    Q_D(QtLeapHand);
    if (d->m_normal != normal)
    {
        d->m_normal = normal;
        emit normalChanged();
    }
}

void QtLeapHand::setVelocity(const QVector3D &velocity)
{
    Q_D(QtLeapHand);
    if (d->m_velocity != velocity)
    {
        d->m_velocity = velocity;
        emit velocityChanged();
    }
}

void QtLeapHand::setStabilizedPosition(const QVector3D &stabilizedPosition)
{
    Q_D(QtLeapHand);
    if (d->m_stabilizedPosition != stabilizedPosition)
    {
        d->m_stabilizedPosition = stabilizedPosition;
        emit stabilizedPositionChanged();
    }
}

void QtLeapHand::setSphereCenter(const QVector3D &sphereCenter)
{
    Q_D(QtLeapHand);
    if (d->m_sphereCenter != sphereCenter)
    {
        d->m_sphereCenter = sphereCenter;
        emit sphereCenterChanged();
    }
}

void QtLeapHand::setFist(bool fist)
{
    Q_D(QtLeapHand);
    if (d->m_isFist != fist)
    {
        d->m_isFist = fist;
        emit isFistChanged();
    }
}

} //QtLeapMotion
