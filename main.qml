import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0
import app.types 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Google image collector")

    Settings {
        id: appSettings
        property string searchEngineId: ""
        property string apiKey: ""
    }

    AnimatedLayout {
        id: mainWindowLayout
        anchors.fill:parent
        //currentIndex: 0

        MainForm {
            objectName: "aForm"
            id: myForm
            //anchors.fill: parent
            width: mainWindow.width
            height: mainWindow.height
            searchText.placeholderText: qsTr("Enter your keyword to search here")

            mouseArea.onClicked: {
                console.log(qsTr('Clicked on background. Text: "' + searchText.text + '"'))
            }

            searchText.onAccepted: {
                myloader.searchFor(searchText.text, appSettings.searchEngineId, appSettings.apiKey)
            }

            settingsBtn.onClicked: {
                mainWindowLayout.currentIndex = 1
            }
        }

        Rectangle {
            objectName: "aRectangle"
            border.color: "black"
            border.width: 1
            color: "lightgreen"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 5

                GridLayout {
                    columns: 2
                    Layout.alignment: Qt.AlignTop

                    Label {
                        text: qsTr("Custom search machine id:")
                    }

                    TextField {
                        id: searchMachineId
                        text: appSettings.searchEngineId
                        placeholderText: "your search id"
                    }

                    Label {
                        text: qsTr("Google API key:")
                    }

                    TextField {
                        id: googleApiKey
                        text: appSettings.apiKey
                        placeholderText: "Your Google API Key"
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignTop
                    text: qsTr("OK")
                    onClicked: {
                        appSettings.searchEngineId = searchMachineId.text
                        appSettings.apiKey = googleApiKey.text
                        mainWindowLayout.currentIndex = 0
                    }
                }
            }

        }
    }


    GoogleLoader {
        id: myloader
        onNewPictureUrl: {
            console.log(qsTr('Received some data: "' + pictureUrl + '"'))
            myForm.outputText.text += pictureUrl + "\n"

            console.log('( ' + myForm.outputText.contentWidth + ',' + myForm.outputText.contentHeight + ')')
        }
    }
}
