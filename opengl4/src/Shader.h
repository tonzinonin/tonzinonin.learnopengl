#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "FaultChecking.h"
#include "glm/glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string v_FilePath;
	std::string f_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath1 , const std::string& filepath2);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v4, float v3) const;
	void SetUniformVec3(const std::string& name, float v0, float v1, float v2) const;
	void SetUniform1i(const std::string& name, int v0) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	unsigned int GetRendererID() const { return this->m_RendererID; }

private:
	unsigned int GetUniformLocation(const std::string name) const;
	ShaderProgramSource ParseShader(const std::string& filepath, const std::string& filepath2) const;
	unsigned int CompileShader(unsigned int type, const std::string& source); 
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};