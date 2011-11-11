import QtQuick 1.0
import com.nokia.meego 1.0

Item {
	id: themeDelegate
	width: parent.width
	height: 80
	Button {
		id: button
		property bool current: (themeSelector.currentIndex == index)
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.topMargin: 5
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 5
		checkable: true
		text: themeName
		iconSource: "file:///usr/share/themes/" + theme + "/meegotouch/icons/" + themeIcon + ".png"
		onClicked: {
			if (checked) {
				themeSelector.currentIndex = index
				themeSelector.currentTheme = themeName
				themeSelector.delegateClicked()
			}
		}
		onCurrentChanged: {
			if (!current && checked) checked = false
			if (current && !checked) checked = true
		}
	}
}
