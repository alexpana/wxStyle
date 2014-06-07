#include "DimPoint.h"

#include <vector>

#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

namespace wxstyle {

    DimPoint DimPoint::ValueOf(const char* stringValue) {
        std::vector<std::string> points;
        boost::split(points, std::string(stringValue), boost::is_any_of(", "), boost::token_compress_on);

        return DimPoint(
            Dimension::ValueOf(points[0]).get(),
            Dimension::ValueOf(points[1]).get());
    }

    bool operator==(const DimPoint& lhs, const DimPoint& rhs) {
        return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
    }

    std::ostream& operator<<(std::ostream& lhs, const DimPoint& rhs) {
        return lhs << "DimPoint(" << rhs.m_x << ", " << rhs.m_y << ")";
    }

} // namespace wxstyle