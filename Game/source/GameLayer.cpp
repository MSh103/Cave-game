#include "GameLayer.h"


Game::Game() 
	: Layer("GameLayer"), m_Camera({{0.f, 0.f, 0.f}, 75.f})
{}

void Game::OnAttach()
{
	m_Color.r = 0.0f;
	m_Color.g = 0.0f;
	m_Color.b = 0.0f;

	Vertex vertices[8] = {
		{ {-0.5f, 0.5f,  0.5f}, {1.f, 0.f, 0.f} }, // TL
		{ {-0.5f,-0.5f,  0.5f}, {0.f, 1.f, 0.f} }, // BL
		{ { 0.5f,-0.5f,  0.5f}, {0.f, 0.f, 1.f} }, // BR
		{ { 0.5f, 0.5f,  0.5f}, {1.f, 1.f, 1.f} }, // TR

		{ { 0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f} }, // TR
		{ { 0.5f,-0.5f, -0.5f}, {0.f, 0.f, 1.f} }, // BR
		{ {-0.5f,-0.5f, -0.5f}, {0.f, 1.f, 0.f} }, // BL
		{ {-0.5f, 0.5f, -0.5f}, {1.f, 0.f, 0.f} }, // TL
	};

	uint32_t indices[3*4] = {
		0, 1, 2,
		2, 3, 0,
		
		4, 5, 6,
		6, 7, 4,
	};

	for (int i = 0; i < 8; i++)
		m_MeshCPU.pushVertex(vertices[i]);
	for (int i = 0; i < 12; i++)
		m_MeshCPU.pushIndex(indices[i]);

	m_MeshGPU.addMeshCPU(&m_MeshCPU);

	//m_VAO = std::make_unique<Atlas::VertexArray>();
	m_Shader = std::make_shared<Atlas::Shader>();

	m_Shader->LoadFromFile(Atlas::ShaderType::Vertex, "assets/Vertex.glsl");
	m_Shader->LoadFromFile(Atlas::ShaderType::Fragment, "assets/Fragment.glsl");
	//m_Shader->LoadFromFile(Atlas::ShaderType::Basic, "assets/Basic.glsl");
	m_Shader->LinkObjectsToProgram();

	//std::shared_ptr<Atlas::VertexBuffer> VBO = std::make_shared<Atlas::VertexBuffer>(vertices, sizeof(Vertex) * 4);
	//VBO->Use();
	//VBO->SetLayout({
	//	{Atlas::ShaderDataType::Float3, "a_Position"},
	//	{Atlas::ShaderDataType::Float3, "a_Color"},
	//	});
	//m_VAO->Use();
	//m_VAO->AddVertexBuffer(VBO);

	//std::shared_ptr<Atlas::IndexBuffer> IBO = std::make_shared<Atlas::IndexBuffer>(indices, 6);
	//IBO->Use();
	//m_VAO->SetIndexBuffer(IBO);

	m_Transform.Position = { 0.f, 0.f, 0.f };
	m_Transform.Rotation = { 0.f, 0.f, 0.f };
	m_Transform.Scale = { 1.f, 1.f, 1.f };

	m_Model = glm::mat4(1.0f);
	//m_View = glm::mat4(1.0f);
	//m_Projection = glm::mat4(1.0f);
	//m_Projection = glm::perspective(glm::radians(45.f), width / height, 0.1f, 100.f);
	//m_View = glm::translate(m_View, glm::vec3(0.f, 0.f, -3.0f));

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

	//glEnable(GL_CULL_FACE);
	glCullFace(GL_CW);
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
