#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

#include "Camera.h"
#include "Mesh.h"
#include "Block.h"

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

class Game : public Atlas::Layer
{
public:
	Game();

	void OnAttach() override;
	void OnDetach() override;
	void OnEvent(Atlas::Event& e) override;
	void OnUpdate(Atlas::TimeStep ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	bool OnKeyPressed(Atlas::KeyPressedEvent e);
private:
	glm::vec3 m_Color;
	Transform m_Transform;
	glm::mat4 m_Model;

	bool m_Status = true;
	bool m_Debug = false;

	std::array<Block, 16 * 256 * 16> m_Blocks;

	Camera m_Camera;

	//std::unique_ptr<Atlas::VertexArray> m_VAO;
	std::shared_ptr<Atlas::Shader> m_Shader;
	MeshCPU m_MeshCPU;
	MeshGPU m_MeshGPU;

};