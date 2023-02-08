#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertex_color;

uniform float rotation;
uniform vec2 translation;

void main() {
  vec2 rotated_position;
  rotated_position.x = translation.x + position.x * cos(rotation) - position.y * sin(rotation);
  rotated_position.y = translation.y + position.x * sin(rotation) + position.y * cos(rotation);
  gl_Position = vec4(rotated_position.x, rotated_position.y, position.z, 1.0);

  vertex_color = color;
}
