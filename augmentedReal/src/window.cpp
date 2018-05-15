#include "window.hpp"

Window::Window(){
	first = false;
	float tempvert[32] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
			 1.0f,  -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
			 -1.0f,  -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
			 -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
		};
	
	std::copy(std::begin(tempvert), std::end(tempvert), std::begin(vertices));
	
	float tempvert2[32] = {
			// positions          // colors           // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
			  0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
			 -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
			 -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
		};
	
	std::copy(std::begin(tempvert2), std::end(tempvert2), std::begin(vertices2));
	
	unsigned int tempin[6] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
 	std::copy(std::begin(tempin), std::end(tempin), std::begin(indices));

	initializeGLFW();
	
	createWindow();

	initializeGLADpointers();
	
	initializeShader("include/shaders/vertexShader.vs", "include/shaders/fragmentShader.fs");           
	initializeShader2("include/shaders/vertexShader.vs", "include/shaders/fragmentShaderGraphic.fs");           
	
	configureBuffer();
		

	frameTex.setID(0);
	frameTex.setName("texture1");	
	frameTex.configureTexture();

	capture.open("testMovie.mp4");
	//capture.open(0); //UNCOMMENT to test camera and comment above ^^

	readUpdateFrame();
	
	graphic.setID(0);
	graphic.setName("graphic");
	graphic.configureTexture();

	stbi_set_flip_vertically_on_load(true);
	graphic.setImage("/home/leeon/augmentedReality/augmentedReal/smile.png");

	updateGraphic();
	configureShader();
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
void Window::configureShader(){	
    shader.use(); 
    shader.setInt(frameTex.getName(), frameTex.getTexID());
	shader2.use();
	shader2.setInt(graphic.getName(), graphic.getTexID());
}
void Window::initializeShader(const char* vertexPath, const char* fragmentPath){
	shader.initShaders(vertexPath, fragmentPath);
}
void Window::initializeShader2(const char* vertexPath, const char* fragmentPath){
	shader2.initShaders(vertexPath, fragmentPath);
}
void Window::configureBuffer(){
	shader.use();    
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	shader2.use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
  	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
  	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
  	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	
	//read from camera and update the texture
	//readUpdateFrame();
	
	//redraw graphic at new position
	//updateGraphic(); 
	
	renderHelper();

	glfwSwapBuffers(window);
}
void Window::poll(){
	//currently no events to listen for
	glfwPollEvents();
}
void Window::terminate(){
		
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
}
bool Window::shouldTerminate(){
	return !glfwWindowShouldClose(window);
}
//	void Window::detectCodes(){
//		Ptr<Dictionary> dictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
//		std::vector<int> markerIds;
//		std::vector<std::vector<Point2f>> markerCorners, rejectedCandidates;
//		DetectorParameters parameters; 
//		detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
//		
//		for(auto row : markerCorners){
//			for(auto col : row){
//				std::cout << col.x << " " << col.y << std::endl;
//			}
//		}
//	}
void Window::readUpdateFrame(){
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, frameTex.getTexture());
	cv::Mat temp;
	if(!capture.read(temp)){
		return;
	}
	cv::flip(temp,temp, +1);
	frameTex.setImage(temp);
	//detectCodes();
	
	//create texture from Mat object 	
	frameTex.renderTexbyMat();
		
}
void Window::updateGraphic(){
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, graphic.getTexture()); 
	graphic.renderTexbyIm();	
}
void Window::renderHelper(){
	
	shader.use();

	glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	readUpdateFrame();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	shader2.use();
		
	glBindVertexArray(VAO2);	
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, graphic.getTexture()); 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
