#pragma once
#include <stdio.h>
#include "App.h"
//********************************************
// PHA0051
// 08/12/2024
//********************************************

int main()
{
	App* application = new App();
	application->RunApp();


	delete application;
	return 0;
}



