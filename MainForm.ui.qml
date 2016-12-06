import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle1
    property alias mouseArea: mouseArea

    width: 600
    height: 600
    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias settingsBtn: settingsBtn
    property alias searchText: searchField

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        TextField {
            id: searchField
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 32
            anchors.right: parent.right
            anchors.rightMargin: 114
            anchors.top: parent.top
            anchors.topMargin: 13
        }

        Button {
            id: settingsBtn
            x: 492
            text: qsTr("Settings")
            anchors.top: parent.top
            anchors.topMargin: 13
            anchors.right: parent.right
            anchors.rightMargin: 8
        }

        ListView {
            id: listView
            orientation: ListView.Horizontal
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 59
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }
        }
    }

}
