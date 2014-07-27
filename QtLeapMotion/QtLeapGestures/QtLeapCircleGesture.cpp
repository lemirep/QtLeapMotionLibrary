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

#include "QtLeapCircleGesture.h"
#include <qmath.h>

namespace QtLeapMotion
{

class QtLeapCircleGesturePrivate
{
public:
    QtLeapCircleGesturePrivate(QtLeapCircleGesture *qq)
        : m_id(0)
        , m_center(0,0,0)
        , m_normal(0,0,0)
        , m_radius(0)
        , m_turns(0)
        , m_state(QtLeapCircleGesture::GestureInvalid)
        , m_clockwise(true)
        , q_ptr(qq)
    {
    }

    Q_DECLARE_PUBLIC(QtLeapCircleGesture)

    int m_id;
    QVector3D m_center;
    QVector3D m_normal;
    qreal m_radius;
    qreal m_turns;
    QtLeapGesture::GestureState m_state;
    bool m_clockwise;
    QtLeapCircleGesture *q_ptr;
};

QtLeapCircleGesture::QtLeapCircleGesture(QObject *parent)
    : QObject(parent)
    , d_ptr(new QtLeapCircleGesturePrivate(this))
{
}

QtLeapCircleGesture::~QtLeapCircleGesture()
{
    delete d_ptr;
}

QtLeapCircleGesture::GestureState QtLeapCircleGesture::getState() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_state;
}

QVector3D QtLeapCircleGesture::getCenter() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_center;
}

QVector3D QtLeapCircleGesture::getNormal() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_normal;
}

qreal QtLeapCircleGesture::getRadius() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_radius;
}

qreal QtLeapCircleGesture::getTurns() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_turns;
}

bool QtLeapCircleGesture::getClockwise() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_clockwise;
}

int QtLeapCircleGesture::getId() const
{
    Q_D(const QtLeapCircleGesture);
    return d->m_id;
}

void QtLeapCircleGesture::setId(int id)
{
    Q_D(QtLeapCircleGesture);
    d->m_id = id;
}

void QtLeapCircleGesture::setClockwise(bool clockwise)
{
    Q_D(QtLeapCircleGesture);
    if (clockwise != d->m_clockwise)
    {
        d->m_clockwise = clockwise;
        emit clockwiseChanged();
    }
}

void QtLeapCircleGesture::setState(QtLeapCircleGesture::GestureState state)
{
    Q_D(QtLeapCircleGesture);
    if (state != d->m_state)
    {
        d->m_state = state;
        emit stateChanged();
    }
}

void QtLeapCircleGesture::setState(Leap::Gesture::State state)
{
    switch (state)
    {
    case Leap::Gesture::STATE_UPDATE:
        this->setState(QtLeapGesture::GestureUpdated);
        break;
    case Leap::Gesture::STATE_INVALID:
        this->setState(QtLeapGesture::GestureInvalid);
        break;
    case Leap::Gesture::STATE_START:
        this->setState(QtLeapGesture::GestureStarted);
        break;
    case Leap::Gesture::STATE_STOP:
        this->setState(QtLeapGesture::GestureDone);
        break;
    }
}

void QtLeapCircleGesture::setCenter(const QVector3D &center)
{
    Q_D(QtLeapCircleGesture);
    if (center != d->m_center)
    {
        d->m_center = center;
        emit centerChanged();
    }
}

void QtLeapCircleGesture::setNormal(const QVector3D &normal)
{
    Q_D(QtLeapCircleGesture);
    if (normal != d->m_normal)
    {
        d->m_normal = normal;
        emit normalChanged();
    }
}

void QtLeapCircleGesture::setRadius(qreal radius)
{
    Q_D(QtLeapCircleGesture);
    if (radius != d->m_radius)
    {
        d->m_radius = radius;
        emit radiusChanged();
    }
}

void QtLeapCircleGesture::setTurns(qreal turns)
{
    Q_D(QtLeapCircleGesture);
    if (turns != d->m_turns)
    {
        d->m_turns = turns;
        emit turnsChanged();
    }
}

QtLeapCircleGesture *QtLeapCircleGesture::fromLeapGesture(const Leap::Gesture &gesture)
{
    QtLeapCircleGesture *circleGesture = new QtLeapCircleGesture();
    circleGesture->update(gesture);
    return circleGesture;
}

void QtLeapCircleGesture::update(const Leap::Gesture &gesture)
{
    Leap::CircleGesture leapGesture = static_cast<Leap::CircleGesture>(gesture);

    this->setId(leapGesture.id());
    this->setState(leapGesture.state());
    this->setCenter(QVector3D(leapGesture.center().x,
                              leapGesture.center().y,
                              leapGesture.center().z));
    this->setRadius(leapGesture.radius());
    this->setNormal(QVector3D(leapGesture.normal().x,
                              leapGesture.normal().y,
                              leapGesture.normal().z));
    this->setTurns(leapGesture.progress());
    this->setClockwise(leapGesture.pointable().direction().angleTo(leapGesture.normal()) <= M_PI / 2);
    this->setState(leapGesture.state());
}

} //QtLeapMotion
