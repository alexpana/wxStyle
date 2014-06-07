#include "DimRect.h"

#include <vector>

#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

namespace wxstyle {

    DimRect DimRect::ValueOf(const char* stringValue) {
        std::vector<std::string> points;
        boost::split(points, std::string(stringValue), boost::is_any_of(", "), boost::token_compress_on);

        return DimRect(
            Dimension::ValueOf(points[0]).get(),
            Dimension::ValueOf(points[1]).get(),
            Dimension::ValueOf(points[2]).get(),
            Dimension::ValueOf(points[3]).get());
    }

	wxRect DimRect::GetValue(const wxRect& referenceRect) const {
		return wxRect(
			m_x.GetValue(referenceRect.GetX()),
			m_y.GetValue(referenceRect.GetY()),
			m_w.GetValue(referenceRect.GetWidth()),
			m_h.GetValue(referenceRect.GetHeight()));
	}

	wxRect DimRect::GetValue(const wxSize& referenceSize) const {
		return GetValue(wxRect(0, 0, referenceSize.GetWidth(), referenceSize.GetHeight()));
	}

	std::ostream& operator<<(std::ostream& lhs, const DimRect& rhs) {
		return lhs << "DimRect(" 
			<< "x:" << rhs.m_x << " "
			<< "y:" << rhs.m_y << " "
			<< "w:" << rhs.m_w << " "
			<< "h:" << rhs.m_h << ")";
	}

	bool operator==(const DimRect& lhs, const DimRect& rhs) {
		return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_w == rhs.m_w && lhs.m_h == rhs.m_h;
	}

} // namespace wxstyle