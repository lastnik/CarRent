import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.2
Page {
    id: page
    width: parent.width
    height: parent.height

    title: qsTr("Car Page")

    Label {
        id: carlabel1
        text: qsTr("Welcome to page car's registration.")
        x: (parent.width - width) / 2
        y: parent.heigth / 6 + 3 * carlabel1.heigth
    }

    Label {
        id: carlabel2

        text: qsTr(" There is you list of cars")
        anchors.top: carlabel1.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: carlabel1.horizontalCenter
    }

    Label {
        id: carlabel3

        text: " if you'd like to add new car press button."
        anchors.horizontalCenter: carlabel2.horizontalCenter
        anchors.top: carlabel2.bottom
        anchors.topMargin: 10
    }
    Label
    {
        id: carBrend
        width: parent.width / 7
        anchors.top:  carlabel3.bottom
        anchors.topMargin: 20
        x: parent.width / 2 - (carBrend.width + lineCarBrend.width)
        text: qsTr("Car brend: ")
    }
    TextField
    {
        id: lineCarBrend
        objectName: "lineCarBrend"
        anchors.verticalCenter:  carBrend.verticalCenter
        anchors.left: carBrend.right
        width: parent.width / 4

        placeholderText: qsTr("Kia")
        placeholderTextColor: "papayawhip"
        Rectangle
        {
            anchors.fill: parent
            color: "papayawhip"
            OpacityAnimator on opacity
            {
                id: er0
                from: 0.7
                to  : 0.0
                duration: 500
            }
        }
    }
    Label
    {
        id: carModel
        width: carBrend.width
        anchors.verticalCenter: lineCarModel.verticalCenter
        anchors.left: carBrend.left
        text: qsTr("Car model: ")
    }
    TextField
    {
        id: lineCarModel
        objectName: "lineCarModel"
        anchors.top:  lineCarBrend.bottom
        anchors.left: lineCarBrend.left
        width: lineCarBrend.width

        placeholderText: qsTr("Rio")
        placeholderTextColor: "papayawhip"
        Rectangle
        {
            anchors.fill: parent
            color: "papayawhip"
            OpacityAnimator on opacity
            {
                id: er1
                from: 0.7
                to  : 0.0
                duration: 500
            }
        }
    }
    Label
    {
        id: carColor
        width: carModel.width
        anchors.verticalCenter: lineCarBrend.verticalCenter
        anchors.left: lineCarBrend.right
        anchors.leftMargin: 5
        text: qsTr("Car color: ")
    }
    TextField
    {
        id: lineCarColor
        objectName: "lineCarColor"
        anchors.top:  lineCarBrend.top
        anchors.left: carColor.right
        width: lineCarModel.width

        placeholderText: qsTr("Red")
        placeholderTextColor: "papayawhip"
        Rectangle
        {
            anchors.fill: parent
            color: "papayawhip"
            OpacityAnimator on opacity
            {
                id: er2
                from: 0.7
                to  : 0.0
                duration: 500
            }
        }
    }
    Label
    {
        id: carNumber
        width: carColor.width
        anchors.verticalCenter:  lineCarNumber.verticalCenter
        anchors.left: carColor.left
        text: qsTr("Car number: ")
    }
    TextField
    {
        id: lineCarNumber
        objectName: "lineCarNumber"
        anchors.top:  lineCarColor.bottom
        anchors.left: lineCarColor.left
        width: lineCarModel.width

        placeholderText: qsTr("o777oo 197 RUS")
        placeholderTextColor: "papayawhip"
        Rectangle
        {
            anchors.fill: parent
            color: "papayawhip"
            OpacityAnimator on opacity
            {
                id: er3
                from: 0.7
                to  : 0.0
                duration: 500
            }
        }
    }
    Label
    {
        id: carYear
        width: carColor.width
        height: carModel.height
        anchors.top:  lineCarNumber.bottom
        anchors.horizontalCenter: carlabel1.horizontalCenter
        text: qsTr("Year of issue: ")
    }
    Label
    {
        id: anch
        anchors.top: carYear.bottom
        anchors.topMargin: 10
        height: carYear.height
    }
    Tumbler
    {
        property date year: new Date()
        anchors.verticalCenter: anch.verticalCenter
        anchors.topMargin: 10
        anchors.horizontalCenter: carYear.horizontalCenter
        width: carYear.height
        height:  parent.width / 3
        id: tumblerCarYear
        objectName: "tumblerCarYear"
        rotation: -90
        //height: lineCarNumber.height
        model: 200
        currentIndex: 100
        delegate: Text
        {
            id: del
            rotation: 90
            width: carYear.height
            text: qsTr("%1").arg(tumblerCarYear.year.getFullYear() + modelData - 100);
            color : "whitesmoke"
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    SwipeView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: carYear.bottom
        anchors.topMargin: 60
        width: parent.width / 2
        height: parent.height / 3
        id: docView
        ListView {
            width: parent.width
            model: documentsCars
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
            target: carDocModel
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
            visible = false
            window.confirmCar()
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
                model : carDocModel
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
                            window.attachImageCar(gallery.index, model.source1Role)
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
                            window.attachImageCar(gallery.index, model.source2Role)
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
                            window.attachImageCar(gallery.index, model.source3Role)
                            gallery.close()
                        }
                    }
                }
            }
        }
    }
    Connections
    {
        target: core
        onError:
        {
            switch(errorCode)
            {
                case 0:
                    er0.restart();
                    break;
                case 1:
                    er1.restart();
                    break;
                case 2:
                    er2.restart();
                    break;
                case 3:
                    er3.restart();
                    break;
                default:
                    break;
            }

        }
    }
}
