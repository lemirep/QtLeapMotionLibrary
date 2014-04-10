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

#include "QtLeapTapGesture.h"

namespace QtLeapMotion
{

QtLeapTapGesture::QtLeapTapGesture(QObject *parent) :
    QObject(parent),
    m_id(-1),
    m_direction(0, 0, 0),
    m_position(0, 0, 0),
    m_state(GestureInvalid)
{
}

int QtLeapTapGesture::getId() const
{
    return this->m_id;
}

QVector3D QtLeapTapGesture::getDirection() const
{
    return this->m_direction;
}

QVector3D QtLeapTapGesture::getPosition() const
{
    return this->m_position;
}

QtLeapTapGesture::GestureState QtLeapTapGesture::getState() const
{
    return this->m_state;
}

void QtLeapTapGesture::setId(int id)
{
    this->m_id = id;
}

void QtLeapTapGesture::setPosition(const QVector3D position)
{
    if (position != this->m_position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void QtLeapTapGesture::setDirection(const QVector3D direction)
{
    if (direction != this->m_direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void QtLeapTapGesture::setState(QtLeapTapGesture::GestureState state)
{
    if (this->m_state != state)
    {
        this->m_state = state;
        emit stateChanged();
    }
}

void QtLeapTapGesture::setState(Leap::Gesture::State state)
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

} // QtLeapMotion
