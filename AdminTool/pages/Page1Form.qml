import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    title: qsTr("Page 1")
    Label {
        id: label1
        text: qsTr("Welcome to the authentication page,")
        x: (parent.width - width) / 2
        y: parent.heigth / 6 + 3 * label1.heigth
    }

    Label {
        id: label2

        text: qsTr(" we ask you to send scans (photos) of some documents")
        anchors.top: label1.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: label1.horizontalCenter
    }

    Label {
        id: label3

        text: " in order to be able to rent or lease cars."
        anchors.horizontalCenter: label2.horizontalCenter
        anchors.top: label2.bottom
        anchors.topMargin: 10
    }
    SwipeView {
        anchors.horizontalCenter: label3.horizontalCenter
        anchors.top: label3.bottom
        anchors.topMargin: 40
        width: parent.width / 2
        height: parent.height / 2
        id: docView
        ListView {
            width: parent.width
            model: documentsFirstly
            delegate: ItemDelegate {
                id: docContent
                width: docView.width
                Text {
                    id: docName
                    text: documentsName
                    width: docView.width - docClip.width
                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "whitesmoke"
                }
                ItemDelegate {
                    anchors.right: docContent.right
                    anchors.verticalCenter: docContent.verticalCenter
                    id: docClip
                    Image {
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectCrop
                        source: "qrc:/source/pics/clip.png"
                    }
                    onClicked:
                    {
                        gallery.index = index
                        gallery.docStr = documentsName
                        gallery.open()
                    }
                }
                Image {
                    anchors.verticalCenter: docContent.verticalCenter
                    anchors.right: docClip.left
                    fillMode: Image.PreserveAspectCrop
                    source: "qrc:/source/pics/checkMark.png"
                    visible: visibleMark
                }
            }
        }
        Connections
        {
            target: personModel
            onSetButton:
            {
                confirm.visible = true
            }
        }
    }
    Button
    {
        anchors.top: docView.bottom
        anchors.horizontalCenter: docView.horizontalCenter
        anchors.topMargin: 10
        id: confirm
        Text {
            anchors.centerIn: parent
            id: name
            text: qsTr("Confirm")
            color: "whitesmoke"
        }
        visible: false
        onClicked:
        {
            window.confirmPerson()
            window.pop()
        }
    }
    Label {
        id : confirmLine1
        anchors.top: confirm.bottom
        anchors.horizontalCenter: docView.horizontalCenter
        text: qsTr("When we are confirm your document,")
        color: "whitesmoke"
        visible: confirm.visible
    }
    Label {
        id : confirmLine2
        anchors.top: confirmLine1.bottom
        anchors.horizontalCenter: confirmLine1.horizontalCenter
        text: qsTr("you will took access to another functions")
        color: "whitesmoke"
        visible: confirm.visible
    }
    Drawer
    {
        property int index : -1
        property string docStr: ""
        id: gallery
        width: window.width
        height: window.height * 0.5
        edge: Qt.BottomEdge
        Text
        {
            id: choose
            width: parent.width
            anchors.top: parent.top
            text: "Please, choose " + gallery.docStr + " image"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "whitesmoke"
        }
        SwipeView
        {
            interactive: false
            anchors.top: choose.bottom
            width: parent.width
            height: parent.height - choose.height
            ListView
            {
                width : parent.width
                height: parent.height
                model : personModel
                delegate: Row{
                    ItemDelegate{
                        width:  parent.width / 3
                        height: parent.width / 3
                        Image
                        {
                            anchors.centerIn: parent
                            width:  parent.width * 0.9
                            height: parent.height * 0.9
                            fillMode: Image.PreserveAspectFit
                            source: "file:/" + model.source1Role
                        }
                        onClicked:
                        {
                            window.attachImage(gallery.index, model.source1Role)
                            gallery.close()
                        }
                    }
                    ItemDelegate{
                        width:  gallery.width / 3
                        height: gallery.width / 3
                        Image
                        {
                            anchors.centerIn: parent
                            width:  parent.width * 0.9
                            height: parent.height * 0.9
                            fillMode: Image.PreserveAspectFit
                            source: "file:/" +  model.source2Role
                        }
                        onClicked:
                        {
                            window.attachImage(gallery.index, model.source2Role)
                            gallery.close()
                        }
                    }
                    ItemDelegate{
                        width:  gallery.width / 3
                        height: gallery.width / 3
                        Image
                        {
                            anchors.centerIn: parent
                            width:  parent.width * 0.9
                            height: parent.height * 0.9
                            fillMode: Image.PreserveAspectFit
                            source: "file:/" + model.source3Role
                        }
                        onClicked:
                        {
                            window.attachImage(gallery.index, model.source3Role)
                            gallery.close()
                        }
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:4;anchors_y:117}D{i:5;anchors_y:192}
}
 ##^##*/
