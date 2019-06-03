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
    title: qsTr("Stack")
    signal attachImage(int docID, string name)
    signal attachImageCar(int docID, string name)
    signal confirmPerson()
    signal confirmCar()
    signal pop()
    signal carView(int id)
    header: ToolBar {
        contentHeight: toolButton.implicitHeight
        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
            visible: stackView.visible
        }
        Label {
            id: center
            text: "-"
            anchors.centerIn: parent
        }
        ItemDelegate {
            id : from
            property bool isMe : false
            property date fromDate: new Date()
            text: fromDate.toLocaleDateString("mm-dd-yyyy")
            anchors.right: center.left
            onClicked:
            {
                grid.local = fromDate
                grid.trueLocal = fromDate
                from.isMe = true
                spaceCalendar.open()
            }
            Connections
            {
                target: calendar
                onNewDate :
                {
                    if(from.isMe)
                    from.fromDate = date
                    from.isMe = false
                }
            }
        }
        ItemDelegate {
            id : to
            property date toDate: new Date()
            property bool isMe : false
            text: toDate.toLocaleDateString("mm-dd-yyyy")
            anchors.left: center.right
            onClicked:
            {
                grid.local = toDate
                grid.trueLocal = toDate
                to.isMe = true
                spaceCalendar.open()
            }
            Connections
            {
                target: calendar
                onNewDate :
                {
                    if(to.isMe)
                    to.toDate = date
                    to.isMe = false
                }
            }
        }
    }
    Drawer {
        id: drawer
        width: window.width * 0.5
        height: window.height
        signal clear()

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Proof of identity or car")
                objectName: "registrationPerson"
                width: parent.width
                onClicked: {
                    drawer.clear()
                    stackView.push("qrc:/pages/pages/Page1Form.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                visible: false
                text: qsTr("My Cars")
                objectName: "myCars"
                width: parent.width
                onClicked: {
                    stackView.push("qrc:/pages/pages/Page2Form.qml")
                    drawer.close()
                }
            }
        }
    }

    Drawer
    {
        id: spaceCalendar
        objectName: "spaceCalendar"
        width: window.width
        height: window.height * 0.5
        bottomMargin: 0
        edge: Qt.TopEdge
        ColumnLayout{
            height: parent.height
            anchors.centerIn: parent
            GridLayout {
                columns: 2
                id : spaceGrid
                DayOfWeekRow {
                    locale: Qt.locale("en_US")
                    Layout.column: 1
                    Layout.fillWidth: true
                }

                WeekNumberColumn {
                    month: grid.local.getMonth()
                    year: grid.local.getFullYear()
                    locale: Qt.locale("en_US")
                    Layout.column: 0
                    Layout.row: 1
                    Layout.fillHeight: true
                }
                MonthGrid {
                    id: grid
                    objectName : "grid"
                    Layout.column: 1
                    Layout.row: 1
                    property date local : new Date()
                    property date trueLocal : new Date()
                    month: grid.local.getMonth()
                    year: grid.local.getFullYear()
                    locale: Qt.locale("en_US")

                    signal changeDate(date d)

                    delegate: ItemDelegate {
                        id: day
                        Rectangle{
                            anchors.centerIn: parent
                            height: parent.height
                            width: parent.width
                            radius: 10
                            color: Material.color((model.day === grid.trueLocal.getDate()
                                                    && model.month === grid.trueLocal.getMonth()
                                                     && model.year === grid.trueLocal.getFullYear()) ? Material.Indigo :
                                                 (model.month === grid.local.getMonth() ?  Material.BlueGrey : Material.Grey))
                            Text{
                                anchors.centerIn: parent
                                height: parent.height
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment  : Text.AlignVCenter
                                text: Qt.formatDateTime(model.date, "dd")
                            }
                        }
                        onClicked:
                        {
                            var a = new Date(model.year, model.month, model.day)
                            grid.changeDate(a)
                            spaceCalendar.close()
                        }
                    }
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
            RowLayout{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                ItemDelegate{
                    Layout.column: 0
                    Layout.row: 1
                    height: lefrArrowPics.height
                    width:  lefrArrowPics.width
                    id: lefrArrow
                    objectName: "leftArrow"
                    signal changeMonth(date d)
                    Image {
                        id: lefrArrowPics
                        height: parent.height
                        Layout.column: 0
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/source/pics/leftArrow.png"
                    }
                    onClicked:
                    {
                        changeMonth(grid.local)
                    }
                }
                Rectangle{
                    Layout.alignment: Qt.AlignCenter
                    Layout.bottomMargin: height * 0.1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 20
                    color: Material.color(Material.Grey)
                    Text
                    {
                        id : str
                        objectName: "str"
                        anchors.centerIn: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment  : Text.AlignVCenter
                        text: Qt.formatDateTime(grid.local,"MMMM yyyy")
                    }
                }
                ItemDelegate{
                    Layout.column: 3
                    Layout.row: 1
                    height: rightArrowPics.height
                    width:  rightArrowPics.width
                    id: rightArrow
                    objectName: "rightArrow"
                    signal changeMonth(date d)
                    Image {
                        id: rightArrowPics
                        height: parent.height
                        Layout.column: 0
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/source/pics/rightArrow.png"
                    }
                    onClicked:
                    {
                        changeMonth(grid.local)
                    }
                }
            }

        }
    }
    Connections
    {
        target: window
        onPop :
        {
            if(stackView.depth > 1) stackView.pop();
        }
    }
    StackView {
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
        visible: false
    }
    MyBusyIndicator
    {
        id: busyIndicatorMain
        objectName: "busyIndicatorMain"
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

    Dialog
    {
        visible: false
        anchors.centerIn: parent
        id: note
        objectName: "note"
        width : window.width / 2
        height : window.height / 3

        Text
        {
            id: waitingConfirm1
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            text: qsTr("We confirm your documents,")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
            color: "whitesmoke"
            font.pointSize: 10
        }
        Text
        {
            id: waitingConfirm2
            anchors.top: waitingConfirm1.bottom
            anchors.horizontalCenter: waitingConfirm1.horizontalCenter
            text: qsTr("please wait for a response from us")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
            color: "whitesmoke"
            font.pointSize: 10
            anchors.topMargin: 10
        }
        Button
        {
            anchors.top: waitingConfirm2.bottom
            anchors.horizontalCenter: waitingConfirm2.horizontalCenter
            anchors.topMargin: 10
            Text {
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter
                color: "whitesmoke"
                font.pointSize: 10
                text: qsTr("Okey!")
            }
            onClicked:
            {
                note.close()
            }
        }
    }
    Dialog
    {
        visible: false
        anchors.centerIn: parent
        id: successReg
        objectName: "successReg"
        width : window.width * 0.7
        height : window.height / 2
        Text
        {
            id: successReg1
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            text: qsTr("We have completed the confirmation of your documents,")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
            color: "whitesmoke"
            font.pointSize: 10
        }
        Text
        {
            id: successReg2
            anchors.top: successReg1.bottom
            anchors.horizontalCenter: successReg1.horizontalCenter
            text: qsTr("and we are grateful for your anticipation.")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
            color: "whitesmoke"
            font.pointSize: 10
            anchors.topMargin: 10
        }
        Text
        {
            id: successReg3
            objectName: "successReg3"
            anchors.top: successReg2.bottom
            anchors.horizontalCenter: successReg2.horizontalCenter
            text: qsTr("and we are grateful for your anticipation.")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
            color: "whitesmoke"
            font.pointSize: 10
            anchors.topMargin: 10
        }
        Button
        {
            anchors.top: successReg3.bottom
            anchors.horizontalCenter: successReg3.horizontalCenter
            anchors.topMargin: 10
            Text {
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter
                color: "whitesmoke"
                font.pointSize: 10
                text: qsTr("Okey!")
            }
            onClicked:
            {
                successReg.close()
            }
        }
    }
    ListModel {
        id: documentsFirstly
    }
    ListModel {
        id: documentsCars
        ListElement
        {
            index : 0
            documentsName: "Сertificate"
            visibleMark: false
        }
        ListElement
        {
            index : 1
            documentsName: "PTS"
            visibleMark: false
        }
        ListElement
        {
            index : 2
            documentsName: "OSAGO"
            visibleMark: false
        }
        ListElement
        {
            index : 3
            documentsName: "Photo of car"
            visibleMark: false
        }
    }
    Connections
    {
        target: core
        onClear:
        {
            documentsFirstly.clear()
        }
    }
    Connections
    {
        target: core
        onAdd:
        {
            documentsFirstly.append({"index": id, "documentsName" : name, "visibleMark" : vis});
        }
    }
    Connections
    {
        target: core
        onWaitingConfirm:
        {
            note.visible = true
        }
    }

    Connections
    {
        target: personModel
        onSetVisible:
        {
            documentsFirstly.get(idDoc).visibleMark = vis
        }
    }

    Connections
    {
        target: carDocModel
        onSetVisible:
        {
            documentsCars.get(idDoc).visibleMark = vis
        }
    }
    Connections
    {
        target: carModel
        onCarRegistrationPage:
        {
            stackView.push("qrc:/pages/pages/AddCarPage.qml")
        }
    }
}
