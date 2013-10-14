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
#include "LeapMotionTouchDevice.h"
#include "LeapMotionServiceUserInterface.h"
#include "Leap.h"
#include <qmath.h>

class LeapMotionListener : public QObject, public Leap::Listener
{
    Q_OBJECT

public :
    LeapMotionListener();
    ~LeapMotionListener();

private :
    QList<QObject*> inputListeners;
    QList<QObject*> gesturesListeners;
    QScreen         *primaryScreen;
    QHash<Leap::Gesture::State, Services::LeapMotionServiceGestureUserInterface::GestureState> gestureStateMatcher;
    int savedMousePointableId;

    QList<QTouchEvent::TouchPoint> touchPoints;
//    QList<QWindowSystemInterface::TouchPoint> touchPoints;
    bool                           mousePressed;
    QPoint                         previousPos;
    QHash<Leap::Gesture::Type, void (LeapMotionListener::*)(const Leap::Gesture &gesture, const Leap::Frame &frame)> gestureHandlers;

    void swipeGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void circleGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void keyTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void screenTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);

    void handleMouseEvents(const Leap::Frame &frame);
    void handleTouchEvents(const Leap::Frame &frame);
    QPointF convertHandPosToScreenPos(const Leap::InteractionBox &interactionBox,
                                      const Leap::Hand &hand);
    QPointF convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                        const Leap::Pointable &pointable);
    QPointF convertPointablePosToScreenPos(const Leap::Vector &normalizedPos);
    QPointF convertGlobalPosToLocalPos(QObject *container, const QPointF &globalPos);
    QVector3D convertVectorToNormalizedScreenVector(const Leap::InteractionBox &interactionBox,
                                        const Leap::Vector &rawPos);
public:
    void onInit(const Leap::Controller &);
    void onConnect(const Leap::Controller &);
    void onDisconnect(const Leap::Controller &);
    void onExit(const Leap::Controller &);
    void onFrame(const Leap::Controller &);
    void onFocusGained(const Leap::Controller &);
    void onFocusLost(const Leap::Controller &);

public:
    void    addInputListener(QObject *target);
    void    removeInputListener(QObject *target);
    void    addGestureListener(QObject *listener);
    void    removeGestureListener(QObject *listener);
};

#endif // LEAPMOTIONLISTENER_H
