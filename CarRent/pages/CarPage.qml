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
    property real   cost:       100.0
    property bool   visFrame     : window._visFrame
    property bool   visRental    : window._visRental
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
        fillMode: Image.PreserveAspectCrop
        source: "file:/" + carPics
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
            text: qsTr("confirm rental offer")
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
}
