#include "GameLayer.h"


Game::Game() 
	: Layer("GameLayer"), m_Camera({{16.f, 256.f, 16.f}, 75.f})
{}

bool IsAir(Block* blocks, glm::vec3 pos)
{
	if (pos.x < 0 || pos.x >= 16
		|| pos.z < 0 || pos.z >= 16
		|| pos.y < 0 || pos.y >= 256)
		return true;

	int index = pos.x + 16 * (pos.z + 16 * pos.y);
	if (blocks[index] == Block::Air)
		return true;

	return false;
}

void Game::OnAttach()
{
	m_Color.r = 0.0f;
	m_Color.g = 0.0f;
	m_Color.b = 0.0f;


	for (size_t x = 0; x < 16; x++)
	{
		for (size_t z = 0; z < 16; z++)
		{
			for (size_t y = 0; y < 256; y++)
			{
				int index = x + 16 * (z + 16 * y);

				if (y == 256)
					m_Blocks[index] = Block::Air;
				else if (y >= 100 && y <= 125)
					m_Blocks[index] = Block::Air;
				else if(y >= 5 && y <= 10)
					m_Blocks[index] = Block::Air;
				else
					m_Blocks[index] = Block::Grass;
			}
		}
	}

	for (size_t x = 0; x < 16; x++)
	{
		for (size_t z = 0; z < 16; z++)
		{
			for (size_t y = 0; y < 256; y++)
			{
				int index = x + 16 * (z + 16 * y);

				if (m_Blocks[index] == Block::Air)
					continue;

				if (IsAir(m_Blocks.data(), { x - 1, y, z }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Left), { x, y, z });
				if (IsAir(m_Blocks.data(), { x + 1, y, z }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Right), { x, y, z });

				if (IsAir(m_Blocks.data(), { x, y - 1, z }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Bottom), { x, y, z });
				if (IsAir(m_Blocks.data(), { x, y + 1, z }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Top), { x, y, z });

				if (IsAir(m_Blocks.data(), { x, y, z - 1 }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Back), { x, y, z });
				if (IsAir(m_Blocks.data(), { x, y, z + 1 }))
					m_MeshCPU.addMeshPosition(getBlockFace(BlockFace::Front), { x, y, z });

			}
		}
	}


	m_MeshGPU.addMeshCPU(&m_MeshCPU);



	m_Shader = std::make_shared<Atlas::Shader>();
	m_Shader->LoadFromFile(Atlas::ShaderType::Vertex, "assets/Vertex.glsl");
	m_Shader->LoadFromFile(Atlas::ShaderType::Fragment, "assets/Fragment.glsl");
	m_Shader->LinkObjectsToProgram();

	

	m_Transform.Position = { 0.f, 0.f, 0.f };
	m_Transform.Rotation = { 0.f, 0.f, 0.f };
	m_Transform.Scale = { 1.f, 1.f, 1.f };

	m_Model = glm::mat4(1.0f);
}

void Game::OnDetach()
{

}

void Game::OnEvent(Atlas::Event& e)
{
	Atlas::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Atlas::KeyPressedEvent>(AT_BIND_EVENT_FN(Game::OnKeyPressed));

	if(!m_Status)
		m_Camera.OnEvent(e);
}

void Game::OnUpdate(Atlas::TimeStep ts)
{
	m_Camera.OnUpdate(ts);

	//m_Transform.Rotation.y += 1.5f * ts;
	//m_Transform.Rotation.z += 1.5f * ts;

	m_Model = glm::translate(glm::mat4(1.0f), m_Transform.Position) *
		glm::rotate(glm::mat4(1.0f), m_Transform.Rotation.x, glm::vec3(1.f, 0.f, 0.f)) *
		glm::rotate(glm::mat4(1.0f), m_Transform.Rotation.y, glm::vec3(0.f, 1.f, 0.f)) *
		glm::rotate(glm::mat4(1.0f), m_Transform.Rotation.z, glm::vec3(0.f, 0.f, 1.f)) *
		glm::scale(glm::mat4(1.0f), m_Transform.Scale);
}

void Game::OnRender()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(m_Color.r, m_Color.g, m_Color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	if(m_Debug)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//m_VAO->Use();
	m_Shader->Use();
	m_Shader->Upload("u_Model", m_Model);
	m_Shader->Upload("u_View", m_Camera.GetViewMatrix());
	m_Shader->Upload("u_Projection", m_Camera.GetProjectionMatrix());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
	m_MeshGPU.render(m_Shader.get());
}

void Game::OnImGuiRender()
{
	ImGui::Begin("Debug");
	ImGui::ColorEdit3("Clear Screen", glm::value_ptr(m_Color));
	ImGui::Separator();
	ImGui::Text("Transform");
	ImGui::DragFloat3("Position", &m_Transform.Position.x, 0.1f);
	ImGui::DragFloat3("Rotation", &m_Transform.Rotation.x, 0.1f);
	ImGui::DragFloat3("Scale", &m_Transform.Scale.x, 0.1f);
	ImGui::Checkbox("Wireframe", &m_Debug);
	ImGui::DragFloat("Camera Speed", &m_Camera.Speed);
	ImGui::End();
}

bool Game::OnKeyPressed(Atlas::KeyPressedEvent e)
{
	if (e.GetKeyCode() == Atlas::Keyboard::Key::F5)
	{
		m_Status = !m_Status;
		Atlas::Application::Get().GetWindow()->SetCursorStatus(m_Status);
		return true;
	}
	if (e.GetKeyCode() == Atlas::Keyboard::Key::Escape)
	{
		Atlas::Application::Get().Close();
		return true;
	}

	return false;
}
