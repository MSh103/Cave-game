#include <Atlas.h>
#include <Atlas/Core/Entrypoint.h>

#include "GameLayer.h"

class GameApp : public Atlas::Application
{
public:
	GameApp()
		:Application({
			.Window = {"Cave Game", 1920, 1080}
			})
	{
		PushLayer(new Game());
		Atlas::Log::Info("Hello, world from Cave Game!");
	}
};


Atlas::Application* Atlas::CreateApplication()
{
	return new GameApp();
}