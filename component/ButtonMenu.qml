import QtQuick 2.0
import QtGraphicalEffects 1.0
MouseArea{
    id: areaButton
    property alias buttonText: txt
    property alias buttonRectangle: rect
    property alias image: imageButton
    property url buttonImage: ""
    property url hoverImage: ""
    property url pressImage: ""
    property url activeImage: ""
    property bool presshold: false
    property bool active: false
    hoverEnabled: true
    Rectangle{
        id: rect
        anchors.fill: parent
        border.width: 0.5
        border.color: "#e6c6c6"
        visible: false
        Text {
            id: txt
            anchors.centerIn: parent
        } 
    }


    Image {
        id: imageHover
        anchors.centerIn: parent
        height: areaButton.height
        fillMode: Image.PreserveAspectFit
        source: hoverImage
        visible: false
        smooth: true
    }
    Image {
        id: imageButton
        height: areaButton.height
        fillMode: Image.PreserveAspectFit
        source: buttonImage
        smooth: true
    }
    states: [
        State {
            name: "active"
            when: areaButton.active
            PropertyChanges {
                target: imageButton
                source: activeImage==""?buttonImage:activeImage
            }
            PropertyChanges {
               target: imageHover
               visible: areaButton.containsMouse
            }
            PropertyChanges {
               target: rect
               color: "#e8d399"
            }

        },
        State {
            name: "persshold"
            when: areaButton.presshold
            PropertyChanges {
                target: imageButton
                source: pressImage==""?buttonImage:pressImage
            }
        },
        State {
            name: "press"
            when: areaButton.pressed
            PropertyChanges {
                target: imageButton
                source: pressImage==""?buttonImage:pressImage
            }

        },
        State {
            name: "hover"
            when: areaButton.containsMouse
            PropertyChanges {
               target: imageHover
               visible: true
            }
            PropertyChanges {
               target: rect
               color: "#f0dea3"
            }

        }
    ]
    onPressAndHold: {
        presshold = true
    }
    onReleased: {
        presshold = false
    }
}
