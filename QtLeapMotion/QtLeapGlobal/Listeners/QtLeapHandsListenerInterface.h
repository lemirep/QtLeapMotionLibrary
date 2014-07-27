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

#ifndef QTLEAPHANDSLISTENERINTERFACE_H
#define QTLEAPHANDSLISTENERINTERFACE_H

#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QtLeapHand;

class QTLEAPMOTION_EXPORT QtLeapHandsListenerInterface
{
public:
    virtual ~QtLeapHandsListenerInterface() {}
    virtual void    updateHands(QList<QtLeapHand*> handsList) = 0;
};

} // QtLeapMotion

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(QtLeapMotion::QtLeapHandsListenerInterface, "org.qtproject.QtLeapMotion.QtLeapHandsListenerInterface/1.0")

QT_END_NAMESPACE

#endif // QTLEAPHANDSLISTENERINTERFACE_H
