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

#ifndef QTLEAPSCREENTAPGESTURE_H
#define QTLEAPSCREENTAPGESTURE_H

#include <QtLeapTapGesture.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QTLEAPMOTION_EXPORT QtLeapScreenTapGesture : public QtLeapTapGesture
{
    Q_OBJECT
public:
    QtLeapScreenTapGesture(QObject *parent = 0);

    // QtLeapGesture interface
    void update(const Leap::Gesture &gesture);
    static QtLeapScreenTapGesture *fromLeapGesture(const Leap::Gesture &gesture);
};

}

#endif // QTLEAPSCREENTAPGESTURE_H
