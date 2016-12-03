import QtQuick 2.7
import QtQuick.Window 2.2
import app.types 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Google image collector")

    MainForm {
        id: myForm
        anchors.fill: parent
        searchText.placeholderText: qsTr("Enter your keyword to search here")

        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + searchText.text + '"'))
        }

        searchText.onAccepted: {
            myloader.searchFor(searchText.text)
        }
    }

    GoogleLoader {
        id: myloader
        onHereYouGo: {
            console.log(qsTr('Received some data: "' + gReply + '"'))
            myForm.outputText.text = gReply

            console.log('( ' + myForm.outputText.contentWidth + ',' + myForm.outputText.contentHeight + ')')
        }
    }
}
