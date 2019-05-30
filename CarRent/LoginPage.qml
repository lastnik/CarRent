import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Styles 1.4
Window {
    Material.theme: Material.Dark

    id : loginWin
    width: 640
    height: 480
    visible: true
    title: qsTr("Login")
    Connections
    {
        target: login
        onLoginPage:
        {
           //if (stackView.depth > 1)
           stackView.pop()
           stackView.push(logPage)
        }
    }
    Connections
    {
        target: login
        onWatingPage:
        {
            //if (stackView.depth > 1)
            stackView.pop()
            stackView.push("qrc:/pages/pages/WaitingPage.qml")
        }
    }
    Connections
    {
        target: login
        onFinishLogin:
        {
            loginWin.close()
        }
    }
    Connections
    {
        target:  login
        onLogFail:
        {

        }
    }
    StackView
    {
        id: stackView
        initialItem: Page
        {
            id: logPage
            //anchors.fill: parent
            Image {
                id: backGround
                height: parent.height
                width : parent.width
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/source/pics/highWay.png"
                TextField {
                    x:parent.width * 0.5 - width / 2
                    y:parent.height * 0.6 - height / 2
                    width:  parent.width * 0.3
                    id : logName
                    objectName: "logName"
                    placeholderText: qsTr("Enter login name")
                    placeholderTextColor: "papayawhip"//Material.color(Material.Pink)

                }
                TextField {
                    anchors.top: logName.bottom
                    anchors.left: logName.left

                    id : password
                    objectName: "password"
                    width:  parent.width * 0.3
                    placeholderText: qsTr("Enter password")
                    placeholderTextColor: "papayawhip"//Material.color(Material.Pink)
                }
                Button
                {
                    id: tryLogin
                    objectName: "tryLogin"
                    anchors.top: password.bottom
                    anchors.left: password.left
                    width: parent.width * 0.3
                    height: password.height
                    Text
                    {
                        id:textLog
                        anchors.centerIn: parent
                        text: "Loggin"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment  : Text.AlignVCenter
                        color: "whitesmoke"//Material.color(Material.Pink)
                        font.pointSize: 10
                    }

                }
                Button
                {
                    id: registration
                    objectName: "registration"
                    anchors.top: tryLogin.bottom
                    anchors.left: tryLogin.left
                    width: parent.width * 0.3
                    height: password.height
                    Text
                    {
                        id:textReg
                        anchors.centerIn: parent
                        text: "Registration"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment  : Text.AlignVCenter
                        color: "whitesmoke"//Material.color(Material.Pink)
                        font.pointSize: 10
                    }

                }
                Rectangle
                {
                    x: parent.width  / 2 - errorCode.width / 2
                    y: parent.height  / 3 - errorCode.height
                    Text
                    {
                        id: errorCode
                        objectName: "errorCode"
                        visible: false
                        anchors.centerIn: parent
                        width: parent.width * 0.8
                        height: logName.height
                        text: "Something goes wrong, try again"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment  : Text.AlignVCenter
                        color: Material.color(Material.Pink)//"white"
                        font.pointSize: 10
                    }
                }
            }
        }
        anchors.fill: parent
    }
}
