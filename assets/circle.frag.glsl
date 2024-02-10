#version 330 core
out vec4 FragColor;
in vec2 uv;
in vec4 oColor;
in float oRadius;

void main() {
	float d = length(uv);
	vec4 color;
	color.rgb = vec3(1.0);
	color.a = 1.0;
	if (d > oRadius) {
		color.a = 0.0;
	}
	FragColor = color * oColor;// * color;
}
