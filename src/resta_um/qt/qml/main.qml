import QtQml 2.11
import QtQuick 2.6
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window

    width: 500
    height: 500
    visible: true

    property int modelScale: width / game.width

    property int selectionX: 3
    property int selectionY: 3
    property bool moving: false

    Item {
        anchors.fill: parent

        Rectangle {
            id: background
            color: "black"
            anchors.fill: parent
        }

        focus: true
        Keys.onPressed: {
            if (event.key == Qt.Key_Left) {
                if (moving)
                {
                    game.left(selectionX, selectionY);
                    moving = false;
                    event.accepted = true
                }
                else if (selectionY > 0)
                {
                    selectionY--;
                    event.accepted = true
                }
            }
            else if (event.key == Qt.Key_Right) {
                if (moving)
                {
                    game.right(selectionX, selectionY);
                    moving = false;
                    event.accepted = true
                }
                else if (selectionY < game.width - 1)
                {
                    selectionY++;
                    event.accepted = true
                }
            }
            else if (event.key == Qt.Key_Up) {
                if (moving)
                {
                    game.up(selectionX, selectionY);
                    moving = false;
                    event.accepted = true
                }
                else if (selectionX > 0)
                {
                    selectionX--;
                    event.accepted = true
                }
            }
            else if (event.key == Qt.Key_Down) {
                if (moving)
                {
                    game.down(selectionX, selectionY);
                    moving = false;
                    event.accepted = true
                }
                else if (selectionX < game.height - 1)
                {
                    selectionX++;
                    event.accepted = true
                }
            }
            else if (event.key == Qt.Key_Space) {
                if(game.board.isPiece(game.board.positionToIndex(selectionX, selectionY)))
                    moving = !moving;
            }
            else if (event.key == Qt.Key_R) {
                game.reset();
                moving = false;
                event.accepted = true
            }
        }

        Grid {
            anchors.fill: parent
            rows: game.width
            columns: game.height
            spacing: modelScale * 0.1

            Repeater {
                id: board
                model: game.board

                delegate: Rectangle {
                    property int row: game.board.indexToPosition(index).x
                    property int column: game.board.indexToPosition(index).y
                    property bool selected: row == window.selectionX && column == window.selectionY

                    width: modelScale * 0.9
                    height: modelScale * 0.9
                    radius: width * 0.5

                    border.width: 2
                    border.color: selected ? "red" : game.board.isNotUsed(index) ? "black" : "white"

                    color: game.board.isPiece(index) ? selected && moving ? "red" : "blue" : "black"
                }
            }
        }
    }
}
