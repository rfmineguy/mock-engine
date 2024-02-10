#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec4 uColor;
uniform mat4 model, view, projection;
uniform float uRadius;

out vec2 uv;
out vec4 oColor;
out float oRadius;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1);
	uv = aPos.xy;
	oColor = uColor;
	oRadius = uRadius;
}
