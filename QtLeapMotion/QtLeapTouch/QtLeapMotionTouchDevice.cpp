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
#include "QtLeapMotionTouchDevice.h"

namespace QtLeapMotion
{

QtLeapMotionTouchDevice * QtLeapMotionTouchDevice::instance = NULL;

QtLeapMotionTouchDevice *QtLeapMotionTouchDevice::getInstance()
{
    if (QtLeapMotionTouchDevice::instance == NULL)
        QtLeapMotionTouchDevice::instance = new QtLeapMotionTouchDevice();
    return QtLeapMotionTouchDevice::instance;
}

QtLeapMotionTouchDevice::QtLeapMotionTouchDevice() : QTouchDevice()
{
}

QtLeapMotionTouchDevice::~QtLeapMotionTouchDevice()
{
    QtLeapMotionTouchDevice::instance = NULL;
}

QTouchDevice::Capabilities QtLeapMotionTouchDevice::capabilities() const
{
    return (QTouchDevice::Position|QTouchDevice::Pressure|QTouchDevice::NormalizedPosition);
}

QTouchDevice::DeviceType QtLeapMotionTouchDevice::type() const
{
    return QTouchDevice::TouchScreen;
}

QString QtLeapMotionTouchDevice::name() const
{
    return QString("Leap Motion");
}

} // QtLeapMotion
