#ifndef WINDOW_H
#define WINDOW_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <shaders/shader.hpp>

#include <iostream>
#include <vector>
using namespace cv;
using namespace aruco;

class Window{
	
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;
		GLFWwindow *window;
		cv::VideoCapture capture;
		cv::Mat frame;
		unsigned int texture1;
		unsigned int VBO, VAO, EBO;
    	Shader ourShader;
	public:
		Window();

		void initializeGLFW();
		void createWindow();
		void initializeShaders(const char* vertexPath, const char* fragmentPath);
		void initializeGLADpointers();
		
		void configureBuffers();
		void configureTextures();
		void configureShaders();
		
		void processInput();
		void readUpdateFrame();
		void render();
		void detectCodes();
		void poll();
		
		void terminate();
		bool shouldTerminate();
		
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif

