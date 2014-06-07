#include "style/StyleDefinitions.h"

namespace wxstyle {

	std::ostream& operator<<(std::ostream& lhs, const FontDefinition& rhs) {
		return lhs << "FontDefinition(" 
			<< "face:" << rhs.fontFace << " " 
			<< "size:" << rhs.fontSize << " " 
			<< "weight:" << rhs.fontWeight << " " 
			<< "style:" << rhs.fontStyle << ")";
	}

	bool operator==(const FontDefinition& lhs, const FontDefinition& rhs) {
		return lhs.fontFace == rhs.fontFace && lhs.fontSize == rhs.fontSize && lhs.fontStyle == rhs.fontStyle && lhs.fontWeight == rhs.fontWeight;
	}

	wxFontInfo FontDefinition::CreateFontInfo() const {
		// size
		wxFontInfo fontInfo = fontSize ? wxFontInfo(fontSize.get()) : wxFontInfo();

		fontInfo.Encoding(wxFONTENCODING_SYSTEM);

		// style
		if (fontStyle) {
			fontInfo.Italic(fontStyle.get() == wxFONTSTYLE_ITALIC);
		}

		// weight
		if (fontWeight) {
			fontInfo.Bold(fontWeight.get() == wxFONTWEIGHT_BOLD);
		}

		// face name
		if (fontFace) {
			fontInfo.FaceName(fontFace.get());
		}

		return fontInfo;
	}

	FontDefinition& FontDefinition::SetFace(const wxString& fontFace) {
		this->fontFace = fontFace;
		return *this;
	}

	FontDefinition& FontDefinition::SetSize(int size) {
		fontSize = size;
		return *this;
	}

	FontDefinition& FontDefinition::SetWeight(wxFontWeight weight) {
		fontWeight = weight;
		return *this;
	}

	FontDefinition& FontDefinition::SetStyle(wxFontStyle style) {
		fontStyle = style;
		return *this;
	}

    IconDefinition& IconDefinition::SetIconName(const wxString& name) {
        iconName= name;
        return *this;
    }

} // namespace wxstyle