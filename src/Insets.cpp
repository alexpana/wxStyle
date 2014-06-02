#include "Insets.h"

namespace wxstyle {

    Insets::Insets() : left(0), top(0), right(0), bottom(0) {}

    Insets::Insets(int left, int top, int right, int bottom) :
        left(left), top(top), right(right), bottom(bottom) {}

    int Insets::Left() {
        return left;
    }

    int Insets::Top() {
        return top;
    }

    int Insets::Right() {
        return right;
    }

    int Insets::Bottom() {
        return bottom;
    }

    int Insets::Width() {
        return left + right;
    }
    int Insets::Height() {
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