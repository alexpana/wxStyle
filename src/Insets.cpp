#include "Insets.h"

#include <vector>

#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

namespace wxstyle {

    Insets Insets::ValueOf(const char* stringValue) {
        std::vector<std::string> points;
        boost::split(points, std::string(stringValue), boost::is_any_of(", "), boost::token_compress_on);

        return Insets(
            boost::lexical_cast<int>(points[0]),
            boost::lexical_cast<int>(points[1]),
            boost::lexical_cast<int>(points[2]),
            boost::lexical_cast<int>(points[3]));
    }

    Insets::Insets() : left(0), top(0), right(0), bottom(0) {}

    Insets::Insets(int left, int top, int right, int bottom) :
        left(left), top(top), right(right), bottom(bottom) {}

    int Insets::Left() const {
        return left;
    }

    int Insets::Top() const {
        return top;
    }

    int Insets::Right() const {
        return right;
    }

    int Insets::Bottom() const {
        return bottom;
    }

    int Insets::Width() const {
        return left + right;
    }
    int Insets::Height() const {
        return top + bottom;
    }

    InsetsBuilder::InsetsBuilder() : left(0), top(0), right(0), bottom(0) {}

    InsetsBuilder& InsetsBuilder::Left(int left) {
        this->left = left;
        return *this;
    }

    InsetsBuilder& InsetsBuilder::Top(int top) {
        this->top = top;
        return *this;
    }

    InsetsBuilder& InsetsBuilder::Right(int right) {
        this->right = right;
        return *this;
    }

    InsetsBuilder& InsetsBuilder::Bottom(int bottom) {
        this->left = left;
        return *this;
    }

    Insets InsetsBuilder::Build() {
        return Insets(left, top, right, bottom);
    }

} // namespace wxstyle