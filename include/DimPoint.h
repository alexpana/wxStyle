#pragma once

#include <wx/gdicmn.h>

#include "Dimension.h"

namespace wxstyle {

	class DimPoint {
	public:
		Dimension m_x;
		Dimension m_y;

		DimPoint() {}

		DimPoint(const Dimension& x, const Dimension& y) : m_x(x), m_y(y) {}

		wxPoint GetValue(const wxPoint& referencePoint) const {
			return wxPoint(m_x.GetValue(referencePoint.x),
				m_y.GetValue(referencePoint.y));
		}

		wxSize GetValue(const wxSize& referenceSize) const {
			return wxSize(m_x.GetValue(referenceSize.GetWidth()),
				m_y.GetValue(referenceSize.GetHeight()));
		}
	};

    bool operator==(const DimPoint& lhs, const DimPoint& rhs);
    std::ostream& operator<<(std::ostream& lhs, const DimPoint& rhs);

} // namespace wxstyle