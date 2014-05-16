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

#include "QtLeapMotionController.h"
#include "QtLeapMotionListener.h"
#include "QtLeapHandsHandlerInterface.h"
#include "QtLeapGestureHandlerInterface.h"
#include "QtLeapMouseHandlerInterface.h"
#include "QtLeapTouchHandlerInterface.h"
#include "QtLeapGestureListenerInterface.h"
#include "QtLeapHandsListenerInterface.h"
#include "QtLeapFingersListenerInterface.h"

namespace QtLeapMotion
{

QtLeapMotionController * QtLeapMotionController::instance = NULL;

QtLeapMotionController::QtLeapMotionController(QObject *parent) : QObject(parent)
{
    this->leapController = new Leap::Controller();
    this->leapListener = new QtLeapMotionListener();
}

QtLeapMotionController::~QtLeapMotionController()
{
    this->leapController->removeListener(*this->leapListener);
    delete this->leapListener;
    delete this->leapController;
    QtLeapMotionController::instance = NULL;
}

QtLeapMotionController *QtLeapMotionController::getInstance()
{
    if (QtLeapMotionController::instance == NULL)
        QtLeapMotionController::instance = new QtLeapMotionController();
    return QtLeapMotionController::instance;
}

void QtLeapMotionController::setTouchHandler(QtLeapTouchHandlerInterface *handler)
{
    this->leapListener->setTouchHandler(handler);
}

void QtLeapMotionController::setMouseHandler(QtLeapMouseHandlerInterface  *handler)
{
    this->leapListener->setMouseHandler(handler);
}

void QtLeapMotionController::addGestureHandler(QtLeapGestureHandlerInterface *handler)
{
    this->leapListener->addGestureHandler(handler);
}

void QtLeapMotionController::setHandHandler(QtLeapHandsHandlerInterface *handler)
{
    this->leapListener->setHandHandler(handler);
}

void QtLeapMotionController::init()
{
    // ADD LISTENER TO LEAP CONTROLLER
    this->leapController->addListener(*this->leapListener);
}

void QtLeapMotionController::registerMouseListener(QObject *listener)
{
    this->leapListener->registerMouseListener(listener);
}

void QtLeapMotionController::registerTouchListener(QObject *listener)
{
    this->leapListener->registerTouchListener(listener);
}

void QtLeapMotionController::registerGestureListener(QtLeapGestureListenerInterface *listener)
{
    this->leapListener->registerGestureListener(listener);
}

void QtLeapMotionController::registerHandListener(QtLeapHandsListenerInterface *listener)
{
    this->leapListener->registerHandListener(listener);
}

void QtLeapMotionController::registerFingerListener(QtLeapFingersListenerInterface *motionListener)
{
    this->leapListener->registerFingerListener(motionListener);
}

void QtLeapMotionController::unregisterMouseListener(QObject *listener)
{
    this->leapListener->unregisterMouseListener(listener);
}

void QtLeapMotionController::unregisterTouchListener(QObject *listener)
{
    this->leapListener->unregisterTouchListener(listener);
}

void QtLeapMotionController::unregisterGestureListener(QtLeapGestureListenerInterface *listener)
{
    this->leapListener->unregisterGestureListener(listener);
}

void QtLeapMotionController::unregisterHandListener(QtLeapHandsListenerInterface *listener)
{
    this->leapListener->unregisterHandListener(listener);
}

void QtLeapMotionController::unregisterFingerListener(QtLeapFingersListenerInterface *motionListener)
{
    this->leapListener->unregisterFingerListener(motionListener);
}

} // QtLeapMotion
