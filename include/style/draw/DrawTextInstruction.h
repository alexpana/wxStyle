#pragma once

#include <memory>

#include "style/draw/Anchor.h"
#include "style/draw/DrawInstruction.h"

class wxColour;
class wxGraphicsContext;
class wxString;

namespace wxstyle {

    class DimPoint;
    class FontDefinition;
    class ShadowDefinition;
    
    class DrawTextInstruction : public DrawInstruction {

	public:
        class Params {

        public:
            Params();

        public:
            Params& SetText(const wxString& text);

            wxString GetText()  const;

            Params& SetShadowDefinition(const ShadowDefinition& shadowDefinition);

            ShadowDefinition GetShadowDefinition() const;

            Params& SetFontDefinition(const FontDefinition& fontDefinition);

            FontDefinition GetFontDefinition() const;

            Params& SetTextColor(const wxColour& color);

            wxColour GetColor() const;

            Params& SetHorizontalAnchor(const HorizontalAlignment horizontalAnchor);

            HorizontalAlignment GetHorizontalAnchor() const;

            Params& SetVerticalAnchor(const VerticalAlignment verticalAnchor);

            VerticalAlignment GetVerticalAnchor() const;

            Params& SetTextPosition(const DimPoint& position);

            DimPoint GetPosition() const;

        private:
            struct ParamsImpl;
            std::shared_ptr<ParamsImpl> impl;
        };

	public:
		DrawTextInstruction(const Params& params);

		void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

		Params GetParams() {
            return parameters;
        }

	private:
		const Params parameters;
	};

} // namespace wxstyle