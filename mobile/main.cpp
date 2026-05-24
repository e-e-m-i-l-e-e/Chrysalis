#include <QQuickWindow>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    const QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, [] {
                         QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection
    );

    engine.load("qrc:/qt/qml/PatternBuilder/qml/Main.qml");
    return QGuiApplication::exec();
}