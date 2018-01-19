import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item1
    property alias playBut: playBut
    property alias stopBut: stopBut

    Button {
        id: playBut
        y: 0
        text: qsTr("Play")
        anchors.left: parent.left
        anchors.leftMargin: 0
        transformOrigin: Item.Center
    }

    Button {
        id: stopBut
        x: -6
        y: 0
        text: qsTr("Stop")
        transformOrigin: Item.Center
        anchors.leftMargin: 106
        anchors.left: parent.left
    }
}
