#ifndef UNICODE 
#define UNICODE
#endif 

#include "TestWindow.h"
#include <iostream>

int main()
{	
	clr::TestWindow window;	
	std::cout << "Hello" << std::endl;
	std::cin.get();
	window.SetMasterVolume(0.02);
	std::cin.get();

	return 0;
}

