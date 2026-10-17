#include "Camera.h"

#include <cmath>

Camera::Camera(const CameraSpec& spec)
{
	m_Position = spec.pos;
	m_Fov = spec.fov;

	m_Direction = glm::vec3(0.f, 0.f, -1.f);

	m_View = glm::mat4(1.0f);

	int width = Atlas::Application::Get().GetWindow()->GetWidth();
	int height = Atlas::Application::Get().GetWindow()->GetHeight();

	m_Projection = glm::perspective(glm::radians(m_Fov), (float)width / (float)height, 0.1f, 300.f);

	m_LastMouseY, m_LastMouseX, m_Pitch = 0.f;
	m_Yaw = -90.f;
}

void Camera::OnEvent(Atlas::Event& e)
{
	Atlas::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Atlas::MouseMovedEvent>(AT_BIND_EVENT_FN(Camera::OnMouseMoved));
}

void Camera::OnUpdate(Atlas::TimeStep ts)
{
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 right = glm::normalize(glm::cross(m_Direction, glm::vec3(0.f, 1.f, 0.f)));

	if (Atlas::Input::IsKeyPressed(Atlas::Keyboard::Key::W))
		m_Position += Speed * ts * m_Direction;
	
	if (Atlas::Input::IsKeyPressed(Atlas::Keyboard::Key::S))
		m_Position -= Speed * ts * m_Direction;


	if (Atlas::Input::IsKeyPressed(Atlas::Keyboard::Key::A))
		m_Position -= Speed * ts * right;

	if (Atlas::Input::IsKeyPressed(Atlas::Keyboard::Key::D))
		m_Position += Speed * ts * right;
}

bool Camera::OnMouseMoved(Atlas::MouseMovedEvent& e)
{
	const auto& [x, y] = e.Get();


	if (m_FirstMouse)
	{
		m_LastMouseX = x;
		m_LastMouseY = y;
		m_FirstMouse = false;
	}
	
	float xOffset = x - m_LastMouseX;
	float yOffset = m_LastMouseY - y;
	m_LastMouseX = x;
	m_LastMouseY = y;

	xOffset *= s_SENSITIVITY;
	yOffset *= s_SENSITIVITY;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	m_Direction.x = std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
	m_Direction.y = std::sin(glm::radians(m_Pitch));
	m_Direction.z = std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));

	return false;
}
