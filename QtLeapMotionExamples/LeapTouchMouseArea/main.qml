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

Item
{
    width : Screen.width
    height : Screen.height

    ListView
    {
        id : series_listview
        anchors.fill: parent
        orientation: ListView.Horizontal
        model : series_model
        delegate: Component {
            Image
            {
                height : series_listview.height
                width : height / 1.47
                source : model.pic
                fillMode: Image.PreserveAspectFit
                scale : del_ma.pressed ? 0.9 : 1
                Behavior on scale {NumberAnimation {duration : 500} }
//                MouseArea
//                {
//                    id : del_ma
//                    anchors.fill: parent
//                }
            }
        }
    }


//    MultiPointTouchArea
//    {
//        anchors.fill: parent
//        property var points : [];

//        onPressed: {points = touchPoints;}
//        onReleased: {points = touchPoints;}
//        onUpdated:  {points = touchPoints;}
//        onTouchUpdated: {points = touchPoints;}

//        Repeater
//        {
//            model : parent.points
//            delegate : Component {
//                Rectangle
//                {
//                    z : 100
//                    width : 25
//                    height : 25
//                    radius : 180
//                    color : "lawngreen"
//                    x : modelData.x
//                    y : modelData.y
//                }
//            }
//        }
//    }

    ListModel
    {
        id : series_model

        ListElement
        {
            title : "Homeland"
            color : "pink"
//            pic : "http://trakt.us/images/posters/10369-300.jpg"
            pic : "10369-300.jpg"
        }
        ListElement
        {
            title : "House"
            color : "purple"
//            pic : "http://trakt.us/images/posters/71-300.jpg"
            pic : "71-300.jpg"
        }
        ListElement
        {
            title : "Rake"
            color : "black"
//            pic : "http://trakt.us/images/posters/23280-300.jpg"
            pic : "23280-300.jpg"

        }
        ListElement
        {
            title : "Shameless"
            color : "grey"
//            pic : "http://trakt.us/images/posters/1388-300.jpg"
            pic : "1388-300.jpg"
        }
        ListElement
        {
            title : "House of Cards"
            color : "white"
//            pic : "http://trakt.us/images/posters/19657-300.jpg"
            pic : "19657-300.jpg"
        }
        ListElement
        {
            title : "Suits"
            color : "yellow"
//            pic : "http://trakt.us/images/posters/9617-300.jpg"
            pic : "9617-300.jpg"
        }
        ListElement
        {
            title : "Castle"
            color : "blue"
//            pic : "http://trakt.us/images/posters/73-300.jpg"
            pic : "73-300.jpg"
        }
        ListElement
        {
            title : "Hannibal"
            color : "red"
//            pic : "http://trakt.us/images/posters/16689-300.jpg"
            pic : "16689-300.jpg"
        }
        ListElement
        {
            title : "The Blacklist"
            color : "orange"
//            pic : "http://trakt.us/images/posters/23288-300.jpg"
            pic : "23288-300.jpg"
        }
        ListElement
        {
            title : "The Americans"
            color : "lightsteelblue"
//            pic : "http://trakt.us/images/posters/19488-300.jpg"
            pic : "19488-300.jpg"
        }
    }

}
