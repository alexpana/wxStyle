#pragma once

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/gdicmn.h>

#include <boost/optional.hpp>


namespace wxstyle {

    template<typename T>
    std::ostream& operator<<(std::ostream& lhs, const boost::optional<T>& rhs) {
        static std::string empty = "<>";
        if (rhs) {
            lhs << "[" << rhs.get() << "]";
        } else {
            lhs << empty;
        }
        return lhs;
    }

    /**
     *  Definition for the text shadow property.
     */
    class ShadowDefinition {
    public:
        /// The color of the shadow.
        wxColor m_color;

        /// The offset of the shadow from the foreground text.
        wxPoint m_offset;

        ShadowDefinition& Merge(const ShadowDefinition& other) {
            this->m_color = other.m_color;
            this->m_offset = other.m_offset;
            return *this;

        }

		ShadowDefinition& SetColor(const wxColor& color) {
			m_color = color;
			return *this;
		}

		ShadowDefinition& SetOffset(const wxPoint& offset) {
			m_offset = offset;
			return *this;
		}
    };

    /**
     *  Definition for the text font property
     */
    class FontDefinition {
    public:
        /// The face of the font.
        boost::optional<wxString> fontFace;

        /// The size of the font.
        boost::optional<int> fontSize;

        /// The weight of the font (light, normal or bold).
        boost::optional<wxFontWeight> fontWeight;

        /// The style of the font (normal, italic or slant).
        boost::optional<wxFontStyle> fontStyle;

        FontDefinition& Merge(const FontDefinition& other) {
            if (other.fontFace) this->fontFace = other.fontFace;
            if (other.fontSize) this->fontSize = other.fontSize;
            if (other.fontWeight) this->fontWeight = other.fontWeight;
            if (other.fontStyle) this->fontStyle = other.fontStyle;
            return *this;
        }

		FontDefinition& SetFace(const wxString& fontFace);

		FontDefinition& SetSize(int size);

		FontDefinition& SetWeight(wxFontWeight weight);

		FontDefinition& SetStyle(wxFontStyle style);

		wxFontInfo CreateFontInfo() const;
    };

    std::ostream& operator<<(std::ostream& lhs, const FontDefinition& rhs);
    bool operator==(const FontDefinition& lhs, const FontDefinition& rhs);

    /**
     *  Definition for the icon property.
     */
    class IconDefinition {
    public:
		boost::optional<wxString> iconName;

        IconDefinition& SetIconName(const wxString& name);

		IconDefinition& Merge(const IconDefinition& other) {
            return *this;
        }
    };

    /**
     *  Definition for the text alignment property.
     */
    class TextAlignmentDefinition {
    public:
		enum Alignment {
			LEFT, CENTER, RIGHT
		};

        /// The alignment of the text, as made possible by the wxAlignment enum
        boost::optional<Alignment> textAlignment;

        TextAlignmentDefinition& Merge(const TextAlignmentDefinition& other) {
            if (other.textAlignment) this->textAlignment = other.textAlignment;
            return *this;
        }
    };

    /**
     *  Generic value definition 
     *  This definition holds a single value of type T.
     */
    template<typename T>
    class ValueDefinition {
    public:
        boost::optional<T> value;

        ValueDefinition() {}
        ValueDefinition(T value) : value(value) {}

        ValueDefinition& Merge(const ValueDefinition& other) {
            if (other.value) this->value = other.value;
            return *this;
        }
    };

    template<typename T>
    bool operator==(const ValueDefinition<T>& lhs, const ValueDefinition<T>& rhs) {
        return lhs.value == rhs.value;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& lhs, const ValueDefinition<T>& rhs) {
        return lhs << "ValueDefinition(" << rhs.value << ")";
    }

} // namespace wxstyle