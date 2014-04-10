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

#ifndef LEAPMOTIONTOUCHDEVICE_H
#define LEAPMOTIONTOUCHDEVICE_H

#include <QTouchDevice>

namespace QtLeapMotion
{

class QtLeapMotionTouchDevice : public QTouchDevice
{
public:
    static QtLeapMotionTouchDevice *getInstance();
    ~QtLeapMotionTouchDevice();

    QTouchDevice::Capabilities capabilities() const;
    QTouchDevice::DeviceType type() const;
    QString name() const;

private:
    static QtLeapMotionTouchDevice *instance;
    QtLeapMotionTouchDevice();

};

}

#endif // LEAPMOTIONTOUCHDEVICE_H
