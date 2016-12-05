import QtQuick 2.0

Item {
    id: layoutItem

    width: parent.width
    height: parent.height

    state: "INACTIVE"

    states: [
        State {
            name: "INACTIVE"
            PropertyChanges { target: layoutItem; x: -width; y: 0}
        },
        State {
            name: "ACTIVE"
            PropertyChanges { target: layoutItem; x: 0; y: 0}
        }
    ]

    Behavior on x {
        NumberAnimation {
            duration: 500
        }
    }

    transitions: [
        Transition {
            from: "INACTIVE"
            to: "ACTIVE"
            SequentialAnimation {
                PropertyAction { target: layoutItem; property: "x"; value: layoutItem.width }
                NumberAnimation {
                    target: layoutItem
                    property: "x"
                    duration: 500
                }
            }
        }
    ]
}
