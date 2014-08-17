#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/fontenum.h>

#include "DimPoint.h"
#include "DimRect.h"

#include "Algorithms.h"
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

				wxPoint contentPosition = GetContentGroupPosition(label);

				DrawImageInstruction(DrawImageInstruction::Params()
					.SetVerticalAnchor(VA_TOP).SetHorizontalAnchor(HA_LEFT)
					.SetImage(icon)
					.SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
					.SetPosition(DimPoint(contentPosition.x, contentPosition.y)))
					.Draw(g, label->GetSize());
			}
		}

		void RenderText(wxGraphicsContext* g, StyledLabel *label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();

			wxPoint contentPosition = GetContentGroupPosition(label);

			DrawTextInstruction(DrawTextInstruction::Params()
				.SetVerticalAnchor(VA_TOP)
				.SetHorizontalAnchor(HA_LEFT)
				.SetText(label->GetText())
				.SetFontDefinition(bundle.GetFont())
				.SetTextColor(bundle.GetForegroundColor())
				.SetShadowDefinition(bundle.GetTextShadow())
				.SetTextPosition(DimPoint(contentPosition.x + GetIconSize(label).GetWidth() + GetIconTextGap(label), contentPosition.y)))
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

		wxSize GetIconSize(StyledLabel* label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();

			if (bundle.HasIconDefinition()) {
				auto icon = ImageRepository::GetInstance()->GetImage(bundle.GetIcon().iconName.get());
				return icon->GetSize();
			} else {
				return wxSize(0, 0);
			}
		}

		wxSize GetTextSize(StyledLabel* label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();
			return TextMetrics(label).GetTextSize(label->GetText(), bundle.GetFont());
		}

		int GetIconTextGap(StyledLabel *label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();
			if (bundle.HasIconDefinition() && label->GetText().Length() > 0) {
				return ICON_TEXT_GAP;
			} else {
				return 0;
			}
		}

		wxPoint GetContentGroupPosition(StyledLabel *label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();

			wxSize contentSize(0, 0);

			contentSize.SetWidth(GetIconSize(label).GetWidth() + GetIconTextGap(label) + GetTextSize(label).GetWidth());
			contentSize.SetHeight(std::max(GetIconSize(label).GetHeight(), GetTextSize(label).GetHeight()));

			wxPoint position = wxstyle::Align(label->GetSize(), contentSize, bundle.GetTextAlignment());

			return position;
		}
	};


	Style StyledLabel::GetDefaultStyle() {
		DefinitionBundle defaultBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_DEFAULT);
		defaultBundle
			.SetTextAlignment(AlignmentDefinition().Horizontal(HA_CENTER).Vertical(VA_CENTER))
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