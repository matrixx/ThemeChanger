#ifndef THEMEMODEL_H
#define THEMEMODEL_H

#include <QAbstractListModel>

class ThemeModel : public QAbstractListModel
{
    Q_OBJECT
public:
	struct ThemeInfo {
		QString theme;
		QString themeName;
		QString themeIcon;
	};
	enum MessageRoles { ThemeRole = Qt::UserRole + 1,
						NameRole, IconRole };
    explicit ThemeModel(QObject *parent = 0);

	void addTheme(const ThemeInfo &theme);
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	int indexOf(QString themeName);
signals:

public slots:

private:
	QList<ThemeInfo> m_themes;
};

#endif // THEMEMODEL_H
