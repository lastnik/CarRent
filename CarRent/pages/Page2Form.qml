import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: parent.width
    height: parent.height

    title: qsTr("List of cars")
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
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        width: parent.width * 0.9
        ListView
        {
            width: parent.width
            height: parent.height
            model: carModel
            delegate: Rectangle
            {
                anchors.fill: parent
                color: "transparent"
                ItemDelegate
                {
                    anchors.centerIn: parent
                    width: rectAdd.width * 1.2
                    height: rectAdd.height * 1.2
                    visible: (model.isLast)? true : false
                    Rectangle
                    {
                        radius: 15
                        color: "royalblue"
                        anchors.centerIn: parent
                        width: rectAdd.width * 1.2
                        height: rectAdd.height * 1.2
                        Text {
                            id: rectAdd
                            anchors.centerIn: parent
                            text: qsTr("Add new car")
                            color: "whitesmoke"
                            font.pointSize: 10
                        }
                    }
                    onClicked:
                    {
                        window.carView(model.index)
                    }
                }
            }
        }
    }
}






/*##^## Designer {
    D{i:1;anchors_height:405;anchors_width:600;anchors_x:0;anchors_y:0}
}
 ##^##*/
