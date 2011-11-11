#include <QtGui/QApplication>
#include <QtDeclarative>
#include "themehandler.h"
#include <QDeclarativeContext>
#include <QDeclarativeEngine>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationDomain("leimu.com");
	QCoreApplication::setApplicationName("ThemeChanger");
    QDeclarativeView view;
	ThemeHandler handler;
	view.engine()->rootContext()->setContextProperty("themeHandler", &handler);
	view.engine()->rootContext()->setContextProperty("themeModel", handler.themeModel());
    view.setSource(QUrl("qrc:/qml/main.qml"));
	handler.fetchCurrentTheme();
    view.showFullScreen();
    return app.exec();
}
