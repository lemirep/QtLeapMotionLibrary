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

#ifndef QTLEAPGESTURELISTENERINTERFACE_H
#define QTLEAPGESTURELISTENERINTERFACE_H

#include <QtLeapGlobal.h>
#include <QObject>

namespace QtLeapMotion
{

class QtLeapGesture;

class QTLEAPMOTION_EXPORT QtLeapGestureListenerInterface
{
public :
    virtual ~QtLeapGestureListenerInterface() {}
    virtual void    updateGestures(QList<QObject *> gestures) = 0;
};

} // QtLeapMotion

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(QtLeapMotion::QtLeapGestureListenerInterface, "org.qtproject.QtLeapMotion.QtLeapGestureListenerInterface/1.0")

QT_END_NAMESPACE

#endif // QTLEAPGESTURELISTENERINTERFACE_H
