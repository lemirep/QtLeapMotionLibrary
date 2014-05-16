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

#include "QtLeapScreenTapGesture.h"

namespace QtLeapMotion
{

QtLeapScreenTapGesture::QtLeapScreenTapGesture(QObject *parent) :
    QtLeapTapGesture(parent)
{
}

void QtLeapScreenTapGesture::update(const Leap::Gesture &gesture)
{
    Leap::ScreenTapGesture tapGesture = static_cast<Leap::ScreenTapGesture>(gesture);
    this->setId(tapGesture.id());
    this->setState(gesture.state());
    this->setDirection(QVector3D(tapGesture.direction().x,
                               tapGesture.direction().y,
                               tapGesture.direction().x));
    this->setPosition(QVector3D(tapGesture.position().x,
                                tapGesture.position().y,
                                tapGesture.position().z));
    this->setState(tapGesture.state());
}

QtLeapScreenTapGesture *QtLeapScreenTapGesture::fromLeapGesture(const Leap::Gesture &gesture)
{
    QtLeapScreenTapGesture *tapGesture = new QtLeapScreenTapGesture();
    tapGesture->update(gesture);
    return tapGesture;
}

} // QtLeapMotion
