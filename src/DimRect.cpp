#include "DimRect.h"

namespace wxstyle {

	wxRect DimRect::GetValue(const wxRect& referenceRect) const {
		return wxRect(
			m_x.GetValue(referenceRect.GetY()),
			m_y.GetValue(referenceRect.GetY()),
			m_w.GetValue(referenceRect.GetWidth()),
			m_h.GetValue(referenceRect.GetHeight()));
	}

	bool operator==(const DimRect& lhs, const DimRect& rhs) {
		return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_w == rhs.m_w && lhs.m_h == rhs.m_h;
	}

} // namespace wxstyle