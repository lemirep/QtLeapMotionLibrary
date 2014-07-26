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

#include "QtLeapSwipeGesture.h"

namespace QtLeapMotion
{

class QtLeapSwipeGesturePrivate
{
public:
    QtLeapSwipeGesturePrivate(QtLeapSwipeGesture *qq)
        : m_state(QtLeapSwipeGesture::GestureInvalid)
        , m_direction(0,0,0)
        , m_position(0,0,0)
        , m_startPosition(0,0,0)
        , m_speed(0)
        , m_id(0)
        , q_ptr(qq)
    {
    }

    Q_DECLARE_PUBLIC(QtLeapSwipeGesture)

    QtLeapSwipeGesture::GestureState m_state;
    QVector3D m_direction;
    QVector3D m_position;
    QVector3D m_startPosition;
    qreal     m_speed;
    int       m_id;
    QtLeapSwipeGesture *q_ptr;
};

QtLeapSwipeGesture::QtLeapSwipeGesture(QObject *parent)
    : QObject(parent)
    , d_ptr(new QtLeapSwipeGesturePrivate(this))
{
}

QtLeapSwipeGesture::~QtLeapSwipeGesture()
{
    delete d_ptr;
}

QtLeapSwipeGesture::GestureState QtLeapSwipeGesture::getState() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_state;
}

QVector3D QtLeapSwipeGesture::getDirection() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_direction;
}

QVector3D QtLeapSwipeGesture::getPosition() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_position;
}

QVector3D QtLeapSwipeGesture::getStartPosition() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_startPosition;
}

qreal QtLeapSwipeGesture::getSpeed() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_speed;
}

int QtLeapSwipeGesture::getId() const
{
    Q_D(const QtLeapSwipeGesture);
    return d->m_id;
}

void QtLeapSwipeGesture::setId(int id)
{
    Q_D(QtLeapSwipeGesture);
    d->m_id = id;
}

void QtLeapSwipeGesture::setState(QtLeapSwipeGesture::GestureState state)
{
    Q_D(QtLeapSwipeGesture);
    if (state != d->m_state)
    {
        d->m_state = state;
        emit stateChanged();
    }
}

void QtLeapSwipeGesture::setState(Leap::Gesture::State state)
{
    switch (state)
    {
    case Leap::Gesture::STATE_UPDATE:
        this->setState(QtLeapGesture::GestureUpdated);
        break;
    case Leap::Gesture::STATE_START:
        this->setState(QtLeapGesture::GestureStarted);
        break;
    case Leap::Gesture::STATE_STOP:
        this->setState(QtLeapGesture::GestureDone);
        break;
    case Leap::Gesture::STATE_INVALID:
        this->setState(QtLeapGesture::GestureInvalid);
        break;
    }
}

void QtLeapSwipeGesture::setDirection(const QVector3D &direction)
{
    Q_D(QtLeapSwipeGesture);
    if (direction != d->m_direction)
    {
        d->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapSwipeGesture::setPosition(const QVector3D &position)
{
    Q_D(QtLeapSwipeGesture);
    if (position != d->m_position)
    {
        d->m_position = position;
        emit positionChanged();
    }
}

void QtLeapSwipeGesture::setStartPosition(const QVector3D &startPosition)
{
    Q_D(QtLeapSwipeGesture);
    if (startPosition != d->m_startPosition)
    {
        d->m_startPosition = startPosition;
        emit startPositionChanged();
    }
}

void QtLeapSwipeGesture::setSpeed(qreal speed)
{
    Q_D(QtLeapSwipeGesture);
    if (speed != d->m_speed)
    {
        d->m_speed = speed;
        emit speedChanged();
    }
}

void QtLeapSwipeGesture::update(const Leap::Gesture &gesture)
{
    Leap::SwipeGesture swipeGesture = static_cast<Leap::SwipeGesture>(gesture);

    this->setId(swipeGesture.id());
    this->setSpeed(swipeGesture.speed());
    this->setState(swipeGesture.state());
    this->setDirection(QVector3D(swipeGesture.direction().x,
                                 swipeGesture.direction().y,
                                 swipeGesture.direction().z));
    this->setPosition(QVector3D(swipeGesture.position().x,
                                swipeGesture.position().y,
                                swipeGesture.position().z));
    this->setStartPosition(QVector3D(swipeGesture.startPosition().x,
                                     swipeGesture.startPosition().y,
                                     swipeGesture.startPosition().z));
}

QtLeapSwipeGesture *QtLeapSwipeGesture::fromLeapGesture(const Leap::Gesture &gesture)
{
    QtLeapSwipeGesture *swipeGesture = new QtLeapSwipeGesture();
    swipeGesture->update(gesture);
    return swipeGesture;
}

} //QtLeapMotion
