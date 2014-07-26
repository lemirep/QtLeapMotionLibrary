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


    SwipeGestureArea {
        id : swipeArea
        anchors.fill: parent

        property int currentGestureId : -1;

        onGestureStarted:
        {
            if (currentGestureId === -1)
            {
                currentGestureId = gesture.id
//                console.log("Gesture started" + gesture + gesture.id + gesture.direction);
            }
        }

        onGestureUpdated:
        {
            if (gesture.id === currentGestureId) {
//                console.log("Gesture updated" + gesture + gesture.id + gesture.direction);
                console.log(gesture.speed)
                if (gesture.speed > 200)
                {
                    console.log(gesture.startPosition.x + " " + gesture.position.x);
                    var rightToLeft = gesture.startPosition.x < gesture.position.x;
                    if (rightToLeft)
                        pathview.incrementCurrentIndex();
                    else
                        pathview.decrementCurrentIndex();
                    currentGestureId = -1;
                }
            }
        }

        onGestureEnded:
        {
            if (currentGestureId !== -1)
            {
                currentGestureId = -1
//                console.log("Gesture Ended " + gesture + gesture.id)
            }
        }
    }

    ListModel
    {
        id : pathModel
        ListElement { color : "red" }
        ListElement { color : "blue" }
        ListElement { color : "violet" }
        ListElement { color : "green" }
        ListElement { color : "yellow" }
        ListElement { color : "orange" }
        ListElement { color : "black" }
    }

    PathView
    {
        id : pathview
        anchors
        {
            fill : parent
        }
        model : pathModel

        preferredHighlightBegin: 0.5
        preferredHighlightEnd:  0.55
        path : Path {
            startX : 0
            startY: pathview.height * 0.5

            PathCurve { x : pathview.width * 0.5; y : pathview.height * 0.3 }
            PathCurve { x : pathview.width; y : pathview.height * 0.5 }
        }

        delegate : Component {
            Rectangle
            {
                color : model.color
                radius : 25
                width : 150
                height : 150
                //                anchors.centerIn: parent
                border
                {
                    width : PathView.isCurrentItem ? 5 : 0
                    color : "white"
                }
            }
        }
    }
}
