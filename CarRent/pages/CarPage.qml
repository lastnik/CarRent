import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: carPage
    title: qsTr("Page car")
    //objectName: "carPage"
    property string carOwner:   window._carOwner
    property string carName:    window._carName
    property string carBrend:   window._carBrend
    property string carModel:   window._carModel
    property string carColor:   window._carColor
    property string carNumber:  window._carNumber
    property string carPics:    window._carPics
    property bool   carConfirm: window._carConfirm
    property string login:      window._login
    property int    year:       window._year
    property real   cost:       window._cost
    property bool   visFrame     : window._visFrame
    property bool   visRental    : window._visRental
    property string carFrom:    window._carFrom
    property string carTo:      window._carTo
    property real   carCost:    window._carCost
    property string carRentUser: window._carRentUser
    property bool buttonVisible: window._buttonVisible
    Image
    {
        id: carImage
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottomMargin: 10
        width: parent.width / 3
        height: parent.height / 3
        fillMode: Image.PreserveAspectFit
        source: "file:/" + carPics
        ItemDelegate
        {
            anchors.fill: parent
            onClicked:
            {
                bigCarImage.open()
            }
            opacity: 0.0
        }
    }
    Dialog
    {
        id: bigCarImage
        anchors.centerIn: parent
        width: parent.width * 0.7
        height: parent.height * 0.7
        Image
        {
            width: parent.width
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: "file:/" + carPics
        }
    }
    Label
    {
        id: carOwnerlabel
        width: parent / 8
        anchors.left: carImage.right
        anchors.leftMargin: 10
        anchors.top: carImage.top
        text: qsTr("Owner :")
        color: "whitesmoke"
    }
    TextField
    {
        id: carOwnerline
        width: parent / 4
        anchors.left: carOwnerlabel.right
        anchors.verticalCenter: carOwnerlabel.verticalCenter
        enabled: false
        placeholderText: qsTr("%1").arg(carPage.carOwner)
        placeholderTextColor: "papayawhip"
        horizontalAlignment : TextInput.AlignHCenter
        verticalAlignment : TextInput.AlignVCenter
    }
    Label
    {
        id: carBrendlabel
        width: carOwnerlabel.width
        anchors.left: carOwnerlabel.left
        anchors.verticalCenter: carBrendline.verticalCenter
        text: qsTr("Brend :")
        color: "whitesmoke"
    }
    TextField
    {
        id: carBrendline
        width: carOwnerline.width
        anchors.left: carOwnerline.left
        anchors.top : carOwnerline.bottom
        enabled: false
        placeholderText: qsTr("%1").arg(carPage.carBrend)
        placeholderTextColor: "papayawhip"
        horizontalAlignment : TextInput.AlignHCenter
        verticalAlignment : TextInput.AlignVCenter
    }
    Label
    {
        id: carModellabel
        width: carOwnerlabel.width
        anchors.left: carOwnerlabel.left
        anchors.verticalCenter: carModelline.verticalCenter
        text: qsTr("Model :")
        color: "whitesmoke"
    }
    TextField
    {
        id: carModelline
        width: carOwnerline.width
        anchors.left: carBrendline.left
        anchors.top : carBrendline.bottom
        enabled: false
        placeholderText: qsTr("%1").arg(carPage.carModel)
        placeholderTextColor: "papayawhip"
        horizontalAlignment : TextInput.AlignHCenter
        verticalAlignment : TextInput.AlignVCenter
    }
    Label
    {
        id: carColorlabel
        width: carOwnerlabel.width
        anchors.left: carOwnerlabel.left
        anchors.verticalCenter: carColorline.verticalCenter
        text: qsTr("Color :")
        color: "whitesmoke"
    }
    TextField
    {
        id: carColorline
        width: carOwnerline.width
        anchors.left: carModelline.left
        anchors.top : carModelline.bottom
        enabled: false
        placeholderText: qsTr("%1").arg(carPage.carColor)
        placeholderTextColor: "papayawhip"
        horizontalAlignment : TextInput.AlignHCenter
        verticalAlignment : TextInput.AlignVCenter
    }
    Label
    {
        id: carYearlabel
        width: carOwnerlabel.width
        anchors.left: carOwnerlabel.left
        anchors.verticalCenter: carYearline.verticalCenter
        text: qsTr("Year  :")
        color: "whitesmoke"
    }
    TextField
    {
        id: carYearline
        width: carOwnerline.width
        anchors.left: carColorline.left
        anchors.top : carColorline.bottom
        enabled: false
        placeholderText: qsTr("%1").arg(carPage.year)
        placeholderTextColor: "papayawhip"
        horizontalAlignment : TextInput.AlignHCenter
        verticalAlignment : TextInput.AlignVCenter
    }
    Frame
    {
        visible: carPage.visRental
        id: carRental
        anchors.left: carOwnerline.right
        anchors.right: carFrame.right
        anchors.top: carOwnerline.top
        anchors.leftMargin: 10
        anchors.bottom: carYearline.bottom
        Label
        {
            id: topNote
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            text: (carPage.visFrame && carPage.visRental) ? qsTr("Ad is accessible on board's") : qsTr("Ad is gone on to renters")
            color: "whitesmoke"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        Label
        {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter : carFromline.verticalCenter
            text: "from :"
            color: "whitesmoke"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        TextField
        {
            id: carFromline
            width: carOwnerline.width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top : topNote.bottom
            enabled: false
            placeholderText: qsTr("%1").arg(carPage.carFrom)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        Label
        {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter : carToline.verticalCenter
            text: "to :"
            color: "whitesmoke"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        TextField
        {
            id: carToline
            width: carOwnerline.width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top : carFromline.bottom
            enabled: false
            placeholderText: qsTr("%1").arg(carPage.carTo)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        Label
        {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter : carToline.verticalCenter
            text: "cost :"
            color: "whitesmoke"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        TextField
        {
            id: carCostline
            width: carOwnerline.width
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top : carToline.bottom
            enabled: false
            placeholderText: qsTr("%1 Rubels per day").arg(carPage.carCost)
            placeholderTextColor: "papayawhip"
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        Button
        {
            visible: carPage.buttonVisible
            id: rentalRespond
            anchors.top: carCostline.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Respond"
            onClicked:
            {
                window.rentalRespond( carPage.carOwner, carPage.carName)
            }
        }
    }
    Frame
    {
        visible: carPage.visFrame
        id: carFrame
        anchors.left:  carImage.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.topMargin: 10
        anchors.top : carImage.bottom
        height: (carFromDelegate.height + carToDelegate.height) * 1.2
        Label
        {
            id: carFrom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: carFromDelegate.verticalCenter
            text: qsTr("from date:")
        }
        ItemDelegate {
            id: carFromDelegate
            anchors.left: carFrom.right
            anchors.leftMargin: 10
            anchors.top:  carFrame.top
            anchors.topMargin: -10
            text: from.fromDate.toLocaleDateString("mm-dd-yyyy")
            onClicked:
            {
                grid.local = from.fromDate
                grid.trueLocal = from.fromDate
                from.isMe = true
                spaceCalendar.open()
            }
        }
        Label
        {
            id: carTo
            anchors.left: carFrom.left
            anchors.verticalCenter: carToDelegate.verticalCenter
            text: qsTr("to date:")
        }
        ItemDelegate
        {
            id: carToDelegate
            anchors.left: carFromDelegate.left
            anchors.top: carFromDelegate.bottom
            text: to.toDate.toLocaleDateString("mm-dd-yyyy")
            onClicked:
            {
                grid.local = to.toDate
                grid.trueLocal = to.toDate
                to.isMe = true
                spaceCalendar.open()
            }
        }

        Slider
        {
            id: carCostSileder
            anchors.left: carFromDelegate.right
            height: carFromDelegate.height
            anchors.right: carOwnerline.right
            value:  carPage.cost / 500.0
            stepSize: 1.0 / 500.0
            snapMode: Slider.SnapAlways
            onMoved:
            {
                carPage.cost = value * 500.0
            }
        }
        TextField
        {
            id: carCostText
            placeholderText: qsTr("%1 Rub per day").arg(carPage.cost)
            placeholderTextColor: "papayawhip"
            text: placeholderText
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
            height: carFromDelegate.height
            anchors.left: carCostSileder.right
            anchors.verticalCenter: carCostSileder.verticalCenter
        }
        Button
        {
            text: (carPage.visFrame && carPage.visRental) ? qsTr("edit rental offer") : qsTr("confirm rental offer")
            anchors.horizontalCenter: carCostSileder.horizontalCenter
            anchors.verticalCenter: carToDelegate.verticalCenter
            height: carToDelegate.height
            onClicked:
            {
                window._carOwner = carPage.carOwner
                window._carName  = carPage.carName
                window._carBrend = carPage.carBrend
                window._carModel = carPage.carModel
                window._carColor = carPage.carColor
                window._carNumber = carPage.carNumber
                window._carPics = carPage.carPics
                window._carConfirm = carPage.carConfirm
                window._login = carPage.login
                window._year =  carPage.year
                window._cost =  carPage.cost
                window.confirmRental()
            }
        }
    }
    Frame
    {
        id: oneChatWindow
        visible: !window._multiplyChatWindow
        objectName: "oneChatWindow"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: carImage.bottom
        anchors.topMargin: 10
        anchors.left: carImage.left
        anchors.right: carRental.right
        Rectangle
        {
            id: oneChatUserName
            visible: true //model.me
            anchors.top: oneChatWindow.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: oneChatView.horizontalCenter
            color: "royalblue"
            radius: 15
            width: oneChatUserNameMessage.width *  1.5
            height: oneChatUserNameMessage.height *  1.5
            Text {
                anchors.centerIn: parent
                id: oneChatUserNameMessage
                text: qsTr("%1").arg(carPage.carRentUser)
                color: "whitesmoke"
                horizontalAlignment : Text.AlignHCenter
                verticalAlignment : Text.AlignVCenter
                font.pointSize: 8
            }
        }
        SwipeView
        {
            visible: true
            id: oneChatView

            anchors.bottom: oneChatLine.top
            anchors.bottomMargin: 10
            orientation: Qt.Vertical
            width: parent.width
            height: parent.height * 0.7
            ListView
            {
                Connections
                {
                    target: chat
                    onSetLast:
                    {
                        listone.positionViewAtEnd()
                    }
                }
                id: listone
                width: parent.width
                height: parent.height
                model: chat
                delegate: Rectangle
                {
                    height: textLineChat.height
                    width: oneChatView.width
                    color: "transparent"
                    Rectangle
                    {
                        id: textLineChat
                        visible: model.chatIsMe
                        anchors.right: parent.right
                        color: "royalblue"
                        radius: 15
                        width: oneChatMessage.width *  1.5
                        height: oneChatMessage.height *  1.5
                        Text {
                            id: oneChatMessage
                            anchors.centerIn: parent
                            text: qsTr("%1").arg(model.chatIsText)
                            color: "whitesmoke"
                            horizontalAlignment : Text.AlignHCenter
                            verticalAlignment : Text.AlignVCenter
                            font.pointSize: 8
                        }
                    }
                    Rectangle
                    {
                        visible: !model.chatIsMe
                        anchors.left: parent.left
                        color: "royalblue"
                        radius: 15
                        width: oneChatMessageleft.width *  1.5
                        height: oneChatMessageleft.height *  1.5
                        Text {
                            id: oneChatMessageleft
                            anchors.centerIn: parent
                            text: qsTr("%1").arg(model.chatIsText)
                            color: "whitesmoke"
                            horizontalAlignment : Text.AlignHCenter
                            verticalAlignment : Text.AlignVCenter
                            font.pointSize: 8
                        }
                    }
                }
            }
        }
        TextField
        {
            id: oneChatLine
            anchors.left: parent.left
            //anchors.right: oneChatSend.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            width: parent.width * 0.8
            horizontalAlignment : TextInput.AlignHCenter
            verticalAlignment : TextInput.AlignVCenter
        }
        ItemDelegate
        {
            id: oneChatSend
            anchors.left: oneChatLine.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.verticalCenter: oneChatLine.verticalCenter
            height: oneChatLine.height * 0.8
            Rectangle
            {
                anchors.fill: parent
                color: "royalblue"
                radius: 15
                Text {
                    anchors.fill: parent
                    text: qsTr("Send")
                    color: "whitesmoke"
                    horizontalAlignment : TextInput.AlignHCenter
                    verticalAlignment : TextInput.AlignVCenter
                }
            }
            onClicked:
            {
                window.chatPush(oneChatLine.text, carPage.carName)
                oneChatLine.clear()
            }
        }
    }
    Frame
    {
        visible: window._multiplyChatWindow
        id: multiplyChatWindow
        objectName: "multiplyChatWindow"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: carFrame.bottom
        anchors.topMargin: 10
        anchors.left: carImage.left
        anchors.right: carRental.right
        Frame
        {
            id: multiChatList
            anchors.left : parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width * 0.2
            SwipeView
            {
                visible: true
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                width: parent.width
                height: multiChatList.height * 0.6
                ListView
                {
                    width: parent.width
                    height: parent.height
                    model: chatList
                    delegate:
                        Rectangle
                        {
                            id: rectChatWithMan
                            //anchors.centerIn: parent
                            width: parent.width
                            height: chatWithMan.height * 1.5
                            radius: 15
                            color: (model.chatActive == model.index) ? "royalblue" : "transparent"
                            ItemDelegate{
                                anchors.fill: parent
                                Text {
                                    id: chatWithMan
                                    anchors.centerIn: parent
                                    text: qsTr("%1").arg(model.chatWithMan)
                                    color: "whitesmoke"
                                    horizontalAlignment : Text.AlignHCenter
                                    verticalAlignment : Text.AlignVCenter
                                    font.pointSize: 8
                                }
                                onClicked:
                                {
                                    window.setChatN(model.index);
                                }
                         }
                    }
                }
            }
        }
        Frame
        {
            anchors.left : multiChatList.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            SwipeView
            {
                visible: true
                id: multiChatView

                anchors.bottom: multiChatLine.top
                anchors.bottomMargin: 10
                orientation: Qt.Vertical
                width: parent.width
                height: parent.height * 0.6
                ListView
                {
                    Connections
                    {
                        target: chat
                        onSetLast:
                        {
                            listmulti.positionViewAtEnd()
                        }
                    }
                    id: listmulti
                    width: parent.width
                    height: parent.height
                    model: chat
                    delegate: Rectangle
                    {
                        height: multiTextLineChat.height
                        width: multiChatView.width
                        color: "transparent"
                        Rectangle
                        {
                            id: multiTextLineChat
                            visible: model.chatIsMe
                            anchors.right: parent.right
                            color: "royalblue"
                            radius: 15
                            width: multiChatMessage.width *  1.5
                            height: multiChatMessage.height *  1.5
                            Text {
                                id: multiChatMessage
                                anchors.centerIn: parent
                                text: qsTr("%1").arg(model.chatIsText)
                                color: "whitesmoke"
                                horizontalAlignment : Text.AlignHCenter
                                verticalAlignment : Text.AlignVCenter
                                font.pointSize: 8
                            }
                        }
                        Rectangle
                        {
                            visible: !model.chatIsMe
                            anchors.left: parent.left
                            color: "royalblue"
                            radius: 15
                            width: multiChatMessageleft.width *  1.5
                            height: multiChatMessageleft.height *  1.5
                            Text {
                                id: multiChatMessageleft
                                anchors.centerIn: parent
                                text: qsTr("%1").arg(model.chatIsText)
                                color: "whitesmoke"
                                horizontalAlignment : Text.AlignHCenter
                                verticalAlignment : Text.AlignVCenter
                                font.pointSize: 8
                            }
                        }
                    }
                }
            }
            TextField
            {
                id: multiChatLine
                anchors.left: parent.left
                //anchors.right: oneChatSend.left
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                width: parent.width * 0.8
                horizontalAlignment : TextInput.AlignHCenter
                verticalAlignment : TextInput.AlignVCenter
            }
            ItemDelegate
            {
                id: multiChatSend
                anchors.left: multiChatLine.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.verticalCenter: multiChatLine.verticalCenter
                height: multiChatLine.height * 0.8
                Rectangle
                {
                    anchors.fill: parent
                    color: "royalblue"
                    radius: 15
                    Text {
                        anchors.fill: parent
                        text: qsTr("Send")
                        color: "whitesmoke"
                        horizontalAlignment : TextInput.AlignHCenter
                        verticalAlignment : TextInput.AlignVCenter
                    }
                }
                onClicked:
                {
                    window.chatPush(multiChatLine.text, carPage.carName)
                    multiChatLine.clear()
                }
            }
        }
    }
}
