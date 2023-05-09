#pragma once

#include "Renderer.h"
#include <iostream>//���������
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::MVPTrans(const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT, const Shader& shader, Camera& camera, OpenglImgui& ui) const
{
	shader.Bind();
	glm::mat4 diy = 
		glm::mat4(
		glm::vec4(1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1.0)
	);
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(camera.fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f); 

	ui.projectionupdate(projection);
	ui.viewupdate(view);

	shader.SetUniformMat4f("projection", projection);
	shader.SetUniformMat4f("view", view);
	shader.SetUniformVec3("viewPos", camera.cameraPos.x , camera.cameraPos.y , camera.cameraPos.z);

	shader.Unbind();
}

void Renderer::Mix(const int& isAddColor, const float& input, const Shader& shader ) const
{
	shader.Bind();
	if (isAddColor)
	{
		float timevalue = glfwGetTime();
		float dv1 = sin(timevalue) / 2.0f + 0.5f;
		float dv2 = sin(timevalue + 1.57) / 2.0f + 0.5f;
		float dv3 = sin(timevalue + 3.14) / 2.0f + 0.5f;
		shader.SetUniform1i("isColor", 1);
		shader.SetUniform4f("u_Color", dv1, dv2, dv3, 1.0f);
	}
	shader.SetUniform1f("mixval", input);
	shader.Unbind();
}

void Renderer::DrawCube(const VertexArray& va, const Shader& shader , const Texture& texture0, const Texture& texture1 , const glm::vec3 *cubePositions,
	OpenglImgui& ui, unsigned int rendererNumber) const
{
	shader.Bind();
	va.Bind();

	glActiveTexture(GL_TEXTURE0);
	texture0.Bind(0);
	glActiveTexture(GL_TEXTURE1);
	texture1.Bind(1);

	for (unsigned int i = 0; i < rendererNumber; i++)
	{
		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, cubePositions[i]);	
		//float angle = i * 20.0;
		//model = glm::rotate(model, glm::radians(float(glfwGetTime()) * 30 + angle), glm::vec3(1.0f, 0.3f, 0.5f));

		ui.modelupdate(model);

		shader.SetUniformMat4f("model", model);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	}
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const Texture& texture0, const Texture& texture1, const IndexBuffer& id) const
{
	shader.Bind();
	va.Bind();
	id.Bind();

	glActiveTexture(GL_TEXTURE0);
	texture0.Bind(0);
	glActiveTexture(GL_TEXTURE1);
	texture1.Bind(1);

	GLCall(glDrawElements(GL_TRIANGLES, id.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::LightCube(const VertexArray& va, const Shader& shader, const glm::vec3 cubePositions, OpenglImgui& ui, unsigned int rendererNumber
	, glm::vec3& translate , bool istran) const
{
	va.Bind();
	shader.Bind();

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, cubePositions);
		if(istran == true) model = glm::translate(model, translate);

		unsigned int i = 1.0;
		float angle = i * 20.0;
		//model = glm::rotate(model, glm::radians(float(glfwGetTime()) * 30 + angle), glm::vec3(1.0f, 0.3f, 0.5f));

		ui.modelupdate(model);

		shader.SetUniformMat4f("model", model);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}