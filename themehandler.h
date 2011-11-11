#ifndef THEMEHANDLER_H
#define THEMEHANDLER_H

#include <QObject>
#include "thememodel.h"

class MGConfItem;
class QSettings;

class ThemeHandler : public QObject
{
    Q_OBJECT
public:
	explicit ThemeHandler(QObject *parent = 0);
	void fetchCurrentTheme();

signals:
	void currentThemeChanged(int index);
	void newThemeApplied();
	void themeChangeCanceled();

public slots:
	Q_INVOKABLE void changeTheme(int index);
	Q_INVOKABLE ThemeModel* themeModel();

private slots:
	void updateCurrentTheme();

private:
	QList<ThemeModel::ThemeInfo> findAvailableThemes();
	void initializeGConfItem();
	void populateModel();
	QSettings* themeFile(const QString& theme);

	ThemeModel* m_model;
	int m_currentThemeIndex;
	MGConfItem* m_gconfItem;
//	QProcess* m_rebootProcess;
};

#endif // THEMEHANDLER_H
