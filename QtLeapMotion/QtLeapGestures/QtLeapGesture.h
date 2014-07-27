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

#ifndef QTLEAPGESTURE_H
#define QTLEAPGESTURE_H

#include <Leap.h>

#include <QtLeapGesture.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QTLEAPMOTION_EXPORT QtLeapGesture
{
public :

    enum GestureState
    {
        GestureStarted = 1,
        GestureUpdated,
        GestureDone,
        GestureInvalid
    };

    virtual int    getId() const = 0;
    virtual void   setId(int id) = 0;
    virtual void   setState(GestureState state) = 0;
    virtual void   setState(Leap::Gesture::State state) = 0;
    virtual GestureState getState() const = 0;
    virtual void   update(const Leap::Gesture &gesture) = 0;
};

} //QtLeapMotion

//Q_DECLARE_INTERFACE(QtLeapMotion::QtLeapGesture, "org.qtproject.QtLeapMotion.QtLeapGesture/1.0")

#endif // QTLEAPGESTURE_H
