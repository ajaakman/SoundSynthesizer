#ifndef UNICODE 
#define UNICODE
#endif 

#include "TestWindow.h"
#include <iostream>

int main()
{	
	clr::TestWindow window;	
	std::cin.get();
	window.SetMasterVolume(0.2);
	std::cin.get();

	return 0;
}

