#include "PatternRenderer.h"

using namespace Chrysalis;

PatternRenderer::PatternRenderer(std::unique_ptr<PatternTraceRenderer> traceRenderer,
                                 std::unique_ptr<PatternShapeRenderer> shapeRenderer)
    : traceRenderer_(std::move(traceRenderer)), shapeRenderer_(std::move(shapeRenderer)) {}

void PatternRenderer::initialize() const {
    traceRenderer_->initialize();
    shapeRenderer_->initialize();
}

void PatternRenderer::upload() const {
    traceRenderer_->upload();
    shapeRenderer_->upload();
}

void PatternRenderer::render() const {
    traceRenderer_->render();
    shapeRenderer_->render();
}

void PatternRenderer::scaleChanged(const float scale) const {
    traceRenderer_->scaleChanged(scale);
}

const PatternTraceRenderer& PatternRenderer::traceRenderer() const {
    return *traceRenderer_;
}