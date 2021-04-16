#pragma once

#include "Core.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	// To be defined in CLIENT
	App* CreateApp();

}