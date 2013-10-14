/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
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

#include "LeapMotionTouchDevice.h"

LeapMotionTouchDevice * LeapMotionTouchDevice::instance = NULL;

LeapMotionTouchDevice *LeapMotionTouchDevice::getInstance()
{
    if (LeapMotionTouchDevice::instance == NULL)
        LeapMotionTouchDevice::instance = new LeapMotionTouchDevice();
    return LeapMotionTouchDevice::instance;
}

LeapMotionTouchDevice::~LeapMotionTouchDevice()
{
    LeapMotionTouchDevice::instance = NULL;
}

QTouchDevice::Capabilities LeapMotionTouchDevice::capabilities() const
{
    return (QTouchDevice::Position|QTouchDevice::Pressure|QTouchDevice::NormalizedPosition);
}

QTouchDevice::DeviceType LeapMotionTouchDevice::type() const
{
    return QTouchDevice::TouchScreen;
}

QString LeapMotionTouchDevice::name() const
{
    return QString("Leap Motion");
}

LeapMotionTouchDevice::LeapMotionTouchDevice() : QTouchDevice()
{
}

