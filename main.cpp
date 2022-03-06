#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qt_windows.h>
#include "AppUtils.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // bool patchEnabled = true;
    bool patchEnabled = false;
    if (patchEnabled)
    {
        SetSearchPathMode(BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE | BASE_SEARCH_PATH_PERMANENT);
    }
    qDebug() << "Patched Enabled: " << patchEnabled;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("patchEnabled", patchEnabled);

    qmlRegisterType<AppUtils>("LoadLibraryApp", 1, 0, "AppUtils");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
