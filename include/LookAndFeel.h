#pragma once

namespace wxstyle
{
	class IRenderer;
	class Stylesheet;
	class Style;

	class LookAndFeel
	{
	public:

		enum class WidgetType
		{
			BUTTON, CHECKBOX, LABEL, TEXTBOX
		};

		static void SetStylesheet(Stylesheet stylesheet);

		static void SetDefaultStyle(WidgetType widgetType, Style& style);

		static void SetDefaultRenderer(WidgetType widgetType, IRenderer& renderer);

		static Style GetStyle(WidgetType widgetType);

		static IRenderer GetRenderer(WidgetType widgetType);

	private:
		// Ensure no instances of this class can be created
		LookAndFeel();
		~LookAndFeel();

		static Stylesheet* m_stylesheet;
	};
}