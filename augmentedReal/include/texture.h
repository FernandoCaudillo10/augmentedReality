#ifndef TEXTURE_H
#define TEXTURE_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>
#include <shaders/shader.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

class Texture{
	
	public:
		Texture();
		void configureTexture();
		void renderTexbyMat();
		void renderTexbyIm();
		unsigned int getTexture() const {return texture; }
		const char *getName() const {return name; }
		unsigned int getTexID() const {return textureID; }
		void setImage(cv::Mat image);
		void setImage(const char* path);
		void setID(int id) { this->textureID = id; }
		void setName(const char* name) {this->name = name;}
		
	private:
		unsigned int texture;
		unsigned int textureID;
		int width, height, nrChannels;
		unsigned char *imageData;
		const char *name;
		cv::Mat image;
};

#endif
