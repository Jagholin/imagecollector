import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    property alias text: myTextField

    color: "lightBlue"
    border.width: 1
    border.color: "black"

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.HorizontalAndVerticalFlick

        leftMargin: 2
        rightMargin: 2
        topMargin: 2
        bottomMargin: 2

        clip: true

        contentWidth: myTextField.contentWidth
        contentHeight: myTextField.contentHeight

        ScrollBar.vertical: ScrollBar {

        }

        ScrollBar.horizontal: ScrollBar {

        }

        Text {
            id: myTextField
            text: qsTr("text")

            wrapMode: Text.WordWrap
        }
    }
}
