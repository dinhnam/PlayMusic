import QtQuick 2.0
import QtQuick.Controls 1.4
Item{
    id: item
    signal itemClick()
    signal itemPressHold()
    signal itemRelease()
    signal itemEnter()
    signal itemDoubleClick()
    property int currentIndex: -1
    property int itemIndex: index
    property url imageUrl: ""
    property string itemName: ""
    property bool hold: false
    property bool selection: false
    property bool itemchecked: checked
    MouseArea
    {
        id: mouseareaitem
        width: parent.width
        height: parent.height
        //anchors.fill: parent
        anchors.centerIn: hold?undefined:parent
        drag.target: hold?mouseareaitem:undefined
        drag.axis: Drag.YAxis
        hoverEnabled: true
        Drag.active: hold
        Rectangle{
            id: rectDrag
            anchors.fill: parent
            color: index==currentIndex?"#ada061":"#c7b87b"
            scale: hold?0.95:1
            ImageCover{
                id: imgCover
                height: parent.height-4
                width: parent.height-4
                anchors{
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: 2
                }
                image: imageUrl
            }
            TextScroll{
                id: textScroll
                width: parent.width-imgCover.width-5
                height: 30
                run: index == currentIndex
                anchors {
                   top: parent.top
                   topMargin: 5
                   left: imgCover.right
                   leftMargin: 5
                }
                title{
                    color: "black"
                    text: itemName
                    font.pixelSize: 16
                }
            }
            CheckBox {
                anchors{
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: 5
                    right: parent.right
                    rightMargin: 20
                }
                visible: selection
                checked: itemchecked
                MouseArea{
                    id: areaCheckBox
                    anchors.fill: parent
                    onClicked: {
                        MusicController.checkItem(index);
                    }
                    onDoubleClicked: {
                        MusicController.checkAllItem(index);
                    }

                }

            }
        }
        onClicked: {
            itemClick()
        }
        onPressAndHold: {
            itemPressHold()
        }
        onReleased: {
            itemRelease()
        }
        onDoubleClicked: {
            itemDoubleClick()
        }

        DropArea {
           id: dropItem
           anchors.fill: parent
           onEntered: {
               itemEnter()
               console.log("item enter")
          }
       }
    }
}



