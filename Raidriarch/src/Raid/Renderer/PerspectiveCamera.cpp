#include "raidpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Raid/Core/Input.h"
#include "Raid/Core/KeyCodes.h"
#include "Raid/Core/Core.h"

static glm::vec3 worldUp = { 0.f, 1.f, 0.f };
static float lastX = 0.f;
static float lastY = 0.f;

namespace Raid {
	//////////////////////////////////////////////
	///---Perspective Camera---/////////////////
	////////////////////////////////////////////
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane))
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(3), glm::vec3(0, 1, 0));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		lastX = Input::GetMouseX();
		lastY = Input::GetMouseY();
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		front.y = sin(glm::radians(m_Rotation.x));
		front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		front = glm::normalize(front);

		glm::vec3 right = glm::normalize(glm::cross(front, worldUp));  
		glm::vec3 up = glm::normalize(glm::cross(right, front));
		
		m_ViewMatrix = glm::lookAt(m_Position, m_Position * front, up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	//////////////////////////////////////////////
	///---Perspective Camera Controller---//////
	////////////////////////////////////////////
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(m_ZoomLevel, 1280.f / 720.f, 0.1f, 100.f)
	{
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(RAID_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(RAID_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(RAID_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(RAID_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio, 0.1f, 100.f);
		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		auto currentPos = Input::GetMousePosition();
		float xoffset = currentPos.first - lastX;
		float yoffset = lastY - currentPos.second; // reversed since y-coordinates go from bottom to top

		lastX = currentPos.first;
		lastY = currentPos.second;

		xoffset *= 0.1f;
		yoffset *= 0.1f;

		m_Rotation.y += xoffset;
		m_Rotation.x += yoffset;

		if (m_Rotation.x > 89.0f)
			m_Rotation.x = 89.0f;
		if (m_Rotation.x < -89.0f)
			m_Rotation.x = -89.0f;

		m_Camera.SetRotation(m_Rotation);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio, 0.1f, 100.f);
		return false;
	}
}