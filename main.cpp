#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "googleloader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<GoogleLoader>("app.types", 1, 0, "GoogleLoader");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
