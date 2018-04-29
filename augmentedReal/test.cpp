#include "window.hpp"

int main(){

	Window window;
	
	window.initializeShaders("include/shaders/vertexShader.vs", "include/shaders/fragmentShader.fs");			
	window.configureBuffers();
	window.configureTextures();
	window.configureShaders();
	

    while (window.shouldTerminate())
    {

        window.processInput();
		
		window.render();
		
		window.poll();
    }
	
	window.terminate();

    return 0;
}

