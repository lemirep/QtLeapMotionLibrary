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

#ifndef DEFAULTQTLEAPTOUCHHANDLER_H
#define DEFAULTQTLEAPTOUCHHANDLER_H

#include <QObject>
#include <QTouchEvent>
#include <QtLeapMotionTouchDevice.h>
#include <QtLeapGlobal.h>
#include <QtLeapTouchHandlerInterface.h>

namespace QtLeapMotion
{

class DefaultQtLeapTouchHandler :
        public QObject,
        public QtLeapTouchHandlerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapMotionHandler)
    Q_INTERFACES(QtLeapMotion::QtLeapTouchHandlerInterface)
public:
    DefaultQtLeapTouchHandler(QObject *parent = 0);
    virtual ~DefaultQtLeapTouchHandler();
    // QtLeapMotionHandler interface
public:
    void onInit(const Leap::Controller &controller);
    void setMotionListeners(QList<QObject *> listener);
    void onFrame(const Leap::Frame &frame);
    void onCleanup();

private:
    QList<QTouchEvent::TouchPoint> touchPoints;
    QList<QObject*> listeners;

};

}

#endif // DEFAULTQTLEAPTOUCHHANDLER_H
