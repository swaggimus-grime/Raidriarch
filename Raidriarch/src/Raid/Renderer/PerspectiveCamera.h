#pragma once

#include "Raid/Events/AppEvent.h"
#include "Raid/Events/MouseEvent.h"
#include "Raid/Core/Timestep.h"

#include <glm/glm.hpp>

namespace Raid {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov = 45.f, float aspectRatio = 16 / 9, float nearPlane = 0.1f, float farPlane = 100.f);

		void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::vec2& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec2& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_Rotation = { 0.f, -90.f };
	};

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_Rotation = { 0.f, -90.f };

		float m_CameraTranslationSpeed = 5.0f;
	};
}