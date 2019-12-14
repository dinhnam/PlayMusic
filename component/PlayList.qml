import QtQuick 2.0
import QtQuick.Controls 2.4
Rectangle {
    Component{
        id: musicItem
        ListViewItem{
            width: parent.width
            height: 52
            imageUrl: cover
            itemName: name
            itemIndex: index
            selection: MusicModel.isSelectOn
            currentIndex: PlayListModel.currentIndex
            onItemClick: {
                MusicController.setCurrentIndex(index)
            }
            onItemPressHold: {
               hold = true
            }
            onItemRelease: {
                hold = false
            }
        }
    }

    ListView{
        id: listview
        anchors.fill: parent
        model: MusicModel
        delegate: musicItem
        spacing: 2
        cacheBuffer: 50
        focus: true
        currentIndex: PlayListModel.currentIndex
        ScrollBar.vertical: ScrollBar {
            parent: listview.parent
            anchors.top: listview.top
            anchors.left: listview.left
            anchors.bottom: listview.bottom
            width: 20

        }
    }
}
