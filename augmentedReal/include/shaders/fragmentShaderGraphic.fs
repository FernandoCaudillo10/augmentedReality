#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D graphic;

void main(){
	vec4 graphicA = texture(graphic, TexCoord);
	graphicA.a = 0.5;
	FragColor = graphicA;
}
