import QtQuick 2.0

Rectangle {
    border.width: 1
    border.color: "#e6c6c6"
    TextInput{
        id: txtSearch
        height: 40
        anchors{
            left: parent.left
            right: btnSearch.left
            leftMargin: 5
        }
        verticalAlignment: Text.AlignVCenter
        color: "black"
        text: ""
        font.pixelSize: 18
        onTextChanged: {
            if(txtSearch.focus == true){
                MusicController.searchItems(txtSearch.text)
            }
        }

    }
    ButtonMenu{
        id: btnSearch
        width: 40
        height: 40
        anchors.right: parent.right
        buttonRectangle.visible: true
        buttonImage: "qrc:/imgSrc/searchIcon.png"
        image.width: 30
        onClicked: {
            if(txtSearch.focus == true){
                MusicController.searchItems(txtSearch.text)
            }
            txtSearch.focus = true
        }
    }
}
