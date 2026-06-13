#include "PatternRenderer.h"

PatternRenderer::PatternRenderer(PatternSpaceRenderer* spaceRenderer, PatternShapeRenderer* shapeRenderer)
: spaceRenderer_(spaceRenderer), shapeRenderer_(shapeRenderer) {}

PatternRenderer::~PatternRenderer() {
    delete spaceRenderer_;
    delete shapeRenderer_;
}

void PatternRenderer::initialize() const {
    spaceRenderer_->initialize();
    shapeRenderer_->initialize();
}

void PatternRenderer::upload() const {
    spaceRenderer_->upload();
    shapeRenderer_->upload();
}

void PatternRenderer::render() const {
    spaceRenderer_->render();
    shapeRenderer_->render();
}

void PatternRenderer::scaleChanged(const float scale) const {
    spaceRenderer_->scaleChanged(scale);
    shapeRenderer_->scaleChanged(scale);
}