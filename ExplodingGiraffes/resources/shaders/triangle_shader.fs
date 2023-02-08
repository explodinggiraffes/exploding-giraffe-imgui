#version 460 core

// TODO: Rename to fragment_color?
out vec4 FragColor;

in vec3 vertex_color;

uniform vec3 color;

void main() {		
	FragColor = vec4(color * vertex_color, 1.0);
}
