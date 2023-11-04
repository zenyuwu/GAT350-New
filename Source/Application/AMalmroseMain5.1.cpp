#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...");

	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World05>();
	world->Initialize();

	// string testing stuff :D

	nc::StringUtils stringUtils;
	std::string str1 = "Hello World";
	std::string str2 = "Hello World";

	std::cout << "ToUpper: " << stringUtils.ToUpper(str1) << std::endl;
	std::cout << "ToLower: " << stringUtils.ToLower(str2) << std::endl;

	if (stringUtils.IsEqualIgnoreCase(str1, str2)) {
		std::cout << "IsEqualIgnoreCase: True" << std::endl;
	}
	else {
		std::cout << "IsEqualIgnoreCase: False" << std::endl;
	}

	for (int i = 0; i < 5; i++) {
		std::cout << "CreateUnique: " << stringUtils.CreateUnique("Kitty") << std::endl; 
	}

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
