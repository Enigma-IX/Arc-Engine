#include "Application.h"

#include "Engine.h"

int main()
{
	Core::ApplicationSpecification appSpec;
	appSpec.Name = "Engine";
	appSpec.WindowSpec.Width = 1920;
	appSpec.WindowSpec.Height = 1080;

	Core::Application application(appSpec);
	application.PushLayer<Engine::Engine>();
	application.Run();
	
	return 0;
}
