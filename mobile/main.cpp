#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

// Our custom QML type (registered via QML_ELEMENT in the header)
#include "openglitem.h"

int main(int argc, char *argv[])
{
    // ── Force the Qt Scene Graph to use raw OpenGL ────────────────────────────
    // Qt6 defaults to its own RHI abstraction layer (which can target Vulkan,
    // Metal, D3D12, or OpenGL).  We lock it to OpenGL so our QOpenGLFunctions
    // calls work directly.  On Android this will use OpenGL ES automatically.
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Load the root QML file.  qrc:/qt/qml/QtOpenGLApp/MainOLD.qml is the path
    // that qt_add_qml_module() generates for us automatically.
    const QUrl url(u"qrc:/qt/qml/QtOpenGLApp/MainOLD.qml"_qs);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.load(url);

    return app.exec();
}