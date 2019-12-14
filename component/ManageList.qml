import QtQuick 2.0
import QtQuick.Controls 2.4
Rectangle{
    Component{
        id: item
        ListViewItem{
            width: parent.width
            height: 52
            imageUrl: cover
            itemName: name
            itemIndex: index
            currentIndex: listview.currentIndex
            selection: MusicModel.isSelectOn
            onItemDoubleClick: {
                MusicController.openItemAt(index)
            }
            onItemClick: {
                listview.currentIndex = index
            }
        }
    }

    ListView{
        id: listview
        anchors.fill: parent
        model: MusicModel
        delegate: item
        spacing: 2
        cacheBuffer: 50
        focus: true
        currentIndex: -1
        ScrollBar.vertical: ScrollBar {
            parent: listview.parent
            anchors.top: listview.top
            anchors.left: listview.left
            anchors.bottom: listview.bottom
            width: 20

        }
        ScrollIndicator.vertical: ScrollIndicator {
            id: indicatorBar
            parent: listview.parent
            anchors.top: listview.top
            anchors.right:  listview.right
            anchors.bottom: listview.bottom
            width: 10
            Indicator{
               onClickIndicator: {
                   listview.positionViewAtIndex(currentIndicator, ListView.Beginning)
               }
            }
        }
        section.property: "name"
        section.criteria: ViewSection.FirstCharacter
        section.delegate: Rectangle {
            width: listview.width
            height: 25
            color: "#eb88ca"
            Text {
                text: section
                font.bold: true
                font.pixelSize: 18
            }
        }

    }
}


