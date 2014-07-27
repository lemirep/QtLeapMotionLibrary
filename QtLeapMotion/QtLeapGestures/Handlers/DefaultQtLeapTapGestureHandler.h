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

#ifndef QTLEAPTAPGESTUREHANDLER_H
#define QTLEAPTAPGESTUREHANDLER_H

#include <QObject>
#include <QHash>
#include <QtLeapGlobal.h>
#include <QtLeapGestureHandlerInterface.h>

namespace QtLeapMotion
{

class QtLeapGesture;

class QtLeapGestureListenerInterface;

class QTLEAPMOTION_EXPORT DefaultQtLeapTapGestureHandler
        :
        public QObject,
        public QtLeapGestureHandlerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapMotionHandler)
    Q_INTERFACES(QtLeapMotion::QtLeapGestureHandlerInterface)
public:

    DefaultQtLeapTapGestureHandler(QObject *parent = 0);
    virtual ~DefaultQtLeapTapGestureHandler();
    // QtLeapMotionHandler interface
public:
    void onInit(const Leap::Controller &controller);
    void setMotionListeners(QList<QtLeapGestureListenerInterface *> listener);
    void onFrame(const Leap::Frame &frame);
    void onCleanup();

private:
    QList<QtLeapGestureListenerInterface *> listeners;
    QHash<int, QObject *> kGestures;
    QHash<int, QObject *> sGestures;

};

} // QtLeapMotion

#endif // QTLEAPTAPGESTUREHANDLER_H
