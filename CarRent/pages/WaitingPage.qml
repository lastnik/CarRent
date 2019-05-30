import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Styles 1.4
Page
{
    id: logPage
    Image {
        id: backGround
        height: parent.height
        width : parent.width
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/source/pics/highWay.png"
        BusyIndicator {
            id: control
            x: backGround.width * 3 / 8
            y: backGround.height / 4
            width: backGround.width / 4
            height: backGround.height / 4
            clip: true
            scale: 1
            z: 0
            rotation: 0
            transformOrigin: Item.Center
            focusPolicy: Qt.WheelFocus
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
        Rectangle
        {
            x: backGround.width  / 2
            y: backGround.height  / 2 + textLog.height
            Text{
                id:textLog
                anchors.centerIn: parent
                width: backGround.width / 4
                height: backGround.height / 4
                text: "Try to loggin...."
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter
                color: "whitesmoke" //Material.color(Material.Pink)
                font.pointSize: 14
            }
        }
    }
}
