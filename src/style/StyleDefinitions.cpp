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

} // namespace wxstyle