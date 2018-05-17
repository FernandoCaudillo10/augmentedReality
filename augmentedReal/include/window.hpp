#ifndef WINDOW_H
#define WINDOW_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>

#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ChessPiece.h>
#include <Coordinates.hpp>

#include <iostream>
#include <vector>


class Window{
	
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;
		GLFWwindow *window;
		cv::VideoCapture capture;
		
		Texture frameTex;
		std::vector <ChessPiece> pieces;
		Coordinates coordinate;
	public:
		Window();

		void initializeGLFW();
		void createWindow();
		void initializeGLADpointers();
		
		void renderHelper();
		void renderGraphic(std::vector<std::vector<float>> &code, ChessPiece &piece);
		void detectHelper(std::vector<std::vector<std::vector<float>>> &codes, std::vector<int> &ids);
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

