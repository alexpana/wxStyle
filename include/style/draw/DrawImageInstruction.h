#pragma once

#include <wx/bitmap.h>

#include "DimPoint.h"
#include "style/draw/Anchor.h"
#include "style/draw/DrawInstruction.h"

namespace wxstyle {
    class DrawImageInstruction : public DrawInstruction {
    public:
        class Builder {
        friend DrawImageInstruction;

        public:
            Builder& SetImagePath(const wxString& imagePath);
            Builder& SetPosition(const DimPoint& position);
            Builder& SetHorizontalAnchor(HorizontalAnchor horizontalAnchor);
            Builder& SetVerticalAnchor(VerticalAnchor verticalAnchor);
            Builder& SetImageSize(const DimPoint& size);

            DrawImageInstruction Build();

        private:
            Builder();
            Builder(const wxString& imagePath, const DimPoint& position, HorizontalAnchor horizontalAnchor, VerticalAnchor verticalAnchor, const DimPoint& size);

        private:
            wxString m_imagePath;
            DimPoint m_position;
            DimPoint m_imageSize;
            HorizontalAnchor m_horizontalAnchor;
            VerticalAnchor m_verticalAnchor;
        };

    public:
        DrawImageInstruction(const wxString& imagePath, const DimPoint& position, HorizontalAnchor horizontalAnchor, VerticalAnchor verticalAnchor, const DimPoint& size);

        static Builder NewBuilder() {
            return Builder();
        }

        Builder ToBuilder() {
            return Builder(m_imagePath, m_position, m_horizontalAnchor, m_verticalAnchor, m_imageSize);
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
        HorizontalAnchor m_horizontalAnchor;
        VerticalAnchor m_verticalAnchor;
        DimPoint m_imageSize;

        // used for caching the bitmap
        const boost::optional<wxBitmap> m_cachedBitmap;
    };
} // namespace wxstyle