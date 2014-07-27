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

#ifndef QTLEAPHANDSHANDLERINTERFACE_H
#define QTLEAPHANDSHANDLERINTERFACE_H

#include <QtLeapGlobal.h>
#include <QtLeapMotionHandler.h>

namespace QtLeapMotion
{

class QtLeapHandsListenerInterface;

class QTLEAPMOTION_EXPORT QtLeapHandsHandlerInterface : public QtLeapMotionHandler
{
    // QtLeapMotionHandler interface
public:
    virtual ~QtLeapHandsHandlerInterface() {}
    virtual void onInit(const Leap::Controller &controller) = 0;
    virtual void setMotionListeners(QList<QtLeapHandsListenerInterface *> listener) = 0;
    virtual void onFrame(const Leap::Frame &frame) = 0;
    virtual void onCleanup() = 0;
};

}

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(QtLeapMotion::QtLeapHandsHandlerInterface, "org.qtproject.QtLeapMotion.QtLeapHandsHandlerInterface/1.0")

QT_END_NAMESPACE

#endif // QTLEAPHANDSHANDLERINTERFACE_H
