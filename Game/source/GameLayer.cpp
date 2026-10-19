#include "GameLayer.h"


Game::Game() 
	: Layer("GameLayer"), m_Camera({{-10.f, 128.f, -10.f}, 75.f})
{}

void Game::OnAttach()
{
	m_Color.r = 0.0f;
	m_Color.g = 0.0f;
	m_Color.b = 0.0f;

	m_Texture = new Texture2D("assets/textureAtlas.png");


	m_Shader = std::make_shared<Atlas::Shader>();
	m_Shader->LoadFromFile(Atlas::ShaderType::Vertex, "assets/Vertex.glsl");
	m_Shader->LoadFromFile(Atlas::ShaderType::Fragment, "assets/Fragment.glsl");
	m_Shader->LinkObjectsToProgram();

	for (size_t x = 0; x < 5; x++)
	{
		for (size_t y = 0; y < 5; y++)
		{
			m_Chunks[y][x] = new Chunk({ x, y });
			m_Chunks[y][x]->Generate();
			m_Chunks[y][x]->BuildMesh();
		}
	}

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


	for (size_t i = 0; i < 5; i++)
		for(size_t j = 0; j < 5; j++)
			m_Chunks[i][j]->Render(m_Camera, *m_Texture, *m_Shader);
}

void Game::OnImGuiRender()
{
	ImGui::Begin("Debug");
	ImGui::ColorEdit3("Clear Screen", glm::value_ptr(m_Color));
	ImGui::Separator();
	ImGui::Text("Transform");
	//ImGui::DragFloat3("Position", &m_Transform.Position.x, 0.1f);
	//ImGui::DragFloat3("Rotation", &m_Transform.Rotation.x, 0.1f);
	//ImGui::DragFloat3("Scale", &m_Transform.Scale.x, 0.1f);
	ImGui::Checkbox("Wireframe", &m_Debug);
	ImGui::DragFloat("Camera Speed", &m_Camera.Speed);
	ImGui::Text("Camera Position: %.2f, %.2f, %.2f", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);
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
