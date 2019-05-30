import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.calendar 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import "pages"
ApplicationWindow {
    id: window
    objectName: "window"
    visible: true
    width: 640
    height: 480
    title: qsTr("AdminTool")
    signal clickedMe(int index)
    signal sendResponce(int indexReq, int totalReq, int value);
    header: ToolBar {
        contentHeight: from.height * 1.2
        ItemDelegate {
            id : from
            property date fromDate: new Date()
            text: fromDate.toLocaleDateString("mm-dd-yyyy")
            anchors.centerIn: parent
        }
    }
    ListModel
    {
        id: model
        objectName: "model"
    }
    ListModel
    {
        id: person
        objectName: "person"
    }
    ListModel
    {
        id: car
        objectName: "car"
    }
    SwipeView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: model
            delegate: ItemDelegate {
                width: parent.width
                Label
                {
                    id: userLogin
                    anchors.verticalCenter: parent.verticalCenter
                    x: parent.width / 10
                    text: qsTr("User login: " + model.login);
                    color: "whitesmoke"
                    font.pointSize: 8
                }
                Label
                {
                    id: docType
                    anchors.left: userLogin.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("type of registration: " + model.type)
                    color: "whitesmoke"
                    font.pointSize: 8
                }
                ItemDelegate
                {
                    id: link
                    objectName: "link"
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    width:  rectbut.width * 1.2
                    height: rectbut.height * 1.2
                    Rectangle
                    {
                        anchors.fill: parent
                        radius: 15
                        color: "royalblue"
                        Text {
                            id: rectbut
                            anchors.centerIn: parent
                            text: qsTr("send response")
                            color: "whitesmoke"
                            font.pointSize: 10
                        }
                    }

                    onClicked:
                    {
                        window.clickedMe(model.index)
                    }
                }
            }
        }
    }
    Label
    {
        anchors.centerIn: parent
        text: qsTr("Nothing to do")
        color: "whitesmoke"
        font.pointSize: 10
        visible: (model.count === 0) ? true : false
    }
    Dialog
    {
        id: personRegistration
        objectName: "personRegistration"
        visible: false
        anchors.centerIn: parent
        width:  parent.width * 0.8
        height: parent.height * 0.8
        property int indexReq
        property int totalReq
        property int bitmap : 0
        SwipeView {
            id: personView
            anchors.top:  parent.top
            width:        parent.width
            height:       parent.height * 0.6
            anchors.left: parent.Left
            ListView {
                model: person
                width: parent.width
                delegate: ItemDelegate
                {
                    width: parent.width
                    Label
                    {
                        id: personDocName
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 10
                        text: qsTr("Documtent: " + model.documents)
                    }
                    ItemDelegate
                    {
                        anchors.right: switchMy.left
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        Image
                        {
                            anchors.fill: parent
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:/source/pics/eye.png"
                        }
                        onClicked:
                        {
                            imageDialog.visible = true
                        }
                    }
                    Dialog{
                        id: imageDialog
                        anchors.centerIn: window
                        width: window.width / 2
                        height: window.height / 2
                        visible: false
                        Image
                        {
                            anchors.fill: parent
                            fillMode: Image.PreserveAspectFit
                            source: "file:/" + model.source
                        }
                    }
                    Switch
                    {
                        id: switchMy
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Correct")
                        position: 0.0
                        onClicked:
                        {
                            if(position === 0.0)
                            {

                                personRegistration.bitmap = personRegistration.bitmap & (~(1 << model.index))
                            }else
                            {

                                personRegistration.bitmap = personRegistration.bitmap | (1 << model.index)
                            }
                        }
                    }
                }
            }
        }
        ItemDelegate{
            //x: personRegistration.x + personRegistration.width / 2 - width / 2
            //y: personRegistration.y + personRegistration.height * 0.8
            anchors.bottom : parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: personView.horizontalCenter
            width: sendResponce.width * 1.2
            height: sendResponce.height * 1.2
            Rectangle
            {
                anchors.fill: parent
                radius: 15
                color: "royalblue"
                Text
                {
                    id: sendResponce
                    anchors.centerIn: parent
                    text: qsTr("Send Responce")
                    font.pointSize: 10
                    color: "whitesmoke"
                }
            }
            onClicked:
            {
                personRegistration.visible = false;
                window.sendResponce(personRegistration.indexReq, personRegistration.totalReq, personRegistration.bitmap);
            }
        }
    }
    Dialog
    {
        id: carRegistration
        objectName: "carRegistration"
        visible: false
        anchors.centerIn: parent
        width:  parent.width * 0.8
        height: parent.width * 0.8
    }
    Connections
    {
        target: core
        onAdd:
        {
            model.append({"login" : userName, "type" : type})
        }
    }
    Connections
    {
        target: core
        onAddDoc:
        {
            person.append({"documents" : docName, "source" : docSource})
        }
    }
    Connections
    {
        target: core
        onErase:
        {
            model.remove(totalReq)
        }
    }
    Connections
    {
        target: core
        onClearDoc:
        {
            if(personRegistration.visible === true)
            {
                person.clear();
            }else
            {
                car.clear();
            }
        }
    }
    /*StackView {
        id: stackView
        objectName: "stackView"
        initialItem: "qrc:/pages/pages/ListPage.ui.qml"
        anchors.fill: parent

        MyBusyIndicator {
            id: busyIndicator
            x: window.width * 3 / 8
            y: window.height / 4
            width: window.width / 4
            height: window.height / 4
            clip: true
            scale: 1
            z: 0
            rotation: 0
            transformOrigin: Item.Center
            focusPolicy: Qt.WheelFocus
        }
        visible: true
    }*/
}
