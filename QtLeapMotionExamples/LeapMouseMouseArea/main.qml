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

import QtQuick 2.1
import QtQuick.Window 2.1
import QtLeapMotion 2.0

Rectangle
{
    width : Screen.width
    height : Screen.height
    color : "dodgerblue"


    Rectangle
    {
        height : parent.height * 0.4
        width : parent.width * 0.4
        color : "red"
        scale : rec1_ma.pressed ? 0.9 : 1
        anchors
        {
            left : parent.left
            top : parent.top
            margins : 50
        }
        MouseArea
        {
            id : rec1_ma
            anchors.fill: parent
        }
    }

    Rectangle
    {
        height : parent.height * 0.4
        width : parent.width * 0.4
        color : "orange"
        scale : rec2_ma.pressed ? 0.9 : 1
        anchors
        {
            right : parent.right
            top : parent.top
            margins : 50
        }
        MouseArea
        {
            id : rec2_ma
            anchors.fill: parent
        }
    }

    Rectangle
    {
        height : parent.height * 0.4
        width : parent.width * 0.4
        color : "yellow"
        scale : rec3_ma.pressed ? 0.9 : 1
        anchors
        {
            left : parent.left
            bottom : parent.bottom
            margins : 50
        }
        MouseArea
        {
            id : rec3_ma
            anchors.fill: parent
        }
    }

    Rectangle
    {
        height : parent.height * 0.4
        width : parent.width * 0.4
        color : "blue"
        scale : rec4_ma.pressed ? 0.9 : 1
        anchors
        {
            right : parent.right
            bottom : parent.bottom
            margins : 50
        }
        MouseArea
        {
            id : rec4_ma
            anchors.fill: parent
        }
    }
}
