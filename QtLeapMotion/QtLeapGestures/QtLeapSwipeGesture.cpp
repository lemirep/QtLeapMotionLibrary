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

QtLeapSwipeGesture::QtLeapSwipeGesture(QObject *parent) :
    QObject(parent),
    m_state(QtLeapSwipeGesture::GestureInvalid),
    m_direction(0,0,0),
    m_position(0,0,0),
    m_startPosition(0,0,0),
    m_speed(0),
    m_id(0)

{
}

QtLeapSwipeGesture::GestureState QtLeapSwipeGesture::getState() const
{
    return this->m_state;
}

QVector3D QtLeapSwipeGesture::getDirection() const
{
    return this->m_direction;
}

QVector3D QtLeapSwipeGesture::getPosition() const
{
    return this->m_position;
}

QVector3D QtLeapSwipeGesture::getStartPosition() const
{
    return this->m_startPosition;
}

qreal QtLeapSwipeGesture::getSpeed() const
{
    return this->m_speed;
}

int QtLeapSwipeGesture::getId() const
{
    return this->m_id;
}

void QtLeapSwipeGesture::setId(int id)
{
    this->m_id = id;
}

void QtLeapSwipeGesture::setState(QtLeapSwipeGesture::GestureState state)
{
    if (state != this->m_state)
    {
        this->m_state = state;
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
    if (direction != this->m_direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapSwipeGesture::setPosition(const QVector3D &position)
{
    if (position != this->m_position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void QtLeapSwipeGesture::setStartPosition(const QVector3D &startPosition)
{
    if (startPosition != this->m_startPosition)
    {
        this->m_startPosition = startPosition;
        emit startPositionChanged();
    }
}

void QtLeapSwipeGesture::setSpeed(qreal speed)
{
    if (speed != this->m_speed)
    {
        this->m_speed = speed;
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
