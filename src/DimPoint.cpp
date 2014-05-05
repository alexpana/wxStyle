#include "DimPoint.h"

namespace wxstyle {

    bool operator==(const DimPoint& lhs, const DimPoint& rhs) {
        return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
    }

    std::ostream& operator<<(std::ostream& lhs, const DimPoint& rhs) {
        return lhs << "DimPoint(" << rhs.m_x << ", " << rhs.m_y << ")";
    }

} // namespace wxstyle