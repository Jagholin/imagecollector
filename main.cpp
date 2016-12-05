#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "googleloader.h"
#include "googleimageprovider.h"
#include "imagelistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("https://github.com/Jagholin");
    app.setOrganizationName("Jagholin");
    app.setApplicationName("ImageLoader");

    ImageListModel *imageList = new ImageListModel;
    GoogleImageProvider *myImageProvider = new GoogleImageProvider(imageList);

    QQmlApplicationEngine engine;
    qmlRegisterType<GoogleLoader>("app.types", 1, 0, "GoogleLoader");
    engine.addImageProvider("gloader", myImageProvider);
    engine.rootContext()->setContextProperty("imageListModel", imageList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
