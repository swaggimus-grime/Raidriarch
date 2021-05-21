#include "raidpch.h"
#include "App.h"

#include <glad/glad.h>

namespace Raid {

#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App* App::s_Instance = nullptr;

	App::App()
	{
		RAID_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] = {
			-0.5, -0.5, 0.f,
			0.f, 0.5, 0.f,
			0.5, -0.5, 0.f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

		unsigned int indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main() {
				gl_Position = vec4(a_Position, 1.f);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(1.f, 0.f, 0.f, 1.f);
			}

		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}


	App::~App()
	{
	}

	void App::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, (void*)0);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		RAID_CORE_TRACE("{0}", e);

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();) {
			(*--i)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}