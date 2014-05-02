#pragma once

#include <wx/gdicmn.h>

#include "Dimension.h"

namespace wxstyle {

	class DimPoint {
	public:
		DimPoint(const Dimension& x, const Dimension& y) : m_x(x), m_y(y) {}
		wxPoint GetValue(const wxPoint& referencePoint) {
			return wxPoint(m_x.GetValue(referencePoint.x),
				m_y.GetValue(referencePoint.y));
		}

		wxSize GetValue(const wxSize& referenceSize) {
			return wxSize(m_x.GetValue(referenceSize.GetWidth()),
				m_y.GetValue(referenceSize.GetHeight()));
		}

	private:
		const Dimension m_x;
		const Dimension m_y;
	};

} // namespace wxstyle