#ifndef TEXTURE_H
#define TEXTURE_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>
#include <shaders/shader.hpp>

#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

class Texture{
	
	public:
		Texture();
		void configureTexture();
		void renderTexbyMat();
		void renderTexbyIm();
		unsigned int getTexture() const {return texture; }
		void setImage(cv::Mat image);
		void setImage(const char* path);
		void setasBackground();
		void setasGraphic();
		void bind();
	    	Shader shader;
		void setVertices(float vertices[]);
		void setIndices(unsigned int indices[]);
		void updateCoordinate(float coord[12]);
		void draw();
		void render();
		void setBuffers();
		void release();
		void setTexCoordinate(float coord[8]);
		cv::Mat getMat()const {return image;}
	private:
		unsigned int VBO, VAO, EBO;
		float vertices[32]; 		
		unsigned int indices[6]; 	
		
		unsigned int texture;
	
		bool isBackground;

		int width, height, nrChannels;
		unsigned char *imageData;
		cv::Mat image;
};

#endif
