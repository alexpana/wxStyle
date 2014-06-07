#pragma once

#include <wx/window.h>
#include <wx/dcclient.h>

#include "style/StyleDefinitions.h"

namespace wxstyle
{
    class TextMetrics
    {
    public:
        TextMetrics(StyledWindow* window)
            : m_dc(window)
        {
            m_dc.SetFont(wxFont(window->GetDefinitionBundle().GetFont().CreateFontInfo()));
        }

        wxSize GetTextSize(const wxString& text, const wxFont& font) {
            int width, height;
            m_dc.GetTextExtent(text, &width, &height, 0, 0, &font);
            return wxSize(width, height);
        }

        wxSize GetTextSize(const wxString& text, const FontDefinition& fontDefinition) {
            return GetTextSize(text, wxFont(fontDefinition.CreateFontInfo()));
        }

        wxFontMetrics GetFontMetrics() {
            return m_dc.GetFontMetrics();
        }

    private:
        wxWindowDC m_dc;
    };
} // namespace wxstyle