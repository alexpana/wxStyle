#include "style/StyleDefinitions.h"

namespace wxstyle {

	std::ostream& operator<<(std::ostream& lhs, const FontDefinition& rhs) {
		return lhs << "FontDefinition(" 
			<< "face:" << rhs.m_face << " " 
			<< "size:" << rhs.m_size << " " 
			<< "weight:" << rhs.m_weight << " " 
			<< "style:" << rhs.m_style << ")";
	}

	bool operator==(const FontDefinition& lhs, const FontDefinition& rhs) {
		return lhs.m_face == rhs.m_face && lhs.m_size == rhs.m_size && lhs.m_style == rhs.m_style && lhs.m_weight == rhs.m_weight;
	}

	wxFontInfo FontDefinition::CreateFontInfo() const {
		// size
		wxFontInfo fontInfo = m_size ? wxFontInfo(m_size.get()) : wxFontInfo();

		fontInfo.Encoding(wxFONTENCODING_SYSTEM);

		// style
		if (m_style) {
			fontInfo.Italic(m_style.get() == wxFONTSTYLE_ITALIC);
		}

		// weight
		if (m_weight) {
			fontInfo.Bold(m_weight.get() == wxFONTWEIGHT_BOLD);
		}

		// face name
		if (m_face) {
			fontInfo.FaceName(m_face.get());
		}

		return fontInfo;
	}

	FontDefinition& FontDefinition::SetFace(const wxString& fontFace) {
		m_face = fontFace;
		return *this;
	}

	FontDefinition& FontDefinition::SetSize(int size) {
		m_size = size;
		return *this;
	}

	FontDefinition& FontDefinition::SetWeight(wxFontWeight weight) {
		m_weight = weight;
		return *this;
	}

	FontDefinition& FontDefinition::SetStyle(wxFontStyle style) {
		m_style = style;
		return *this;
	}

} // namespace wxstyle