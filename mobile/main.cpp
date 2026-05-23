#include <QDirIterator>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    const QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Print all import paths
    qDebug() << "Import paths:" << engine.importPathList();

    // Print all embedded resources - check if style qmldir is there
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString path = it.next();
        if (path.contains("style") || path.contains("qml"))
            qDebug() << path;
    }

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, [] {
                         QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection
    );

    engine.load("qrc:/qt/qml/PatternBuilder/qml/Main.qml");
    return QGuiApplication::exec();
}