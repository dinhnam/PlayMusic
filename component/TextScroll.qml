import QtQuick 2.0
Item{
    property bool run: false
    property alias title: txt
    property bool runtext: run && elidetxt.truncated
    layer.enabled: true
    Text{
        id: elidetxt
        width: parent.width
        text: txt.text
        elide: Text.ElideRight
        visible: !runtext
        color: txt.color
        font: txt.font
    }

    Text {
        id: txt
        visible: runtext
        PropertyAnimation on x{
            loops: Animation.Infinite
            from: 0
            to: -(txt.width + 100)
            duration: 20*txt.width
            running: runtext
        }
    }
    Text{
       text: txt.text
       color: txt.color
       font: txt.font
       anchors{
           left: txt.right
           leftMargin: 100
       }
       visible: runtext
    }
}


