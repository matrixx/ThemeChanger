import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage
	Rectangle {
		id: splash
		property int side: (parent.width >= parent.height) ? parent.height : parent.width
		width: side - 130;
		height: side - 130;
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter
		visible: true
		radius: 10
		border.width: 1
		border.color: 'white'
		z: 100
		gradient: Gradient {
			GradientStop { id: stop1; color: 'grey'; position: 0.0 }
			GradientStop { id: stop2; color: Qt.darker('grey', 1.3); position: 1.0 }
		}
		Text {
			id: infotext
			width: parent.width - 40
			wrapMode: Text.WordWrap
			anchors.centerIn: parent
			color: 'white'
			font { family: "Helvetica"; pixelSize: 20; bold: true }
			text: "Welcome to use ThemeChanger by Leimu. This software is licenced under LGPL and is powered by Qt. Theme changer code adapted from Widgetsgallery MeeGo Touch demo application. Note that in order to change theme, you need to reboot your device afterwards. Usage only in your own responsibility."
		}
		MouseArea {
			onClicked: splash.visible = false
			anchors.fill: parent
		}
	}

	Rectangle {
		color: 'white'
		anchors.fill: parent
		radius: 10
		Rectangle {
			id: title
			height: 80
			anchors.margins: 10
			anchors.left: parent.left
			anchors.top: parent.top
			anchors.right: parent.right
			radius: 5
			gradient: Gradient {
				GradientStop { position: 0.0; id: stop3; color: '#dddddd' }
				GradientStop { position: 1.0; id: stop4; color: 'white' }
			}
			Text {
				anchors.centerIn: parent
				color: '#333333'
				text: "ThemeChanger"
				font { pixelSize: 24 }
			}
		}

		ListView {
			id: themeSelector
			property string currentTheme: ""
			function delegateClicked() {
				confirmDialog.open()
			}
			anchors.margins: 10
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			height: parent.height - 110
			model: themeModel
			delegate: ThemeDelegate {}
		}
	}
	QueryDialog {
		id: confirmDialog
		titleText: "Do you want to apply theme " + themeSelector.currentTheme + "?"
		message: "Note that you need to reboot your device after selecting 'Apply' for theme to apply correctly"
		acceptButtonText: "Apply"
		rejectButtonText: "Cancel"
		onAccepted: themeHandler.changeTheme(themeSelector.currentIndex)
	}
	QueryDialog {
		id: rebootDialog
		titleText: "Theme applied successfully"
		message: "Now you need to reboot your device to see the new theme"
		acceptButtonText: "OK"
	}
	QueryDialog {
		id: sameDialog
		titleText: themeSelector.currentTheme + " is already applied"
		message: "Please select another theme"
		acceptButtonText: "OK"
	}
	Connections {
		target: themeHandler
		onCurrentThemeChanged: {
			console.debug("current index is going to be changed to" + index)
			themeSelector.currentIndex = index;
		}
		onNewThemeApplied: {
			rebootDialog.open();
		}
		onThemeChangeCanceled: {
			sameDialog.open();
		}
	}
}


