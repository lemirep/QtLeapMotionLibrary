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

#ifndef QTLEAPTOOL_H
#define QTLEAPTOOL_H

#include <QObject>
#include <QtLeapGlobal.h>
#include <QtLeapPointable.h>

namespace Leap
{
class Pointable;
}

namespace QtLeapMotion
{

class QtLeapPointable;

class QTLEAPMOTION_EXPORT QtLeapTool : public QtLeapPointable
{
    Q_OBJECT
public:
    QtLeapTool(Leap::Pointable *pointable, QtLeapHand *parent);
    virtual ~QtLeapTool();

    void update(Leap::Pointable *pointable) Q_DECL_OVERRIDE;
};

}

#endif // QTLEAPTOOL_H
