#pragma once

#ifdef RAID_PLATFORM_WINDOWS

extern Raid::App* Raid::CreateApp();

int main(int argc, char** argv)
{
	Raid::Log::Init();

	auto app = Raid::CreateApp();
	app->Run();
	delete app;
}

#endif