import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: mainLayout
    default property var layoutChildren
    property Component itemDelegate: Qt.createComponent("AnimatedLayoutItem.qml")

    Component.onCompleted: {
        // moving all layoutChildren to children property
    }

    property int currentIndex: 0

    onCurrentIndexChanged: {
        for (var i = 0; i < children.length; ++i) {
            if (i != currentIndex)
                children[i].state = "INACTIVE"
            else
                children[i].state = "ACTIVE"
        }
    }

    onLayoutChildrenChanged: {
        itemDelegate.createObject(mainLayout, {data: layoutChildren, state: children.length == currentIndex ? "ACTIVE" : "INACTIVE"})
    }
}
