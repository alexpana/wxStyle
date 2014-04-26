#pragma once

#include <functional>

#include "Renderer.h"

namespace wxstyle {

class FunctionRenderer : public IRenderer {
public:
    typedef const std::function<void(StyledWindow*)> render_fn;

    FunctionRenderer(const render_fn& function) : m_renderFunction(function) {};

    void Render(StyledWindow* window) const override {
        m_renderFunction(window);
    }

private:
    const render_fn m_renderFunction;
};

} // namespace wxstyle