#include "style/draw/DrawTextInstruction.h"

#include <wx/colour.h>
#include <wx/graphics.h>
#include <wx/string.h>

#include "style/StyleDefinitions.h"
#include "DimPoint.h"

#include <memory>

namespace wxstyle {

    typedef DrawTextInstruction::Params Params;

    struct Params::ParamsImpl {
        wxString text;
        ShadowDefinition shadowDefinition;
        FontDefinition fontDefinition;
        wxColour color;
        HorizontalAlignment horizontalAnchor;
        VerticalAlignment verticalAnchor;
        DimPoint position;
    };

    Params::Params() {
        impl = std::make_shared<ParamsImpl>();
        impl->verticalAnchor = VerticalAlignment::VA_CENTER;
        impl->horizontalAnchor = HorizontalAlignment::HA_CENTER;
    }

	Params& Params::SetText(const wxString& text) {
		impl->text = text;
		return *this;
	}

	Params& Params::SetShadowDefinition(const ShadowDefinition& shadowDefinition) {
		impl->shadowDefinition = shadowDefinition;
		return *this;
	}

	Params& Params::SetFontDefinition(const FontDefinition& fontDefinition) {
		impl->fontDefinition = fontDefinition;
		return *this;
	}

	Params& Params::SetTextColor(const wxColor& color) {
		impl->color = color;
		return *this;
	}

	Params& Params::SetHorizontalAnchor(const HorizontalAlignment horizontalAnchor) {
		impl->horizontalAnchor = horizontalAnchor;
		return *this;
	}

	Params& Params::SetVerticalAnchor(const VerticalAlignment verticalAnchor) {
		impl->verticalAnchor = verticalAnchor;
		return *this;
	}

	Params& Params::SetTextPosition(const DimPoint& position) {
		impl->position = position;
		return *this;
	}

    wxString Params::GetText() const {
        return impl->text;
    }

    ShadowDefinition Params::GetShadowDefinition() const {
        return impl->shadowDefinition;
    }

    FontDefinition Params::GetFontDefinition() const {
        return impl->fontDefinition;
    }

    wxColour Params::GetColor() const {
        return impl->color;
    }

    HorizontalAlignment Params::GetHorizontalAnchor() const {
        return impl->horizontalAnchor;
    }

    VerticalAlignment Params::GetVerticalAnchor() const {
        return impl->verticalAnchor;
    }

    DimPoint Params::GetPosition() const {
        return impl->position;
    }

    DrawTextInstruction::DrawTextInstruction(const Params& params) : parameters(params)
	{}

	void DrawTextInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {

        wxString text = parameters.GetText();

		// We need to set the font before computing it's extent
		wxFontInfo fontInfo = parameters.GetFontDefinition().CreateFontInfo();
		g->SetFont(fontInfo, *wxBLACK);

		double w, h;
		g->GetTextExtent(text, &w, &h);

		wxPoint offset = ComputeOffset(w, h, parameters.GetHorizontalAnchor(), parameters.GetVerticalAnchor());

		wxSize finalPosition = parameters.GetPosition().GetValue(windowSize);
		int x = finalPosition.GetWidth() + offset.x;
		int y = finalPosition.GetHeight() + offset.y;

        ShadowDefinition shadowDefinition = parameters.GetShadowDefinition();

		// Draw Shadow
		g->SetFont(fontInfo, shadowDefinition.m_color);
		g->DrawText(text, x + shadowDefinition.m_offset.x, y + shadowDefinition.m_offset.y);

		// Draw Text
		g->SetFont(fontInfo, parameters.GetColor());
		g->DrawText(text, x, y);
	}

} // namespace wxstyle