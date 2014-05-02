#pragma once

#include <memory>

#include <wx/colour.h>
#include <wx/graphics.h>

namespace wxstyle {

	class GradientDefinition {
	public:
		GradientDefinition& AddColorStop(const int index, const wxColor& color) {
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

		virtual wxGraphicsBrush CreateBrush(const wxGraphicsContext& g, const wxRect& referenceRect) const override {
			if (m_direction == VERTICAL) {
				return g.CreateLinearGradientBrush(0, -2, 0, referenceRect.GetHeight(), GetGradientStops());
			} else {
				return g.CreateLinearGradientBrush(-2, 0, referenceRect.GetWidth(), 0, GetGradientStops());
			}
		}

	private:
		Direction m_direction;
	};

} // namespace wxstyle