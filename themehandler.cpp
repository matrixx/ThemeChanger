#include "themehandler.h"
#include <QDir>
#include <QSettings>
#include <MGConfItem>

static const QString THEMEDIR = "/usr/share/themes/";


ThemeHandler::ThemeHandler(QObject *parent) :
	QObject(parent), m_model(new ThemeModel(this)), m_currentThemeIndex(-1), m_gconfItem(0)//, m_rebootProcess(0)
{
	initializeGConfItem();
	populateModel();
}

void ThemeHandler::changeTheme(int index)
{
	if (index >= 0 && index != m_currentThemeIndex) {
		m_currentThemeIndex = index;
		m_gconfItem->set(m_model->data(m_model->index(index, 0), ThemeModel::ThemeRole));
		emit newThemeApplied();
	} else {
		emit themeChangeCanceled();
	}
}

QList<ThemeModel::ThemeInfo> ThemeHandler::findAvailableThemes()
{
	QList<ThemeModel::ThemeInfo> themes;

	// find all directories under the theme directory
	QDir themeDir(THEMEDIR);
	const QFileInfoList directories = themeDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	qDebug("found %d directories", directories.count());
	foreach(const QFileInfo & dir, directories) {
		ThemeModel::ThemeInfo info;
		const QSettings* themeIndexFile = themeFile(dir.baseName());
		if (!themeIndexFile)
			continue;

		// check if this theme is visible
		if (!themeIndexFile->value("X-MeeGoTouch-Metatheme/X-Visible", true).toBool()) {
			delete themeIndexFile;
			continue;
		}

		info.theme = dir.baseName();
		info.themeName = themeIndexFile->value("Desktop Entry/Name", "").toString();
		info.themeIcon = themeIndexFile->value("X-MeeGoTouch-Metatheme/X-Icon", "").toString();

		// remove this again, when duitheme is phased out
		if (info.themeIcon.isEmpty()) {
			info.themeIcon = themeIndexFile->value("X-DUI-Metatheme/X-Icon", "").toString();
		}
		// end remove

		// ok it's a valid theme. Add it to list of themes
		themes.append(info);
		delete themeIndexFile;
	}
	return themes;
}

ThemeModel* ThemeHandler::themeModel()
{
	return m_model;
}

void ThemeHandler::initializeGConfItem()
{
	m_gconfItem = new MGConfItem("/meegotouch/theme/name", this);
	connect(m_gconfItem, SIGNAL(valueChanged()), this, SLOT(updateCurrentTheme()));
}

void ThemeHandler::populateModel()
{
	QList<ThemeModel::ThemeInfo> themes = findAvailableThemes();
	foreach (ThemeModel::ThemeInfo theme, themes) {
		m_model->addTheme(theme);
	}
}

void ThemeHandler::fetchCurrentTheme()
{
	int index = -1;
	QString currentTheme = m_gconfItem->value().toString();
	if (currentTheme.isEmpty()) {
		currentTheme = "blanco";
	}
	index = m_model->indexOf(currentTheme);
	if (index >= 0) {
		m_currentThemeIndex = index;
		emit currentThemeChanged(index);
	}
}

QSettings* ThemeHandler::themeFile(const QString& theme)
{
	// Determine whether this is a m theme:
	// step 1: we need to have index.theme file
	QDir themeDir(THEMEDIR);

	const QString themeIndexFileName = themeDir.absolutePath() + QDir::separator() + theme + QDir::separator() + "index.theme";
	if (!QFile::exists(themeIndexFileName))
		return NULL;

	// step 2: it needs to be a valid ini file
	QSettings *themeIndexFile = new QSettings(themeIndexFileName, QSettings::IniFormat);
	if (themeIndexFile->status() != QSettings::NoError) {
		delete themeIndexFile;
		return NULL;
	}

	// step 3: we need to have X-MeeGoTouch-Metatheme group in index.theme
	// remove the X-DUI-Metatheme statement again when duitheme is phased out.
	if ((!themeIndexFile->childGroups().contains(QString("X-MeeGoTouch-Metatheme")))
		&&(!themeIndexFile->childGroups().contains(QString("X-DUI-Metatheme")))) {
		delete themeIndexFile;
		return NULL;
	}
	return themeIndexFile;
}

void ThemeHandler::updateCurrentTheme()
{
	QString themeName = m_gconfItem->value().toString();
	int index = m_model->indexOf(themeName);
	if (index >= 0) {
		emit currentThemeChanged(index);
	}
}


