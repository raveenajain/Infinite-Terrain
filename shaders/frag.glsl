// Sources: notes, https://learnopengl.com/Lighting/Basic-Lighting,
// 					https://learnopengl.com/Getting-started/Shaders,
//          https://learnopengl.com/Advanced-OpenGL/Depth-testing
#version 330 core

// fragment shader output
out vec4 FragColor;

// uniforms
uniform vec3 lightPos;
uniform vec3 viewPos;

// input from vertex shader
in vec3 pos;
float near = 0.1;
float far = 1.1;

// function calls
float createDepth(float depth);

// darker = closer
// farther = lighter
float createDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z);
}

void main() {
	float depth = createDepth(gl_FragCoord.z);
  FragColor = vec4(vec3(pow(depth, 1) * pos), 1.0);
}
