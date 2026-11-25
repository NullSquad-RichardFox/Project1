#include "pch.h"
#include "Application.h"


int main() 
{	
	Application app;
	app.Initialize();

	app.Run();


	app.Shutdown();
	return 0;
}