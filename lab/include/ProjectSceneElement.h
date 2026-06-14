#ifndef CHRYSALIS_PATTERNBUILDERSCENE_H
#define CHRYSALIS_PATTERNBUILDERSCENE_H

#include <QQuickFramebufferObject>

#include "ProjectRenderer.h"

namespace Chrysalis {
    class ProjectSceneElement: public QQuickFramebufferObject {
        Q_OBJECT
        QML_NAMED_ELEMENT(ProjectScene)

        class Renderer: public ProjectRenderer, public QQuickFramebufferObject::Renderer {
        public:
            explicit Renderer(MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer, CursorRenderer* cursorRenderer);

            void changeProject(const Project* project);
        protected:
            void render() override;
            void synchronize(QQuickFramebufferObject*) override;
            QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
        private:
            boost::optional<const Project*> pendingProject_ = boost::none;
        };
    public:
        explicit ProjectSceneElement(QQuickItem *parent = nullptr);

        [[nodiscard]] Renderer* createRenderer() const override;
    public slots:
        void projectChanged(const Project* project);
    protected:
        void wheelEvent(QWheelEvent* event) override;
        void hoverMoveEvent(QHoverEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
    private:
        QPointF normalize(QPointF&& point) const;

        QPointF mousePosition_;
        QPointF windowPosition_;

        bool isLeftMouseButtonPressed_ = false;

        Renderer* renderer_ = nullptr;
    };
}

#endif //CHRYSALIS_PATTERNBUILDERSCENE_H