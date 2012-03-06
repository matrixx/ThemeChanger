# Add more folders to ship with the application, here


QT += declarative

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
CONFIG += meegotouch

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    themehandler.cpp \
    thememodel.cpp

OTHER_FILES += \
    qml/MainPage.qml \
    qml/main.qml \
    ThemeChanger.desktop \
    ThemeChanger.png \
    ThemeChanger.svg \
    qml/ThemeDelegate.qml \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

RESOURCES += \
    res.qrc

LIBS += -lmeegotouchcore
# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

# enable booster
CONFIG += qdeclarative-boostable
QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_LFLAGS += -pie -rdynamic

HEADERS += \
    themehandler.h \
    thememodel.h


