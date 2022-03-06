import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.15
import LoadLibraryApp 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Load Library App")

    Page {
        anchors.fill: parent

        Flickable {
            id: flickable

            anchors.fill: parent
            anchors.margins: 10

            contentWidth: columnLayout.width
            contentHeight: columnLayout.height
            clip: true
            ScrollBar.vertical: ScrollBar {
                width: 20
            }

            ColumnLayout {
                id: columnLayout

                width: flickable.width - 20

                Text {
                    text: qsTr("patchEnabled: %1".arg(patchEnabled))
                }

                Text {
                    Layout.fillWidth: true

                    text: qsTr("LoadLibrary")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

                TextField {
                    id: fileNameInput

                    Layout.fillWidth: true

                    text: "my_opengl_driver.dll"
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    selectByMouse: true
                }

                Button {
                    text: qsTr("LoadLibrary")
                    onClicked: {
                        let ok = appUtils.loadLibrary(fileNameInput.text);
                        status.text = new Date() + " LoadLibrary(" + fileNameInput.text + ") = " + ok;
                    }
                }

                Text {
                    id: status
                    Layout.fillWidth: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

                TextArea {
                    id: pathTextArea

                    Layout.fillWidth: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    selectByMouse: true
                }

                RowLayout {

                    Button {
                        text: qsTr("Get Path")
                        onClicked: {
                            pathTextArea.text = appUtils.getEnv("PATH").replace(/;/g, '\n')
                        }
                    }

                    Button {
                        text: qsTr("Set Path")
                        onClicked: {
                            appUtils.putEnv("PATH", pathTextArea.text.replace(/\n/g, ';'));
                        }
                    }

                }

            }
        }

    }

    AppUtils {
        id: appUtils
    }
}
