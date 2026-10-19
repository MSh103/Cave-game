#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

#include "Camera.h"

#include "Chunk.h"

#include <array>

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

	bool m_Status = true;
	bool m_Debug = false;

	Camera m_Camera;

	//std::unique_ptr<Atlas::VertexArray> m_VAO;
	std::shared_ptr<Atlas::Shader> m_Shader;
	Texture2D* m_Texture = nullptr;

	std::array<std::array<Chunk*, 5>, 5> m_Chunks;
};