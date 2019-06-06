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
    height: 640
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
        property int indexReq
        property int totalReq
        property int bitmap : 0
        property string brend  : ""
        property string model  : ""
        property string color  : ""
        property string number : ""
        property int    year   : 0
        SwipeView {
            id: carView
            anchors.top:  parent.top
            width:        parent.width
            height:       parent.height * 0.6
            anchors.left: parent.Left
            anchors.bottom: lineCarBrend.top
            ListView {
                model: car
                width: parent.width
                delegate: ItemDelegate
                {
                    width: parent.width
                    Label
                    {
                        id: carDocName
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 10
                        text: qsTr("Documtent: " + model.documents)
                    }
                    ItemDelegate
                    {
                        anchors.right: switchMyCar.left
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
                            imageDialogCar.visible = true
                        }
                    }
                    Dialog{
                        id: imageDialogCar
                        //anchors.centerIn: window
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
                        id: switchMyCar
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Correct")
                        position: 0.0
                        onClicked:
                        {
                            if(position === 0.0)
                            {

                                carRegistration.bitmap = carRegistration.bitmap & (~(1 << model.index))
                            }else
                            {

                                carRegistration.bitmap = carRegistration.bitmap | (1 << model.index)
                            }
                        }
                    }
                }
            }
        }

        Label
        {
            id: carBrend
            width: parent.width / 7
            anchors.left: carYear.left
            anchors.verticalCenter: lineCarBrend.verticalCenter
            text: qsTr("Car brend: ")
        }
        TextField
        {
            id: lineCarBrend
            objectName: "lineCarBrend"
            anchors.top:  lineCarModel.top
            anchors.right: lineCarNumber.right
            width: parent.width / 3

            placeholderText: qsTr("%1").arg(carRegistration.brend)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            enabled: false
        }

        Label
        {
            id: carModel
            width: carBrend.width
            anchors.verticalCenter: lineCarModel.verticalCenter
            anchors.left: carColor.left
            text: qsTr("Car model: ")
        }
        TextField
        {
            id: lineCarModel
            anchors.bottom:  lineCarColor.top
            anchors.bottomMargin: 10
            anchors.left: lineCarColor.left
            width: lineCarBrend.width

            placeholderText: qsTr("%1").arg(carRegistration.model)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            enabled: false
        }

        Label
        {
            id: carColor
            width: carModel.width
            anchors.verticalCenter: lineCarColor.verticalCenter
            anchors.left:  switchMyCarInfo.left
            text: qsTr("Car color: ")
        }
        TextField
        {
            id: lineCarColor
            anchors.top:  lineCarNumber.top
            anchors.left: carColor.right
            width: lineCarModel.width
            placeholderText: qsTr("%1").arg(carRegistration.color)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            enabled: false
        }


        Label
        {
            id: carNumber
            width: carColor.width
            anchors.verticalCenter:  lineCarNumber.verticalCenter
            anchors.right: lineCarNumber.left
            anchors.rightMargin: 20
            text: qsTr("Car number: ")
        }
        TextField
        {
            id: lineCarNumber
            anchors.bottom:  lineCarYear.top
            anchors.bottomMargin: 10
            anchors.right: lineCarYear.right

            width: lineCarModel.width
            placeholderText: qsTr("%1").arg(carRegistration.number)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            enabled : false
        }
        Label
        {
            id: carYear
            width: carColor.width
            height: carModel.height
            anchors.verticalCenter: lineCarYear.verticalCenter
            anchors.right: lineCarYear.left
            anchors.rightMargin: 20
            text: qsTr("Year of issue: ")
        }
        TextField
        {
            id: lineCarYear
            anchors.bottom: customButton.top
            anchors.right: customButton.horizontalCenter
            anchors.rightMargin: 10
            width: lineCarModel.width
            placeholderText: qsTr("%1").arg(carRegistration.year)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            enabled : false
        }
        Switch
        {
            id: switchMyCarInfo
            anchors.bottom: customButton.top
            anchors.left: customButton.horizontalCenter
            anchors.leftMargin: 10
            text: qsTr("Correct")
            position: 0.0
            onClicked:
            {
                    if(position === 0.0)
                    {
                        if(carRegistration.bitmap > 0)
                        {
                            carRegistration.bitmap = -carRegistration.bitmap
                        }
                    }else
                    {
                        if(carRegistration.bitmap < 0)
                        {
                            carRegistration.bitmap = -carRegistration.bitmap
                        }
                    }

            }
        }
        ItemDelegate{
            anchors.bottom : parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: carView.horizontalCenter
            width: sendResponceCar.width * 1.2
            height: sendResponceCar.height * 1.2
            id: customButton
            Rectangle
            {
                anchors.fill: parent
                radius: 15
                color: "royalblue"
                Text
                {
                    id: sendResponceCar
                    anchors.centerIn: parent
                    text: qsTr("Send Responce")
                    font.pointSize: 10
                    color: "whitesmoke"
                }
            }
            onClicked:
            {
                switchMyCarInfo.position = 0.0
                carRegistration.visible = false;
                window.sendResponce(carRegistration.indexReq, carRegistration.totalReq, carRegistration.bitmap);
            }
        }
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
            if(personRegistration.visible === true)
            {
                person.append({"documents" : docName, "source" : docSource})
            }else
            {
                car.append({"documents" : docName, "source" : docSource})
            }
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
}
