#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Backend : public QObject {
    Q_OBJECT
public slots:
    void sayHello() {
        qDebug() << "Hello from C++";
    }
};

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    Backend backend;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

#include "main.moc"