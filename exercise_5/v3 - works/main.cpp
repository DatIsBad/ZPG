#pragma once
#include <stdio.h>
#include "App.h"


int main()
{
	App* application = new App();
	application->RunApp();


	delete application;
	return 0;
}



