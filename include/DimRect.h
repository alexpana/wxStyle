#pragma once

#include <wx/gdicmn.h>

#include "Dimension.h"

namespace wxstyle {

	class DimRect {
	public:
		Dimension m_x;
		Dimension m_y;
		Dimension m_w;
		Dimension m_h;

		DimRect() {}

		DimRect(Dimension x, Dimension y, Dimension width, Dimension height) : 
			m_x(x), m_y(y), m_w(width), m_h(height)
		{}

		wxRect GetValue(const wxRect& referenceRect) const;
		wxRect GetValue(const wxSize& referenceSize) const;
	};

	std::ostream& operator<<(std::ostream& lhs, const DimRect& rhs);
	bool operator==(const DimRect& lhs, const DimRect& rhs);

} // namespace wxstyle