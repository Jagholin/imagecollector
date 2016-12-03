import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle1
    property alias mouseArea: mouseArea

    width: 600
    height: 600
    property alias outputText: outputWindow.text
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
            anchors.right: parent.right
            anchors.rightMargin: 200
            anchors.left: parent.left
            anchors.leftMargin: 200
            anchors.top: parent.top
            anchors.topMargin: 13
        }

        ScrollableTextField {
            id: outputWindow
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 59
        }
    }

}
