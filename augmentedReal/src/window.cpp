#include "window.hpp"

Window::Window(){
	float tempvert[32] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
			 1.0f,  -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
			 -1.0f,  -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
			 -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
		};
	unsigned int tempin[6] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};	

	initializeGLFW();
	
	createWindow();

	initializeGLADpointers();
	
	for (unsigned int i=0; i<2; ++i) {
		ChessPiece temp;
		pieces.push_back(temp);
	}	

	frameTex.setasBackground();
		
	frameTex.setVertices(tempvert);
	frameTex.setIndices(tempin);
	frameTex.setBuffers();

		
	capture.open("chessVideo.mp4");
	//capture.open(0); //UNCOMMENT to test camera and comment above ^^

	readUpdateFrame();
}
void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::initializeGLFW(){
	
	//initializes glfw and makes sure only version 3 can be run and to run core profile from graphics card
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void Window::createWindow(){
	
	//create window and check if fails
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Augmented Reality", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

	//adds esc key as added option to close window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}
void Window::initializeGLADpointers(){

	//initializes necessary drivers that are OS/System specific
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

}
void Window::render(){
	
	//clears buffer to redraw
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	renderHelper();

	glfwSwapBuffers(window);
}
void Window::poll(){
	//currently no events to listen for
	glfwPollEvents();
}
void Window::terminate(){

	frameTex.release();

    glfwTerminate();
}
bool Window::shouldTerminate(){
	return !glfwWindowShouldClose(window);
}
//void Window::detectCodes(){
/*
	Ptr<Dictionary> dictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	std::vector<int> markerIds;
	std::vector<std::vector<Point2f>> markerCorners, rejectedCandidates;
	DetectorParameters parameters; 
	detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
	
	for(auto row : markerCorners){
		for(auto col : row){
			std::cout << col.x << " " << col.y << std::endl;
		}
	}
;*/
//}
void Window::readUpdateFrame(){
	
	frameTex.bind();
		
	cv::Mat temp;
	if(!capture.read(temp)){
		return;
	}
	//cv::flip(temp,temp, +1);

	frameTex.setImage(temp);
	//detectCodes();
	
	//create texture from Mat object 	
	frameTex.renderTexbyMat();
		
}
void Window::renderHelper(){
	
	frameTex.render();	
	readUpdateFrame();
	frameTex.draw();
	
	float coord[12] = {
			// positions (x,y,z)
			 0.0f,  0.0f, 0.0f,  // top right
			 0.0f,  -1.0f, 0.0f,  // bottom right
			 -1.0f,  -1.0f, 0.0f, // bottom left
			 -1.0f,  0.0f, 0.0f,  // top left 
	};
	float coord2[12] = {
			// positions (x,y,z)
			 1.0f,  1.0f, 0.0f,  // top right
			 1.0f,  -0.0f, 0.0f,  // bottom right
			 -0.0f,  -0.0f, 0.0f, // bottom left
			 -0.0f,  1.0f, 0.0f,  // top left 
	};
	pieces[0].renderWithCoord(coord);
	pieces[1].renderWithCoord(coord2);
}
