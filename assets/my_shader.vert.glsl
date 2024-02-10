#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model, view, projection;
uniform vec4 uColor;
  
out vec4 vertexColor;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0);
	vertexColor = uColor;
}
