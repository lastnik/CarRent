import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    property bool updateInfo: false
    title: qsTr("Home")
    Text{
        id: rentalLog
        objectName: "rentalLog"
        visible: false
        anchors.centerIn: parent
        width: parent.width / 4
        height: parent.height / 4
        text: "Find nothing on these dates("
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment  : Text.AlignVCenter
        color: "whitesmoke" //Material.color(Material.Pink)
        font.pointSize: 14
    }
    SwipeView {
        id: swipeView
        objectName: "rentalView"
        visible: true
        orientation: Qt.Vertical
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.9
        ListView {
            width: parent.width
            height: parent.height
            model: rentalModel
            delegate: Rectangle
            {
                width: parent.width
                height: lineRentalName.height * 2.5
                color: "transparent"
                Frame
                {
                    anchors.centerIn: parent
                    width: parent.width
                    height: lineRentalName.height * 2.4
                    ItemDelegate{
                        anchors.fill: parent
                        width: parent.width
                        height: parent.height
                        Label
                        {
                            id: rentalName
                            //width: parent.width / 4
                            anchors.left: parent.left
                            anchors.leftMargin: 20
                            anchors.verticalCenter: lineRentalName.verticalCenter
                            text: qsTr("Car :")
                            color: "whitesmoke"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                        }
                        TextField
                        {
                            id: lineRentalName
                            anchors.top: parent.top
                            anchors.left: rentalName.right
                            width: parent.width / 2
                            placeholderText: qsTr("%1").arg(model.adCarName)
                            placeholderTextColor: "papayawhip"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                            enabled: false
                        }
                        Label
                        {
                            id: rentalCost
                            width: rentalName
                            anchors.left: lineRentalName.right
                            anchors.verticalCenter: lineRentalName.verticalCenter
                            text: qsTr("Cost: ")
                            color: "whitesmoke"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                        }
                        TextField
                        {
                            id: lineRentalCost
                            anchors.top: parent.top
                            anchors.left: rentalCost.right
                            width: parent.width / 3
                            placeholderText: qsTr("%1 Rubels per day").arg(model.adCarCost)
                            placeholderTextColor: "papayawhip"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                            enabled: false
                        }
                        Label
                        {
                            id: rentalOwner
                            anchors.left: rentalName.left
                            anchors.verticalCenter: lineRentalOwner.verticalCenter
                            text: qsTr("Car owner: ")
                            color: "whitesmoke"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                        }
                        TextField
                        {
                            id: lineRentalOwner
                            anchors.top: lineRentalName.bottom
                            anchors.left: rentalOwner.right
                            placeholderText: qsTr("%1").arg(model.adCarOwner)
                            placeholderTextColor: "papayawhip"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                            enabled: false
                        }
                        Label
                        {
                            id: rentalFrom
                            anchors.left: lineRentalOwner.right
                            anchors.verticalCenter: lineRentalOwner.verticalCenter
                            text: qsTr("From: ")
                            color: "whitesmoke"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                        }
                        TextField
                        {
                            id: lineRentalFrom
                            anchors.left: rentalFrom.right
                            anchors.verticalCenter: rentalFrom.verticalCenter
                            placeholderText: qsTr("%1").arg(model.adCarFrom)
                            placeholderTextColor: "papayawhip"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                            enabled: false
                        }
                        Label
                        {
                            id: rentalTo
                            anchors.left: lineRentalFrom.right
                            anchors.verticalCenter: lineRentalFrom.verticalCenter
                            text: qsTr("To: ")
                            color: "whitesmoke"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                        }
                        TextField
                        {
                            id: lineRentalTo
                            anchors.left: rentalTo.right
                            anchors.verticalCenter: rentalTo.verticalCenter
                            placeholderText: qsTr("%1").arg(model.adCarTo)
                            placeholderTextColor: "papayawhip"
                            horizontalAlignment : TextInput.AlignHCenter
                            verticalAlignment : TextInput.AlignVCenter
                            enabled: false
                        }
                        onClicked:
                        {
                            window.rentalView(model.index)
                        }
                    }
                }
            }
        }
    }
    BusyIndicator {
        id: control
        objectName: "rentalControl"
        visible: false
        anchors.centerIn: parent
        contentItem: Item {
            implicitWidth: 64
            implicitHeight: 64

            Item {
                id: item
                x: parent.width / 2 - 32
                y: parent.height / 2 - 32
                width: 64
                height: 64
                opacity: control.running ? 1 : 0

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 250
                    }
                }

                RotationAnimator {
                    target: item
                    running: control.visible && control.running
                    from: 0
                    to: 360
                    loops: Animation.Infinite
                    duration: 1250
                }

                Repeater {
                    id: repeater
                    model: 6

                    Rectangle {
                        x: item.width / 2 - width / 2
                        y: item.height / 2 - height / 2
                        implicitWidth: 10
                        implicitHeight: 10
                        radius: 5
                        color: "whitesmoke"
                        transform: [
                            Translate {
                                y: -Math.min(item.width, item.height) * 0.5 + 5
                            },
                            Rotation {
                                angle: index / repeater.count * 360
                                origin.x: 5
                                origin.y: 5
                            }
                        ]
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
