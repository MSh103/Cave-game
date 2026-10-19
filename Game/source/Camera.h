#pragma once

#include <Atlas.h>
#include <Atlas/Renderer/Core/Math.h>

class Camera
{
public:
	typedef struct CameraSpec
	{
		glm::vec3 pos;
		float fov;
	};

	Camera(const CameraSpec& spec);
	~Camera() = default;

	void OnEvent(Atlas::Event& e);
	void OnUpdate(Atlas::TimeStep ts);

	float Speed = 10.f;

	const glm::mat4& GetViewMatrix() const { return m_View; }
	const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
	const glm::vec3& GetPosition() const { return m_Position; }
private:
	bool OnMouseMoved(Atlas::MouseMovedEvent& e);
private:
	glm::mat4 m_View, m_Projection;

	glm::vec3 m_Position, m_Direction;
	float m_Fov;

	float m_LastMouseX, m_LastMouseY;
	float m_Yaw, m_Pitch;

	bool m_FirstMouse = true;

	static constexpr float s_SENSITIVITY = 0.1f;
};
