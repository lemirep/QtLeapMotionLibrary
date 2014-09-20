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

    property int oldHandId : -1
    property bool fist : false

    HandsMotionArea
    {
        onHandAdded: {

            console.log("Hand Added")
            if (oldHandId === -1)
                oldHandId = hand.id
        }

        onHandRemoved: {

            console.log("Hand Removed")
            if (oldHandId !== -1)
            {
                oldHandId = -1;
                fist = false;
            }
        }

        onHandUpdated : {
            console.log("Fingers" + hand.isFist);
            if (oldHandId !== -1)
                fist = hand.isFist
        }
    }

    Text
    {
        width : parent.width
        height : parent.height
        text : "We have a fist"
        color : "black";
        visible : fist
        font.pointSize: 45
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
