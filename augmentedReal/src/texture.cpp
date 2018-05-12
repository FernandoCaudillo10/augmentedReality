#include "texture.h"

Texture::Texture(){
	imageData = nullptr;
}
void Texture::configureTexture(){

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   	
}

void Texture::renderTexbyMat(){
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image.ptr());
	glGenerateMipmap(GL_TEXTURE_2D);
	
}
void Texture::renderTexbyIm(){
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void Texture::setImage(const char * path){
	imageData = stbi_load(path, &width, &height, &nrChannels, 0);	
}
void Texture::setImage(cv::Mat image) {
	this->image = image;
}

