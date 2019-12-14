import QtQuick 2.0
Item{
    id: itemIndicator
    signal clickIndicator()
    width: 20
    height: parent.height
    anchors.right: parent.right
    property int currentIndicator: 0
    Rectangle{
        anchors.fill: parent
        radius: 10
        opacity: 0.8
        color: "#db7272"
        Column{
            Repeater{
                model: MusicModel.indicatorIndex
                Item{
                    id: keysearch
                    width: 20
                    height: listview.height /28
                    Text {
                        id: keyname
                        anchors.centerIn: parent
                        text: modelData.key
                        font.bold: true
                        color: "#823431"
                    }
                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                           itemIndicator.currentIndicator = modelData.value
                           clickIndicator()
                        }
                        onEntered: {
                            keyname.color = "yellow"
                        }
                        onExited: {
                            keyname.color = "#823431"
                        }
                    }
                }
            }
        }
    }
}


