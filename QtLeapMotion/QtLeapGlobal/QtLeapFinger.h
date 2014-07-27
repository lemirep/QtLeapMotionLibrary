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

#ifndef QTLEAPMOTION_LEAPFINGER_H__
#define QTLEAPMOTION_LEAPFINGER_H__

#include <QObject>
#include <QtLeapPointable.h>
#include "QtLeapGlobal.h"

namespace Leap
{
class Pointable;
}

namespace QtLeapMotion
{
class QtLeapPointable;

class QTLEAPMOTION_EXPORT QtLeapFinger : public QtLeapPointable
{
    Q_OBJECT
public :
    QtLeapFinger(Leap::Pointable *pointable, QtLeapHand *parent);
    ~QtLeapFinger();

    QtLeapFinger *fromLeapPointable(Leap::Pointable *pointable);
    void update(Leap::Pointable *pointable) Q_DECL_OVERRIDE;
};

}

#endif //__LEAPFINGER_H__
