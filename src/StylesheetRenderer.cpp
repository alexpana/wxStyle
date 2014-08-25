#pragma once

#include "StylesheetRenderer.h"

#include "Algorithms.h"
#include "DimRect.h"
#include "FontMetrics.h"
#include "StyledWindow.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/ImageRepository.h"
#include "style/DefinitionBundle.h"

namespace wxstyle
{
    void StylesheetRenderer::DrawBackground(wxGraphicsContext *g, StyledWindow *window) const {
        DefinitionBundle bundle = window->GetDefinitionBundle();

        if (bundle.HasDrawInstructions())
        {
            // draw instructions
            for (auto instruction : bundle.GetDrawInstructions())
            {
                instruction->Draw(g, window->GetSize());
            }
        }
        else
        {
            // solid or transparent background
            wxColor backgroundColor;
            if (bundle.HasOpacityDefinition() && !bundle.IsOpaque()) {
                // Transparent
                backgroundColor = window->GetInheritedBackgroundColor();
            } else {
                // Opaque
                if (bundle.HasBackgroundColorDefinition()) {
                    backgroundColor = bundle.GetBackgroundColor();
                } else {
                    backgroundColor = window->GetBackgroundColour();
                }
            }

            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(backgroundColor)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
                .Draw(g, window->GetSize());
        }
    }

    wxSize StylesheetRenderer::GetIconSize(StyledWindow *window) const {
        DefinitionBundle bundle = window->GetDefinitionBundle();

        if (bundle.HasIconDefinition()) {
            auto icon = ImageRepository::GetInstance()->GetImage(bundle.GetIcon().iconName.get());
            return icon->GetSize();
        } else {
            return wxSize(0, 0);
        }
    }

    wxSize StylesheetRenderer::GetTextSize(StyledWindow *window) const {
        DefinitionBundle bundle = window->GetDefinitionBundle();
        return TextMetrics(window).GetTextSize(window->GetText(), bundle.GetFont());
    }

    int StylesheetRenderer::GetIconTextGap(StyledWindow *window) const {
        static int ICON_TEXT_GAP = 8;

        DefinitionBundle bundle = window->GetDefinitionBundle();
        if (bundle.HasIconDefinition() && window->GetText().Length() > 0) {
            return ICON_TEXT_GAP;
        } else {
            return 0;
        }
    }

    wxPoint StylesheetRenderer::GetContentGroupPosition(StyledWindow *window) const {
        DefinitionBundle bundle = window->GetDefinitionBundle();

        wxSize contentSize(0, 0);

        contentSize.SetWidth(GetIconSize(window).GetWidth() + GetIconTextGap(window) + GetTextSize(window).GetWidth());
        contentSize.SetHeight(std::max(GetIconSize(window).GetHeight(), GetTextSize(window).GetHeight()));

        wxPoint position = wxstyle::Align(window->GetSize(), contentSize, bundle.GetTextAlignment());

        return position;
    }
}