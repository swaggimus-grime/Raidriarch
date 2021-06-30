#pragma once

#ifdef RAID_PLATFORM_WINDOWS

extern Raid::App* Raid::CreateApp();

int main(int argc, char** argv)
{
	Raid::Log::Init();

	RAID_PROFILE_BEGIN_SESSION("Startup", "RaidriarchProfile-Startup.json");
	auto app = Raid::CreateApp();
	RAID_PROFILE_END_SESSION();

	RAID_PROFILE_BEGIN_SESSION("Runtime", "RaidriarchProfile-Runtime.json");
	app->Run();
	RAID_PROFILE_END_SESSION();

	RAID_PROFILE_BEGIN_SESSION("Startup", "RaidriarchProfile-Shutdown.json");
	delete app;
	RAID_PROFILE_END_SESSION();
}

#endif