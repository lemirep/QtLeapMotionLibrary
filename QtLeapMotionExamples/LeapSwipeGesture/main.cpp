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

#include <QGuiApplication>
#include <QScopedPointer>
#include <QtLeapGlobal/QtLeapMotionQQuickView.h>

int     main(int ac, char **av)
{
    QScopedPointer<QGuiApplication> app(new QGuiApplication(ac, av));
    QtLeapMotion::QtLeapMotionQQuickView *view = new QtLeapMotion::QtLeapMotionQQuickView();

    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->setLeapMouseEnabled(true);
    view->showView();
    return app->exec();
}
