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

#include "QtLeapUtils.h"

namespace QtLeapMotion
{

QPointF QtLeapUtils::convertNormalizedPointablePosToScreenPos(const Leap::Vector &normalizedPos)
{
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    return QPointF(normalizedPos.x * primaryScreen->geometry().width(),
                   (1 - normalizedPos.y) * primaryScreen->geometry().height());
}

QPointF QtLeapUtils::convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox, const Leap::Pointable &pointable)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(pointable.stabilizedTipPosition());
    return QtLeapUtils::convertNormalizedPointablePosToScreenPos(normalizedPos);
}

QPointF QtLeapUtils::convertGlobalPosToLocalPos(QObject *container, const QPointF &globalPos)
{
    QWindow *win = NULL;
    if ((win = qobject_cast<QWindow *>(container)) != NULL)
        return QPointF(win->mapFromGlobal(globalPos.toPoint()));
    return globalPos;
}

QVector3D QtLeapUtils::convertVectorToNormalizedScreenVector(const Leap::InteractionBox &interactionBox, const Leap::Vector &rawPos)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(rawPos);
    QPointF screenPos = QtLeapUtils::convertNormalizedPointablePosToScreenPos(normalizedPos);
    QVector3D ret = QVector3D(screenPos.x(), screenPos.y(), normalizedPos.z);
    return ret;
}

} // QtLeapMotion
