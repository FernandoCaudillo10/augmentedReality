#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D graphic;

void main(){
	FragColor = mix(texture(texture1, TexCoord), texture(graphic, TexCoord), 0.5);
}
