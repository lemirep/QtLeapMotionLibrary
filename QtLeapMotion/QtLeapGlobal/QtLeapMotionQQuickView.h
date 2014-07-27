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

#ifndef __LEAPMOTIONQQUICKVIEW_H_
#define __LEAPMOTIONQQUICKVIEW_H_

#include <QtQuick/QQuickView>
#include "QtLeapGlobal.h"

namespace QtLeapMotion
{

class QtLeapMotionController;

class QTLEAPMOTION_EXPORT QtLeapMotionQQuickView : public QQuickView
{
    Q_OBJECT

private:
    bool touchEnabled;
    bool mouseEnabled;
    QtLeapMotionController *leapController;

public :
    QtLeapMotionQQuickView();
    ~QtLeapMotionQQuickView();
    void showView();
    void setSource(const QUrl &source);
    void setLeapTouchEnabled(bool touchEnabled);
    void setLeapMouseEnabled(bool mouseEnabled);
    bool getTouchEnabled() const { return this->touchEnabled; }
    bool getMouseEnabled() const { return this->mouseEnabled; }
    QtLeapMotionController *getLeapController() const { return this->leapController; }

};

} // QtLeapMotion

#endif // __LEAPMOTIONQQUICKVIEW_H_
