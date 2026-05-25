#include "ChrysalisRenderer.h"

#include <iostream>
#include <QOpenGLFramebufferObject>

#include "Argument.h"
#include "BinaryFunction.h"
#include "Project.h"

#include "Logger.h"
#include "VectorFunction.h"
#define LOGGER_NAME "Chrysalis Renderer"

// --- Operators "*" and "/" use width and height of QRectF (scaling operations) ---------------------------------------

QPointF& operator*=(QPointF& point, const QRectF& rect) {
    point.setX(point.x() * rect.width());
    point.setY(point.y() * rect.height());
    return point;
}

QPointF operator*(QPointF point, const QRectF& rect) {
    return point *= rect;
}

QRectF& operator/=(QRectF& rect, const double denominator) {
    rect.setSize(rect.size() / denominator);
    return rect;
}

// --- Operators "+" and "-" use x and y of QRectF (translating operations) --------------------------------------------

QPointF& operator+=(QPointF& point, const QRectF& rect) {
    point.setX(point.x() + rect.x());
    point.setY(point.y() + rect.y());
    return point;
}

QRectF& operator-=(QRectF& rect, const QPointF& point) {
    rect.moveLeft(rect.x() - point.x());
    rect.moveTop(rect.y() - point.y());
    return rect;
}

QPointF operator+(QPointF point, const QRectF& rect) {
    return point += rect;
}

// ---------------------------------------------------------------------------------------------------------------------

ChrysalisRenderer::ChrysalisRenderer(ChrysalisOpenGLProgram* program,
                                     CursorRenderer* cursorRenderer,
                                     CartesianRenderer* cartesianRenderer)
    : program_(program), cursorRenderer_(cursorRenderer), cartesianRenderer_(cartesianRenderer) {}

ChrysalisRenderer::~ChrysalisRenderer() {
    delete program_;
    delete cartesianRenderer_;
}

