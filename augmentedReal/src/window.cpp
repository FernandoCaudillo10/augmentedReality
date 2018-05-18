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
	
	for (unsigned int i=0; i<12; ++i) {
		ChessPiece temp;
		temp.setType(i);
		pieces.push_back(temp);
	}	

	frameTex.setasBackground();
		
	frameTex.setVertices(tempvert);
	frameTex.setIndices(tempin);
	frameTex.setBuffers();

		
	//capture.open("../../Desktop/board.mp4");
	capture.open(0); //UNCOMMENT to test camera and comment above ^^

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
void Window::renderGraphic(std::vector<std::vector<float>> &code, ChessPiece &piece){
	float coord[12];
	
	int i=0;	
	for(auto att : code){
		if(i == 12)
			break;
		if(att.size() == 1)
			continue;
		coord[i] = att[0];
		coord[i+1] = att[1];
		coord[i+2] = 0.0f;
		i += 3;	
	}
		
	piece.renderWithCoord(coord);
}
void Window::detectHelper(std::vector<std::vector<std::vector<float>>> &codes, std::vector<int> &ids){

	for (auto& piece : pieces) {
		for(auto& code : codes){
			if (piece.getCodeId() == code[0][0]){
				renderGraphic(code, piece);
			}
		}
	}
}
void Window::detectCodes(){
	std::vector<std::vector<std::vector<float>>> temporary_vector;
	temporary_vector = coordinate.getCoordinates(frameTex.getMat());

//	for(auto code : temporary_vector){
//		std::cout << "[";
//		for(auto point : code){
//			std::cout << "[";
//			for(auto elem : point){
//				std::cout << elem << ", ";
//			}
//			std::cout << "]\n";
//		}
//		std::cout << "]\n";
//	}

	std::vector<int> temporary;
	temporary = coordinate.getMarkerIds();

	
	detectHelper(temporary_vector, temporary);	
}
void Window::readUpdateFrame(){
	
	frameTex.bind();
		
	cv::Mat temp;
	if(!capture.read(temp)){
		return;
	}
	//cv::flip(temp,temp, +1);
	cv::rotate(temp,temp, cv::ROTATE_180);	

	
	frameTex.setImage(temp);
	
	//create texture from Mat object 	
	frameTex.renderTexbyMat();
		
}
void Window::renderHelper(){
	
	frameTex.render();	
	readUpdateFrame();
	frameTex.draw();
	
	detectCodes();
}
