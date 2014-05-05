#pragma once

#include <wx/bitmap.h>

#include "DimPoint.h"
#include "style/draw/IDrawInstruction.h"

namespace wxstyle {
    class DrawImageInstruction : public IDrawInstruction {
    public:
        class Builder {
        friend DrawImageInstruction;

        public:
            Builder& SetImagePath(const wxString& imagePath);
            Builder& SetPosition(const DimPoint& position);

            DrawImageInstruction Build();

        private:
            Builder();
            Builder(const wxString& imagePath, const DimPoint& position);

        private:
            wxString m_imagePath;
            DimPoint m_position;
        };

    public:
        DrawImageInstruction(const wxString& imagePath, const DimPoint& position);

        static Builder NewBuilder() {
            return Builder();
        }

        Builder ToBuilder() {
            return Builder(m_imagePath, m_position);
        }

        wxString GetImagePath() const {
            return m_imagePath;
        }

        DimPoint GetPosition() const {
            return m_position;
        }

        virtual void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

    private:
        const wxString m_imagePath;
        const DimPoint m_position;
        const boost::optional<wxBitmap> m_cachedBitmap;
    };
} // namespace wxstyle