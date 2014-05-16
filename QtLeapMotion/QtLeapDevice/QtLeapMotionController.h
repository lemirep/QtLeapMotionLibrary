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

#ifndef LEAPMOTIONCONTROLLER_H
#define LEAPMOTIONCONTROLLER_H


#include <QObject>
#include "Leap.h"

namespace QtLeapMotion
{

class QtLeapMotionListener;

class QtLeapMouseHandlerInterface;
class QtLeapTouchHandlerInterface;
class QtLeapGestureHandlerInterface;
class QtLeapHandsHandlerInterface;

class QtLeapGestureListenerInterface;
class QtLeapHandsListenerInterface;
class QtLeapFingersListenerInterface;

class QtLeapMotionController : public QObject
{
    Q_OBJECT

private :
    QtLeapMotionController(QObject *parent = 0);

    static QtLeapMotionController *instance;
    QtLeapMotionListener *leapListener;
    Leap::Controller   *leapController;

public:
    ~QtLeapMotionController();

    static QtLeapMotionController *getInstance();

    void    setTouchHandler(QtLeapTouchHandlerInterface *touchHandler);
    void    setMouseHandler(QtLeapMouseHandlerInterface *mouseHandler);
    void    addGestureHandler(QtLeapGestureHandlerInterface *gestureHandler);
    void    setHandHandler(QtLeapHandsHandlerInterface *handHandler);
    void    init();

public slots:

    void    registerMouseListener(QObject *motionListener);
    void    registerTouchListener(QObject *motionListener);
    void    registerGestureListener(QtLeapGestureListenerInterface *motionListener);
    void    registerHandListener(QtLeapHandsListenerInterface*motionListener);
    void    registerFingerListener(QtLeapFingersListenerInterface *motionListener);

    void    unregisterMouseListener(QObject *motionListener);
    void    unregisterTouchListener(QObject *motionListener);
    void    unregisterGestureListener(QtLeapGestureListenerInterface *motionListener);
    void    unregisterHandListener(QtLeapHandsListenerInterface *motionListener);
    void    unregisterFingerListener(QtLeapFingersListenerInterface *motionListener);
};

} //QtLeapMotion

#endif // LEAPMOTIONCONTROLLER_H
