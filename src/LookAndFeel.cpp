#include "LookAndFeel.h"

namespace wxstyle
{
	Stylesheet* CreateDefaultLookAndFeel()
	{
		return nullptr;
	}

	Stylesheet* LookAndFeel::m_stylesheet = CreateDefaultLookAndFeel();
}