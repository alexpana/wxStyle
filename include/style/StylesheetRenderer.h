#pragma once

#include "Renderer.h"

class wxSize;
class wxPoint;
class wxGraphicsContext;
class StyledWindow;

namespace wxstyle
{
    class StylesheetRenderer : public IRenderer
    {
    public:
        ~StylesheetRenderer() override {};

    protected:
        // Generic method used for clearing the background based on the opacity
        // and background color style definitions
        void DrawBackground(wxGraphicsContext *g, StyledWindow *window) const;

        wxSize GetIconSize(StyledWindow *window) const;

        wxSize GetTextSize(StyledWindow *window) const;

        int GetIconTextGap(StyledWindow *window) const;

        wxPoint GetContentGroupPosition(StyledWindow *window) const;
    };
}