#ifndef RENDERER_H
#define RENDERER_H
#include "glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"

class  Renderer
{
private:
	unsigned int model;
public:
	Renderer();
	void Draw(float* vertex, unsigned int* index, glm::mat4 modelMatrix);
	unsigned int VBO = 0; // VertexBufferObject
	unsigned int VAO = 0; // VertexArrayObject
	unsigned int EBO = 0; // ElementsBufferObject
	unsigned int program = 0; // ProgramShader
	void CreateBuffers();
	void BindBuffers();
	unsigned int CompileShader(unsigned int type, const char* shaderPath);
	void CreateProgram(const char* vertexShaderPath, const char* pixelShaderPath);
	void DefVertexAttribute();
	void CallUniformShaders();
	void UpdateUniformShaders(glm::mat4 modelMatrix);
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif