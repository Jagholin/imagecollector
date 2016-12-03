import QtQuick 2.7
import QtQuick.Window 2.2
import app.types 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainForm {
        id: myForm
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }

    GoogleLoader {
        id: myloader
        onHereYouGo: {
            console.log(qsTr('Received some data: "' + gReply + '"'))
            myForm.textEdit.text = gReply
        }
    }
}
