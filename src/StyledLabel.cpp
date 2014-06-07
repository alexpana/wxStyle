#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/fontenum.h>

#include "DimPoint.h"
#include "DimRect.h"

#include "FontMetrics.h"
#include "style/draw/DrawTextInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/ImageRepository.h"

namespace wxstyle {

	class DefaultLabelRenderer : public IRenderer {
	public:
        static const int ICON_TEXT_GAP = 8;

		DefaultLabelRenderer() {};
		~DefaultLabelRenderer() {};

		virtual void Render(StyledWindow* window) const {
            StyledLabel* label = (StyledLabel*) window;

            wxAutoBufferedPaintDC deviceContext(label);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            ClearBackground(g.get(), label);

            RenderIcon(g.get(), label);

            RenderText(g.get(), label);
        }

    private:
        void RenderIcon(wxGraphicsContext* g, StyledLabel *label) const {
            DefinitionBundle bundle = label->GetDefinitionBundle();

            if (bundle.HasIconDefinition()) {
                auto icon = ImageRepository::GetInstance()->GetImage(bundle.GetIcon().iconName.get());
                int gap = GetIconTextGap(label);

                TextMetrics metrics(label); 
                wxRect textSize = metrics.GetTextSize(label->GetText(), bundle.GetFont());

                DrawImageInstruction(DrawImageInstruction::Params()
                    .SetImage(icon)
                    .SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
                    .SetPosition(DimPoint(Dimension(- textSize.GetWidth() / 2 - gap / 2, 0.5), Dimension(0, 0.5)))
                    .SetVerticalAnchor(VA_CENTER)
                    .SetHorizontalAnchor(HA_CENTER))
                    .Draw(g, label->GetSize());
            }
        }

        void RenderText(wxGraphicsContext* g, StyledLabel *label) const {
            DefinitionBundle bundle = label->GetDefinitionBundle();
            int iconWidth = 0;
            int gap = GetIconTextGap(label);

            if (bundle.HasIconDefinition()) {
                auto icon = ImageRepository::GetInstance()->GetImage(bundle.GetIcon().iconName.get());
                iconWidth = icon->GetSize().GetWidth();
            }

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetText(label->GetText())
                .SetFontDefinition(FontDefinition().SetSize(10).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD))
                .SetTextColor("#BABCC0")
                .SetShadowDefinition(ShadowDefinition().SetColor("#323232").SetOffset(wxPoint(0, 1)))
                .SetTextPosition(DimPoint(Dimension(iconWidth / 2 + gap / 2, 0.5), Dimension(-2, 0.5))))
                .Draw(g, label->GetSize());
        }

        void ClearBackground(wxGraphicsContext *g, StyledLabel *label) const {
            DefinitionBundle bundle = label->GetDefinitionBundle();
            wxColor backgroundColor;

            if (bundle.HasOpacityDefinition() && !bundle.IsOpaque()) {
                // Transparent
                backgroundColor = label->GetInheritedBackgroundColor();
            } else {
                // Opaque
                if (bundle.HasBackgroundColorDefinition()) {
                    backgroundColor = bundle.GetBackgroundColor();
                } else {
                    backgroundColor = label->GetBackgroundColour();
                }
            }

            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(backgroundColor)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
                .Draw(g, label->GetSize());
        }

        int GetIconTextGap(StyledLabel *label) const {
            DefinitionBundle bundle = label->GetDefinitionBundle();
            if (bundle.HasIconDefinition() && label->GetText().Length() > 0) {
                return ICON_TEXT_GAP;
            } else {
                return 0;
            }
        }
	};

    Style StyledLabel::GetDefaultStyle() {
        DefinitionBundle defaultBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_DEFAULT);


        defaultBundle
            .SetTextAlignment(wxALIGN_CENTER_VERTICAL)
            .SetFont(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_NORMAL))
            .SetForegroundColor("#929395");

        return Style().AddBundle(Style::CAT_DEFAULT, defaultBundle);
    }

	StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
		Init();
	}

	void StyledLabel::Init() {
		SetOpaque(false);

		SetRenderer(std::shared_ptr<DefaultLabelRenderer>(new DefaultLabelRenderer()));
        SetStyle(StyledLabel::GetDefaultStyle());
	}

} // namespace wxstyle