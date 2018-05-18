#include "texture.h"

Texture::Texture(){
	imageData = nullptr;
	isBackground = false;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());
	glGenerateMipmap(GL_TEXTURE_2D);
	
}
void Texture::renderTexbyIm(){
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void Texture::setImage(const char * path){
	imageData = stbi_load(path, &width, &height, &nrChannels, 0);	
}
void Texture::setImage(cv::Mat image) {
	this->image = image;
}
void Texture::setasBackground(){
	isBackground = true;
	shader.initShaders("include/shaders/vertexShader.vs", "include/shaders/fragmentShader.fs");
	
	configureTexture();

    shader.use(); 
    shader.setInt("background", 0);
}
void Texture::setasGraphic(){
	isBackground = false;
	shader.initShaders("include/shaders/vertexShader.vs", "include/shaders/fragmentShaderGraphic.fs");
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	configureTexture();
    
	shader.use(); 
    shader.setInt("graphic", 0);

	stbi_set_flip_vertically_on_load(true);
}
void Texture::bind(){
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, texture);
}
void Texture::setVertices(float vertices[]){
	std::copy(vertices, vertices+32, std::begin(this->vertices));
}
void Texture::setIndices(unsigned int indices[]){
 	std::copy(indices, indices+6, std::begin(this->indices));
}
void Texture::setBuffers(){
	shader.use();
	
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
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
}
void Texture::render(){
	
	shader.use();
		
	glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	bind();
}
void Texture::draw(){
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Texture::release(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool norm(float num){
	return ( num <= 1.0 && num >= -1.0);
}

void Texture::updateCoordinate(float coord[]){
		
	for(int i=0; i<12; i++)
		if(!norm(coord[i]))
			return;

	int j=0;
	for(int i=0; i<32; i += 8){
		vertices[i] = coord[j];
		vertices[i+1] = coord[j+1];
		vertices[i+2] = coord[j+2]; 
		j += 3;
	}
			
	shader.use();
    
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
}

void Texture::setTexCoordinate(float coord[8]) {
	for(int i=0; i<12; i++)
		if(!norm(coord[i]))
			return;

	int j=0;
	for(int i=6; i<32; i += 8){
		vertices[i] = coord[j];
		vertices[i+1] = coord[j+1];
		j += 2;
	}

	shader.use();
    
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
}
