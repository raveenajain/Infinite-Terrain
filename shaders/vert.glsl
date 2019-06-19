// Sources: notes, https://learnopengl.com/Getting-started/Shaders
// 					https://stackoverflow.com/questions/13983189/opengl-how-to-calculate-normals-in-a-terrain-height-grid

#version 330 core

layout(location=0)in vec3 position;

// uniforms, MVP matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// vertex shader output
out vec3 pos;

void main() {
	// set color based on y-depth (coordinate height)
	pos = vec3(1.0, position.y + 0.5, 0.0);

	gl_Position = projection * view * model * vec4(position, 1.0f);
}
