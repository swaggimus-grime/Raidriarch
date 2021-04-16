#pragma once

#ifdef RAID_PLATFORM_WINDOWS

extern Raid::App* Raid::CreateApp();

int main(int argc, char** argv)
{
	Raid::Log::Init();
	RAID_CORE_WARN("Initialized Log!");
	int a = 5;
	RAID_INFO("Hello! Var={0}", a);

	auto app = Raid::CreateApp();
	app->Run();
	delete app;
}

#endif