void ChrysalisRenderer::initialize() {
    initializeOpenGLFunctions();

    using A = Argument;
    using BF = BinaryFunction;
    using VF = VectorFunction;

    const auto parameters = new ProjectParameters();
    parameters->addParameter(new Parameter("Back Waist Length", 42));
    parameters->addParameter(new Parameter("Back Width", 31));
    parameters->addParameter(new Parameter("Bust Height", 28));
    parameters->addParameter(new Parameter("Bust Span", 17));
    parameters->addParameter(new Parameter("Apex to center-front", 21));
    parameters->addParameter(new Parameter("Apex to shoulder", 27));
    parameters->addParameter(new Parameter("Hip Depth", 21.5));
    parameters->addParameter(new Parameter("Bust Circumference", 96));
    parameters->addParameter(new Parameter("Waist Circumference", 68));
    parameters->addParameter(new Parameter("Neck Circumference", 38));
    parameters->addParameter(new Parameter("Shoulder Length", 11));
    parameters->addParameter(new Parameter("Hip Circumference", 98));
    // parameters->addParameter(new Parameter("Length", 66));
    // parameters->addParameter(new Parameter("Bust", 96));
    // parameters->addParameter(new Parameter("Bust Height", 36));
    // parameters->addParameter(new Parameter("Back Width", 31));
    // parameters->addParameter(new Parameter("Neck", 38));
    // parameters->addParameter(new Parameter("Shoulder Length", 11));
    // parameters->addParameter(new Parameter("Shoulder To Waist Back", 42));
    // parameters->addParameter(new Parameter("Shoulder To Waist Front", 54));
    // parameters->addParameter(new Parameter("Sleeve Length", 62));

    auto project = PB::Project("", parameters);

    // Back
    const auto backSpaceRendererData = new SpaceRendererData();
    const auto backSpace = new Space(backSpaceRendererData);
    const auto backOutline = new PB::Outline(backSpace);
    const auto back = new PB::Pattern("Back", backSpace, backOutline);

    // Main lines
    back->addPoint("S", 0, 0);
    back->nextPoint("W", Space::Direction::DOWN, parameters->getParameter("Back Waist Length"));
    back->nextPoint("H", Space::Direction::DOWN, parameters->getParameter("Hip Depth"));
    back->nextPoint("H1", Space::Direction::RIGHT, new BF(new BF(parameters->getParameter("Hip Circumference"), new A(4), BF::DIVISION), new A(1), BF::SUBTRACTION));
    back->addPoint("W", "W1", Space::Direction::RIGHT, new VF(backSpace, "H", "H1", VF::LENGTH));
    back->addPoint("W", "W2", Space::Direction::RIGHT, new BF(new BF(parameters->getParameter("Bust Circumference"), new A(4), BF::DIVISION), new A(1), BF::SUBTRACTION));
    back->addPoint("S", "S1", Space::Direction::RIGHT, new VF(backSpace, "W", "W2", VF::LENGTH));
    back->addPoint("W", "AH", Space::Direction::UP, new BF(new VF(backSpace, "S", "W", VF::LENGTH), new A(2), BF::DIVISION));
    back->addPoint("AH", "UB", Space::Direction::UP, new BF(new VF(backSpace, "S", "AH", VF::LENGTH), new A(3), BF::DIVISION));
    back->addPoint("H", "T", Space::Direction::UP, new BF(new VF(backSpace, "H", "W", VF::LENGTH), new A(2), BF::DIVISION));
    // Neck
    back->addPoint("S", "N", Space::Direction::RIGHT, new BF(parameters->getParameter("Neck Circumference"), new A(6), BF::DIVISION));
    back->nextPoint("N1", Space::Direction::DOWN, new BF(parameters->getParameter("Neck Circumference"), new A(16), BF::DIVISION));
    back->nextPoint("N2", Space::Direction::LEFT, new VF(backSpace, "N", "S", VF::LENGTH));
    back->addPoint("N1", "N3", Space::Direction::LEFT, new BF(new VF(backSpace, "N2", "N1", VF::LENGTH), new A(2), BF::DIVISION));
    // Shoulder
    back->addPoint("N", "S2", new A(-18), parameters->getParameter("Shoulder Length"));
    // Armhole
    back->addPoint("UB", "UB1", Space::Direction::RIGHT, new BF(parameters->getParameter("Back Width"), new A(2), BF::DIVISION));
    back->addPoint("AH", "AH1", Space::Direction::RIGHT, new BF(parameters->getParameter("Back Width"), new A(2), BF::DIVISION));
    back->nextPoint("AH2", new A(45), new A(1.5));
    back->addPoint("AH", "AH3", Space::Direction::RIGHT, new VF(backSpace, "W", "W2", VF::LENGTH));
    back->nextPoint("AH4", Space::Direction::LEFT, new A(1));
    back->addPoint("W", "W2", Space::Direction::LEFT, new BF(new BF(parameters->getParameter("Bust Circumference"), new A(4), BF::DIVISION), new A(1), BF::ADDITION));
    back->addPoint("S", "S1", Space::Direction::LEFT, new VF(backSpace, "W", "W2", VF::LENGTH));

    // back->addPoint("A", 0, 0);
    // back->nextPoint("L", Space::Direction::DOWN, parameters->getParameter("Length"));
    // back->addPoint("A", "B", Space::Direction::DOWN, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Bust"), new Argument(2), BinaryFunction::DIVISION), new Argument(3), BinaryFunction::DIVISION), new Argument(5), BinaryFunction::ADDITION));
    // back->addPoint("A", "W", Space::Direction::DOWN, parameters->getParameter("Shoulder To Waist Back"));
    // back->addPoint("B", "B1", Space::Direction::LEFT, new BinaryFunction(new BinaryFunction(parameters->getParameter("Back Width"), new Argument(2), BinaryFunction::DIVISION), new Argument(1), BinaryFunction::ADDITION));
    // back->addPoint("B1", "B2", Space::Direction::LEFT, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Bust"), new Argument(2), BinaryFunction::DIVISION), new Argument(4), BinaryFunction::DIVISION), new Argument(14), BinaryFunction::MIN));
    // back->addPoint("B1", "B3", Space::Direction::LEFT, new BinaryFunction(new BinaryFunction(new VectorFunction(backSpace, "B1", "B2", &VectorFunction::LENGTH), new Argument(2), BinaryFunction::DIVISION), new Argument(1), BinaryFunction::SUBTRACTION));
    // back->addPoint("B1", "S", Space::Direction::UP, new VectorFunction(backSpace, "A", "B", &VectorFunction::LENGTH));
    // back->addPoint("A", "A1", Space::Direction::LEFT, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Neck"), new Argument(2), BinaryFunction::DIVISION), new Argument(3), BinaryFunction::DIVISION), new Argument(0.5), BinaryFunction::ADDITION));
    // back->nextPoint("A2", Space::Direction::UP, new Argument(2));
    // back->addPoint("S", "S1", Space::Direction::DOWN, new Argument(3));
    // back->addPoint("B1", "S2", Space::Direction::DOWN, new BinaryFunction(new BinaryFunction(new VectorFunction(backSpace, "A", "B", &VectorFunction::LENGTH), new Argument(3), BinaryFunction::DIVISION), new Argument(1), BinaryFunction::SUBTRACTION));
    // back->addPoint("B1", "S3", new Argument(135), new Argument(2.5));
    // back->addPoint("S1", "S4", new VectorFunction(backSpace, "A2", "S1", &VectorFunction::ANGLE), new Argument(1.5));
    // back->addPoint("A2", "D0", new VectorFunction(backSpace, "A2", "S1", &VectorFunction::ANGLE), new Argument(5));
    // back->addPoint("D0", "D01", Space::Direction::DOWN, new Argument(7));
    // back->addPoint("D0", "D02", new VectorFunction(backSpace, "A2", "S1", &VectorFunction::ANGLE), new Argument(1.75));
    // back->addPoint("L", "L1", Space::Direction::LEFT, new BinaryFunction(new VectorFunction(backSpace, "B", "B3", &VectorFunction::LENGTH), new Argument(1), BinaryFunction::ADDITION));

    const auto patternRendererBack = new PatternRenderer(
        new PatternSpaceRenderer(program_, backSpaceRendererData),
        new PatternShapeRenderer()
    );
    patternRenderers_.push_back(patternRendererBack);

    // Front
    const auto frontSpaceRendererData = new SpaceRendererData();
    const auto frontSpace = new Space(frontSpaceRendererData);
    const auto frontOutline = new PB::Outline(frontSpace);
    const auto front = new PB::Pattern("Front", frontSpace, frontOutline);

    // Main lines
    back->sharePoint("S", front);
    back->sharePoint("W", front);
    back->sharePoint("H", front);
    back->sharePoint("AH", front);
    back->sharePoint("UP", front);
    back->sharePoint("T", front);
    front->addPoint("H", "H1", Space::Direction::LEFT, new BF(new BF(parameters->getParameter("Hip Circumference"), new A(4), BF::DIVISION), new A(1), BF::ADDITION));
    front->addPoint("W", "W1", Space::Direction::LEFT, new VF(backSpace, "H", "H1", VF::LENGTH));
    // Neck
    front->addPoint("S", "N", Space::Direction::LEFT, new BF(parameters->getParameter("Neck Circumference"), new A(6), BF::DIVISION));
    front->nextPoint("N1", Space::Direction::DOWN, new BF(new BF(parameters->getParameter("Neck Circumference"), new A(6), BF::DIVISION), new A(2), BF::ADDITION));
    // Shoulder
    front->addPoint("N", "S2", new BF(new A(180), new A(26), BF::ADDITION), parameters->getParameter("Shoulder Length"));
    // Armhole
    front->addPoint("UB", "UB1", Space::Direction::LEFT, new BF(parameters->getParameter("Back Width"), new A(2), BF::DIVISION));
    front->addPoint("AH", "AH1", Space::Direction::LEFT, new BF(parameters->getParameter("Back Width"), new A(2), BF::DIVISION));
    front->nextPoint("AH2", new BF(new A(90), new A(45), BF::ADDITION), new A(2.5));
    front->addPoint("AH", "AH3", Space::Direction::LEFT, new VF(backSpace, "W", "W2", VF::LENGTH));
    front->nextPoint("AH4", Space::Direction::RIGHT, new A(1));
    // Bust dart
    front->addPoint("S", "B", Space::Direction::DOWN, parameters->getParameter("Bust Height"));
    front->nextPoint("DA", Space::Direction::LEFT, new BF(parameters->getParameter("Bust Span"), new A(2), BF::DIVISION));

    // back->sharePoint("A", front);
    // back->sharePoint("B", front);
    // back->sharePoint("W", front);
    // back->sharePoint("L", front);
    // back->sharePoint("A2", front);
    // back->sharePoint("D01", front);
    // back->sharePoint("D02", front);
    // front->addPoint("B", "B4", Space::Direction::LEFT, new BinaryFunction(new BinaryFunction(parameters->getParameter("Bust"), new Argument(2), BinaryFunction::DIVISION), new Argument(4), BinaryFunction::ADDITION));
    // front->nextPoint("W1", Space::Direction::DOWN, new VectorFunction(frontSpace, "B", "W", &VectorFunction::LENGTH));
    // front->addPoint("B4", "L2", Space::Direction::DOWN, new VectorFunction(frontSpace, "B", "L", &VectorFunction::LENGTH));
    // front->addPoint("B4", "A3", Space::Direction::UP, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Bust"), new Argument(2), BinaryFunction::DIVISION), new Argument(2), BinaryFunction::DIVISION), new Argument(1), BinaryFunction::ADDITION));
    // front->nextPoint("A4", Space::Direction::RIGHT, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Neck"), new Argument(2), BinaryFunction::DIVISION), new Argument(3), BinaryFunction::DIVISION), new Argument(0.5), BinaryFunction::ADDITION));
    // front->addPoint("A3", "A5", Space::Direction::DOWN, new BinaryFunction(new BinaryFunction(new BinaryFunction(parameters->getParameter("Neck"), new Argument(2), BinaryFunction::DIVISION), new Argument(3), BinaryFunction::DIVISION), new Argument(1), BinaryFunction::ADDITION));
    // front->addPoint("A4", "A6", Space::Direction::RIGHT, new Argument(5));
    // front->addPoint("B4", "B5", Space::Direction::RIGHT, new BinaryFunction(new VectorFunction(frontSpace, "A3", "A6", &VectorFunction::LENGTH), new Argument(2), BinaryFunction::SUBTRACTION));
    // front->addPoint("A6", "A7", new VectorFunction(frontSpace, "A6", "B5", VectorFunction::ANGLE), new Argument(1.5));
    // front->addPoint("A2", "A-2", new BinaryFunction(new VectorFunction(frontSpace, "D02", "D01", VectorFunction::ANGLE), new Argument(0.75), BinaryFunction::MULTIPLICATION), new Argument(0.25));
    // front->addPoint("A", "A0", Space::Direction::LEFT, new Argument(1));

    const auto patternRendererFront = new PatternRenderer(
        new PatternSpaceRenderer(program_, frontSpaceRendererData),
        new PatternShapeRenderer()
    );
    patternRenderers_.push_back(patternRendererFront);

    // auto pattern1 = project.addPattern("Back");
    // pattern1
    //     .addPoint("A", 0, 0)
    //     .nextPoint("B", Space::Direction::UP, 10)
    //     .addPoint("C", 10, 10)
    //     .nextPoint("D", Space::Direction::DOWN, 10);
    // PatternRenderer* patternRenderer1 = new PatternRenderer(
    //     new PatternSpaceRenderer(program_, pattern1.getSpaceRendererData()),
    //     new PatternShapeRenderer()
    // );
    // patternRenderers_.push_back(patternRenderer1);
    //
    // auto pattern2 = project.addPattern("Front");
    // pattern2
    //     .addPoint("A", 7, 5)
    //     .nextPoint("B", Space::Direction::UP, 20)
    //     .nextPoint("C", Space::Direction::RIGHT, 5)
    //     .nextPoint("D", Space::Direction::DOWN, 7)
    //     .nextPoint("E", Space::Direction::RIGHT, 10)
    //     .nextPoint("F", Space::Direction::DOWN, 10)
    //     .addPoint("D", "G", Space::Direction::DOWN, 3);
    //
    // PatternRenderer* patternRenderer2 = new PatternRenderer(
    //     new PatternSpaceRenderer(program_, pattern2.getSpaceRendererData()),
    //     new PatternShapeRenderer()
    // );
    // patternRenderers_.push_back(patternRenderer2);

    program_->initialize();
    cartesianRenderer_->initialize();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->initialize();
    }
    cursorRenderer_->initialize();
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    area_.setSize(size / scale_);
    cartesianRenderer_->changeArea(area_);
    cartesianRenderer_->upload();
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeOffset(QPointF&& delta) {
    area_ -= delta * area_;
    cartesianRenderer_->changeArea(area_);
}

