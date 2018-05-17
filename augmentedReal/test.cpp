#include "window.hpp"

int main(){

	Window window;
		
    while (window.shouldTerminate()){

        window.processInput();
		
		window.render();
		
		window.poll();
    }
	
	window.terminate();

    return 0;
}

