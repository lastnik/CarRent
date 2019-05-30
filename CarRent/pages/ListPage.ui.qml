import QtQuick 2.12
import QtQuick.Controls 2.5

Page {

    title: qsTr("Home")

    SwipeView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }
}
