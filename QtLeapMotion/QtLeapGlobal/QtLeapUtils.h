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

#ifndef QTLEAPUTILS_H
#define QTLEAPUTILS_H

#include <Leap.h>
#include <QWindow>
#include <QPointF>
#include <QScreen>
#include <QVector3D>
#include <QGuiApplication>

namespace QtLeapMotion
{

class QtLeapUtils
{
public:
    static QPointF convertNormalizedPointablePosToScreenPos(const Leap::Vector &normalizedPos);

    static QPointF convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                        const Leap::Pointable &pointable);

    static QPointF convertGlobalPosToLocalPos(QObject *container, const QPointF &globalPos);

    static QPointF convertHandPosToScreenPos(const Leap::InteractionBox &interactionBox,
                                                            const Leap::Hand &hand);

    static QVector3D convertVectorToNormalizedScreenVector(const Leap::InteractionBox &interactionBox, const Leap::Vector &rawPos);
};

} // QtLeapMotion

#endif // QTLEAPUTILS_H
