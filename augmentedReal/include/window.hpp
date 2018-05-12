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
		unsigned int VBO, VAO, EBO;
		float vertices[32]; 		
		unsigned int indices[6]; 	
	public:
		Window();

		void initializeGLFW();
		void createWindow();
		void initializeGLADpointers();
		
		void configureShader();
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

