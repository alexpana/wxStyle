#pragma once

#include <string>
#include <boost/optional/optional.hpp>

namespace wxstyle {

    class Dimension {
    public:
        explicit Dimension(int absolute = 0, float relative = 0) : m_absolute(absolute), m_relative(relative) {}

        int GetAbsolute() const {
            return m_absolute;
        }

        float GetRelative() const {
            return m_relative;
        }

        int GetValue(int referenceSize) const {
            return (int)(referenceSize * m_relative) + m_absolute;
        }

        static boost::optional<Dimension> ValueOf(std::string representation);

    private:
        float m_relative;
        int m_absolute;
    };

    std::ostream& operator<<(std::ostream& lhs, const Dimension& rhs);

    bool operator==(const Dimension& lhs, const Dimension& rhs);

} // namespace wxstyle