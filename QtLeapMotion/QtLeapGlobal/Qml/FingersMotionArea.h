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

#ifndef FINGERSMOTIONAREA_H
#define FINGERSMOTIONAREA_H

#include <QQuickItem>
#include <QtLeapFingersListenerInterface.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QtLeapFinger;

class QTLEAPMOTION_EXPORT FingersMotionArea :
        public QQuickItem,
        public QtLeapFingersListenerInterface
{
    Q_OBJECT
    Q_INTERFACES(QtLeapMotion::QtLeapFingersListenerInterface)
public:
    FingersMotionArea(QQuickItem *parent = 0);

    // Have a bounding box 3d to dected if Finger is in area

    void updateFingers(QList<QtLeapFinger *> fingersList);
};

} // QtLeapMotion

#endif // FINGERSMOTIONAREA_H
