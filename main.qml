import QtQuick 2.1
import QtQuick.Window 2.1

import Tepee3D 1.0 // FOR LEAP GESTURE ARE

Rectangle
{
    width : Screen.width
    height : Screen.height
    color : "dodgerblue"

    MultiPointTouchArea
    {
        anchors.fill: parent
        property var points : [];

        onPressed: {points = touchPoints;}
        onReleased: {points = touchPoints;}
        onUpdated:  {points = touchPoints;}
        onTouchUpdated: {points = touchPoints;}

        Repeater
        {
            model : parent.points
            delegate : Component {
                Rectangle
                {
                    z : 100
                    width : 25
                    height : 25
                    radius : 180
                    color : "lawngreen"
                    x : modelData.x
                    y : modelData.y
                }
            }
        }
    }

    LeapGestureArea
    {
        anchors.fill: parent

        onCircleGesture :
        {
            console.log("circle gesture");
        }

        onSwipeGesture :
        {
            console.log("swipe gesture");
        }

        onKeyTapGesture :
        {
            console.log("keyTap gesture");
        }

        onScreenTapGesture :
        {
            console.log("screenTap gesture");
        }
    }
}
