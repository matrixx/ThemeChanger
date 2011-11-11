#include "thememodel.h"

ThemeModel::ThemeModel(QObject *parent) :
    QAbstractListModel(parent)
{
	QHash<int, QByteArray> roles;
	roles[ThemeRole] = "theme";
	roles[NameRole] = "themeName";
	roles[IconRole] = "themeIcon";
	setRoleNames(roles);
}

void ThemeModel::addTheme(const ThemeInfo& theme)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_themes << theme;
	endInsertRows();
}

bool ThemeModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (count > m_themes.size() || m_themes.size() <= 0) {
		return false;
	} else {
		beginRemoveRows(QModelIndex(), row, row + count);
		for (int i = row; i < row + count; ++i) {
			m_themes.removeAt(row);
		}
		endRemoveRows();
		return true;
	}
}

int ThemeModel::rowCount(const QModelIndex & parent) const {
	return m_themes.count();
}

QVariant ThemeModel::data(const QModelIndex & index, int role) const {
	if (index.row() < 0 || index.row() > m_themes.count())
		return QVariant();

	const ThemeInfo &theme = m_themes[index.row()];
	switch (role) {
	case ThemeRole:
		return theme.theme;
		break;
	case NameRole:
		return theme.themeName;
		break;
	case IconRole:
		return theme.themeIcon;
		break;
	default:
		return QVariant();
	}
}

int ThemeModel::indexOf(QString themeName)
{
	int index = -1;
	for (int i = 0; i < m_themes.size(); ++i) {
		if (m_themes.at(i).theme == themeName) {
			index = i;
			break;
		}
	}
	return index;
}



