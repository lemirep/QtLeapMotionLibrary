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

#include <QCoreApplication>
#include "QtLeapMotionQQuickView.h"

#include "QtLeapMotionController.h"

#include "DefaultQtLeapHandsHandler.h"
#include "DefaultQtLeapMouseHandler.h"
#include "DefaultQtLeapTouchHandler.h"
#include "DefaultQtLeapCircleGestureHandler.h"
#include "DefaultQtLeapSwipeGestureHandler.h"
#include "DefaultQtLeapTapGestureHandler.h"

#include "CircleLeapGestureArea.h"
#include "KeyTapLeapGestureArea.h"
#include "ScreenTapLeapGestureArea.h"
#include "SwipeLeapGestureArea.h"

#include "HandsMotionArea.h"
#include "FingersMotionArea.h"

#include "QtLeapHand.h"
#include "QtLeapFinger.h"

namespace QtLeapMotion
{

QtLeapMotionQQuickView::QtLeapMotionQQuickView() :
    QQuickView(),
    touchEnabled(false),
    mouseEnabled(false)
{
    qmlRegisterUncreatableType<QtLeapMotion::AbstractGestureArea>("QtLeapMotion", 2, 0, "AbstractGestureArea", "");
    qmlRegisterType<QtLeapMotion::CircleLeapGestureArea>("QtLeapMotion", 2, 0, "CircleGestureArea");
    qmlRegisterType<QtLeapMotion::KeyTapLeapGestureArea>("QtLeapMotion", 2, 0, "KeyTapGestureArea");
    qmlRegisterType<QtLeapMotion::ScreenTapLeapGestureArea>("QtLeapMotion", 2, 0, "ScreenTapGestureArea");
    qmlRegisterType<QtLeapMotion::SwipeLeapGestureArea>("QtLeapMotion", 2, 0, "SwipeGestureArea");
    qmlRegisterType<QtLeapMotion::HandsMotionArea>("QtLeapMotion", 2, 0, "HandsMotionArea");
    qmlRegisterType<QtLeapMotion::FingersMotionArea>("QtLeapMotion", 2, 0, "FingersMotionArea");
    qmlRegisterUncreatableType<QtLeapMotion::QtLeapSwipeGesture>("QtLeapMotion", 2, 0, "QtLeapSwipeGesture", "");
    qmlRegisterUncreatableType<QtLeapMotion::QtLeapHand>("QtLeapMotion", 2, 0, "Hand", "");
    qmlRegisterUncreatableType<QtLeapMotion::QtLeapFinger>("QtLeapMotion", 2, 0, "Finger", "");
    //    qmlRegisterUncreatableType<QtLeapMotion::QtLeapTapGesture>("QtLeapMotion", 2, 0, "QtLeapTapGesture", "");
//    qmlRegisterUncreatableType<QtLeapMotion::QtLeapScreenTapGesture>("QtLeapMotion", 2, 0, "QtLeapScreenTapGesture", "");
//    qmlRegisterUncreatableType<QtLeapMotion::QtLeapCircleGesture>("QtLeapMotion", 2, 0, "QtLeapCircleGesture", "");


    this->leapController = QtLeapMotion::QtLeapMotionController::getInstance();

    // Set Handlers Handler
    this->leapController->setHandHandler(new QtLeapMotion::DefaultQtLeapHandsHandler(this->leapController));
    this->leapController->setMouseHandler(new QtLeapMotion::DefaultQtLeapMouseHandler(this->leapController));
    this->leapController->setTouchHandler(new QtLeapMotion::DefaultQtLeapTouchHandler(this->leapController));
    this->leapController->addGestureHandler(new QtLeapMotion::DefaultQtLeapCircleGestureHandler(this->leapController));
    this->leapController->addGestureHandler(new QtLeapMotion::DefaultQtLeapSwipeGestureHandler(this->leapController));
    this->leapController->addGestureHandler(new QtLeapMotion::DefaultQtLeapTapGestureHandler(this->leapController));


    this->leapController->init();
}

QtLeapMotionQQuickView::~QtLeapMotionQQuickView()
{
    delete this->leapController;
}

void QtLeapMotionQQuickView::showView()
{
    this->show();
}

void QtLeapMotionQQuickView::setSource(const QUrl &source)
{
    QQuickView::setSource(source);
}

void QtLeapMotionQQuickView::setLeapTouchEnabled(bool touchEnabled)
{
    this->touchEnabled = touchEnabled;
    if (this->touchEnabled)
        this->leapController->registerTouchListener(this);
}

void QtLeapMotionQQuickView::setLeapMouseEnabled(bool mouseEnabled)
{
    this->mouseEnabled = mouseEnabled;
    if (this->mouseEnabled)
        this->leapController->registerMouseListener(this);
}

} // QtLeapMotion
