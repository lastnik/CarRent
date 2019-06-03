import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 600
    height: 400

    title: qsTr("Page 2")
    Label {
        id: label1
        text: qsTr("Welcome to page with you car.")
        x: (parent.width - width) / 2
        y: parent.heigth / 6 + 3 * label1.heigth
    }

    Label {
        id: label2

        text: qsTr(" There is you list of cars")
        anchors.top: label1.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: label1.horizontalCenter
    }

    Label {
        id: label3

        text: " if you'd like to add new car press button."
        anchors.horizontalCenter: label2.horizontalCenter
        anchors.top: label2.bottom
        anchors.topMargin: 10
    }
    SwipeView {
        id: swipeView
        orientation: Qt.Vertical
        anchors.top: label3.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: parent.width
        ListView
        {
            width: parent.width
        }
    }
}




/*##^## Designer {
    D{i:1;anchors_height:405;anchors_width:600;anchors_x:0;anchors_y:0}
}
 ##^##*/
