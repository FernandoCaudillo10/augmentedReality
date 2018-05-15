#ifndef WINDOW_H
#define WINDOW_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "texture.h"

#include <iostream>
#include <vector>


class Window{
	
	private:
		const unsigned int SCR_WIDTH = 1600;
		const unsigned int SCR_HEIGHT = 1200;
		GLFWwindow *window;
		cv::VideoCapture capture;
		Texture frameTex;
		Texture graphic;
    	Shader shader;
		Shader shader2;
		unsigned int VBO, VAO, EBO;
		unsigned int VBO2, VAO2;
		float vertices[32]; 		
		float vertices2[32]; 		
		unsigned int indices[6]; 	
		bool first;		
	public:
		Window();

		void initializeGLFW();
		void createWindow();
		void initializeGLADpointers();
		
		void configureShader();
		void initializeShader2(const char* vertexPath, const char* fragmentPath);
		void initializeShader(const char* vertexPath, const char* fragmentPath);
		void configureBuffer();
		void renderHelper();
		void processInput();
		void readUpdateFrame();
		void updateGraphic();
		void render();
		//void detectCodes();
		void poll();
		
		void terminate();
		bool shouldTerminate();
		
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif

