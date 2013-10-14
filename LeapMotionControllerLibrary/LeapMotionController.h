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

#ifndef LEAPMOTIONCONTROLLER_H
#define LEAPMOTIONCONTROLLER_H


#include <QObject>
#include "Leap.h"
#include "LeapMotionListener.h"

class LeapMotionController : public QObject
{
    Q_OBJECT

private :
    LeapMotionController(QObject *parent = 0);

    static LeapMotionController *instance;
    LeapMotionListener *leapListener;
    Leap::Controller   *leapController;

public:
    ~LeapMotionController();

    static LeapMotionController *getInstance();

public slots:
    void    registerTargetListenerToLeapMotionInputs(QObject *listener);
    void    registerTargetListenerToLeapMotionGestures(QObject *listener);
    void    unregisterTargetListenerFromLeapMotionInputs(QObject *listener);
    void    unregisterTargetListenerFromLeapMotionGestures(QObject *listener);
};

#endif // LEAPMOTIONCONTROLLER_H
