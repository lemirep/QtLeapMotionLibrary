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

#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include <QObject>
#include <QList>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QHash>
#include <QQuickItem>
#include "Leap.h"
#include <qmath.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QtLeapMouseHandlerInterface;
class QtLeapTouchHandlerInterface;
class QtLeapGestureHandlerInterface;
class QtLeapHandsHandlerInterface;

class QtLeapGestureListenerInterface;
class QtLeapHandsListenerInterface;
class QtLeapFingersListenerInterface;

class QTLEAPMOTION_EXPORT QtLeapMotionListener : public QObject, public Leap::Listener
{
    Q_OBJECT

public :
    QtLeapMotionListener();
    ~QtLeapMotionListener();

private :

//    void handleHandEvents(const Leap::Frame &frame);

    QPointF convertHandPosToScreenPos(const Leap::InteractionBox &interactionBox,
                                      const Leap::Hand &hand);
    QVector3D convertVectorToNormalizedScreenVector(const Leap::InteractionBox &interactionBox,
                                        const Leap::Vector &rawPos);
public:
    void    onInit(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onConnect(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onDisconnect(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onExit(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onFrame(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onFocusGained(const Leap::Controller &) Q_DECL_OVERRIDE;
    void    onFocusLost(const Leap::Controller &) Q_DECL_OVERRIDE;

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

    void    setTouchHandler(QtLeapTouchHandlerInterface *touchHandler);
    void    setMouseHandler(QtLeapMouseHandlerInterface *mouseHandler);
    void    addGestureHandler(QtLeapGestureHandlerInterface *gestureHandler);
    void    setHandHandler(QtLeapHandsHandlerInterface *handHandler);

private:
    QtLeapTouchHandlerInterface *touchHandler;
    QtLeapMouseHandlerInterface *mouseHandler;
    QtLeapHandsHandlerInterface *handHandler;
    QList<QtLeapGestureHandlerInterface *> gestureHandlers;

    QList<QObject*> mouseListeners;
    QList<QObject*> touchListeners;
    QList<QtLeapHandsListenerInterface*> handListeners;
    QList<QtLeapFingersListenerInterface*> fingerListeners;
    QList<QtLeapGestureListenerInterface*> gestureListeners;
};

}


#endif // LEAPMOTIONLISTENER_H
