#pragma once

#include <memory>

#include <wx/colour.h>
#include <wx/graphics.h>

namespace wxstyle {

	class GradientDefinition {
	public:
		GradientDefinition& AddColorStop(const float index, const wxColor& color) {
			m_gradientStops.Add(color, index);
			return *this;
		}

		virtual wxGraphicsBrush CreateBrush(const wxGraphicsContext& g, const wxRect& referenceSize) const = 0;

	protected:
		wxGraphicsGradientStops GetGradientStops() const {
			return m_gradientStops;
		}

	private:
		wxGraphicsGradientStops m_gradientStops;
	};

	typedef std::shared_ptr<GradientDefinition> GradientDefinitionPtr;

	class LinearGradientDefinition : public GradientDefinition {
	public:
		enum Direction {
			HORIZONTAL,
			VERTICAL
		};

		LinearGradientDefinition(Direction direction) : m_direction(direction) {}

		wxGraphicsBrush CreateBrush(const wxGraphicsContext& g, const wxRect& referenceRect) const override {
			if (m_direction == VERTICAL) {
				return g.CreateLinearGradientBrush(0, referenceRect.GetTop() - 1, 0, referenceRect.GetHeight() + 2, GetGradientStops());
			} else {
				return g.CreateLinearGradientBrush(referenceRect.GetLeft() - 1, 0, referenceRect.GetWidth() + 2, 0, GetGradientStops());
			}
		}

	private:
		Direction m_direction;
	};

    class RadialGradientDefinition : public GradientDefinition {
    public:
        RadialGradientDefinition() {};

        wxGraphicsBrush CreateBrush(const wxGraphicsContext& g, const wxRect& referenceRect) const override {
            return g.CreateRadialGradientBrush(
                referenceRect.GetWidth() / 2 + referenceRect.GetX(), 
                referenceRect.GetHeight() / 2 + referenceRect.GetY(), 
                referenceRect.GetWidth() / 2 + referenceRect.GetX(), 
                referenceRect.GetHeight() / 2 + referenceRect.GetY(),
                referenceRect.GetWidth() / 2, 
                GetGradientStops());
        }
    };

} // namespace wxstyle