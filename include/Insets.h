#pragma once

namespace wxstyle {

    class Insets {
    public:
        Insets();
        Insets(int left, int top, int right, int bottom);

        int Left() const;
        int Top() const;
        int Right() const;
        int Bottom() const;

        int Width() const;
        int Height() const;

        static Insets ValueOf(const char* stringValue);

    private:
        int left, top, right, bottom;
    };

    class InsetsBuilder {
    public:
        InsetsBuilder();

        InsetsBuilder& Left(int left);
        InsetsBuilder& Top(int top);
        InsetsBuilder& Right(int right);
        InsetsBuilder& Bottom(int bottom);

        Insets Build();

    private:
        int left, top, right, bottom;
    };

} // namespace wxstyle