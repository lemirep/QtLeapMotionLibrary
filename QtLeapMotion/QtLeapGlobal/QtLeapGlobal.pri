#/****************************************************************************
#**
#** Copyright (C) Paul Lemire
#** Contact: paul.lemire@epitech.eu
#**
#**
#** GNU Lesser General Public License Usage
#** This file may be used under the terms of the GNU Lesser
#** General Public License version 2.1 as published by the Free Software
#** Foundation and appearing in the file LICENSE.LGPL included in the
#** packaging of this file.  Please review the following information to
#** ensure the GNU Lesser General Public License version 2.1 requirements
#** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#**
#** GNU General Public License Usage
#** Alternatively, this file may be used under the terms of the GNU
#** General Public License version 3.0 as published by the Free Software
#** Foundation and appearing in the file LICENSE.GPL included in the
#** packaging of this file.  Please review the following information to
#** ensure the GNU General Public License version 3.0 requirements will be
#** met: http://www.gnu.org/copyleft/gpl.html.
#**
#**
#****************************************************************************/

SOURCES += $$PWD/QtLeapFinger.cpp \
           $$PWD/QtLeapHand.cpp \
           $$PWD/QtLeapPointable.cpp \
           $$PWD/QtLeapTool.cpp \
           $$PWD/QtLeapUtils.cpp \
           $$PWD/Handlers/DefaultQtLeapHandsHandler.cpp \
           $$PWD/Qml/HandsMotionArea.cpp \
           $$PWD/Qml/FingersMotionArea.cpp \
           $$PWD/QtLeapMotionQQuickView.cpp \
           $$PWD/QtLeapBone.cpp


HEADERS += $$PWD/QtLeapFinger.h \
           $$PWD/QtLeapHand.h \
           $$PWD/QtLeapPointable.h \
           $$PWD/QtLeapTool.h \
           $$PWD/QtLeapUtils.h \
           $$PWD/Handlers/QtLeapMotionHandler.h \
           $$PWD/Handlers/QtLeapHandsHandlerInterface.h \
           $$PWD/Handlers/DefaultQtLeapHandsHandler.h \
           $$PWD/Listeners/QtLeapFingersListenerInterface.h \
           $$PWD/Listeners/QtLeapHandsListenerInterface.h \
           $$PWD/Qml/HandsMotionArea.h \
           $$PWD/Qml/FingersMotionArea.h \
           $$PWD/QtLeapMotionQQuickView.h \
           $$PWD/QtLeapGlobal.h \
           $$PWD/QtLeapBone.h

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Handlers
INCLUDEPATH += $$PWD/Qml
INCLUDEPATH += $$PWD/Listeners
