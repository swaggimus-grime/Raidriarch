#include <Raidriarch.h>
#include <Raid/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Raid {
	class RaidriarchEditor : public App
	{
	public:
		RaidriarchEditor()
			:App("Raidriarch Editor")
		{
			PushLayer(new EditorLayer());
		}

		~RaidriarchEditor()
		{
		}
	};

	App* CreateApp()
	{
		return new RaidriarchEditor();
	}
}
