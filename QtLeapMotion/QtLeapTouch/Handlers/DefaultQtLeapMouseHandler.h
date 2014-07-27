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

#ifndef DEFAULTQTLEAPMOUSEHANDLER_H
#define DEFAULTQTLEAPMOUSEHANDLER_H

#include <QObject>
#include <QCursor>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QtLeapMouseHandlerInterface.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QTLEAPMOTION_EXPORT DefaultQtLeapMouseHandler
        :
        public QObject,
        public QtLeapMouseHandlerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapMotionHandler)
    Q_INTERFACES(QtLeapMotion::QtLeapMouseHandlerInterface)
public:
    DefaultQtLeapMouseHandler(QObject *parent = 0);
    virtual ~DefaultQtLeapMouseHandler();

    // QtLeapMotionHandler interface
public:
    void onInit(const Leap::Controller &controller);
    void setMotionListeners(QList<QObject *> listener);
    void onFrame(const Leap::Frame &frame);
    void onCleanup();

private :
    int                   savedMousePointableId;
    bool                           mousePressed;
    QPoint                          previousPos;
    QList<QObject *>                listeners;

};

} // QtLeapMotion

#endif // DEFAULTQTLEAPMOUSEHANDLER_H