void ChrysalisRenderer::changeScale(const double scalar, QPointF&& center) {
    if (!framebufferObject()) return;
    area_ /= scalar;

    center *= 1 - scalar;
    changeOffset(std::move(center));

    scale_ *= scalar;
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->scaleChanged(scale_);
    }
}

void ChrysalisRenderer::changeCursor(QPointF&& cursor) const {
    cursor *= area_;
    cursor += area_;
    for (const auto& patternRenderer: patternRenderers_) {
        for (const auto& points = patternRenderer->getPoints();
             const auto& point: points) {
            constexpr double pointRadius = 0.25;
            if (const double distance = sqrt(pow(point.x() - cursor.x(), 2) + pow(point.y() - cursor.y(), 2));
                distance < pointRadius) {
                cursorRenderer_->displayCursor({point.x(), point.y()});
                return;
            }
        }
    }
    cursorRenderer_->hideCursor();
}

void ChrysalisRenderer::render() {
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(11.0f / 255.0f, 9.0f / 255.0f, 10.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.ortho(
        0, framebufferObject()->width(),
        framebufferObject()->height(), 0,
        -1, 1
    );
    projection.scale(scale_);
    projection.translate(-area_.x(), -area_.y(), 0);

    program_->bind();
    program_->setProjection(projection);
    cartesianRenderer_->render();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->render();
    }
    cursorRenderer_->render();
    program_->release();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    bool shouldAnimate = false;
    shouldAnimate |= cursorRenderer_->animate();
    cartesianRenderer_->upload();
    if (shouldAnimate) object->update();
}
