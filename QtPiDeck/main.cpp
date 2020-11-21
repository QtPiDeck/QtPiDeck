#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QtGlobal>
#include <QCursor>

#include "connectionsettings.h"

void setCursorVisibility();

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QIcon::setThemeName("maintheme");

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    setCursorVisibility();

    // register all types in separate function
    qmlRegisterType<ConnectionSettings>("data.connectionsettings", 1, 0, "ConnectionSettings");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

void setCursorVisibility() {
    auto hideCursorVar = qgetenv("HIDE_CURSOR");
    auto hideCursor = [](){
        QCursor cursor(Qt::BlankCursor);
        QGuiApplication::setOverrideCursor(cursor);
        QGuiApplication::changeOverrideCursor(cursor);
    };
    if (hideCursorVar.isEmpty()) {
#ifdef Q_PROCESSOR_ARM
        hideCursor();
#endif
        return;
    }

    if (hideCursorVar.toInt() != 0) {
        hideCursor();
    }
}
