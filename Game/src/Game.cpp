#include <Raidriarch.h>

class ExampleLayer : public Raid::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Raid::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Raid::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Raid::VertexBuffer::Create(vertices, sizeof(vertices)));
		Raid::BufferLayout layout = {
			{ Raid::ShaderDataType::Float3, "a_Position" },
			{ Raid::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Raid::IndexBuffer> indexBuffer;
		indexBuffer.reset(Raid::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Raid::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Raid::VertexBuffer> squareVB;
		squareVB.reset(Raid::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Raid::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Raid::IndexBuffer> squareIB;
		squareIB.reset(Raid::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Raid::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Raid::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Raid::Timestep ts) override
	{
		if (Raid::Input::IsKeyPressed(RAID_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Raid::Input::IsKeyPressed(RAID_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Raid::Input::IsKeyPressed(RAID_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Raid::Input::IsKeyPressed(RAID_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Raid::Input::IsKeyPressed(RAID_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Raid::Input::IsKeyPressed(RAID_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Raid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Raid::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Raid::Renderer::BeginScene(m_Camera);

		Raid::Renderer::Submit(m_BlueShader, m_SquareVA);
		Raid::Renderer::Submit(m_Shader, m_VertexArray);

		Raid::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Raid::Event& event) override
	{
	}
private:
	std::shared_ptr<Raid::Shader> m_Shader;
	std::shared_ptr<Raid::VertexArray> m_VertexArray;

	std::shared_ptr<Raid::Shader> m_BlueShader;
	std::shared_ptr<Raid::VertexArray> m_SquareVA;

	Raid::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Game : public Raid::App
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game()
	{

	}

};

Raid::App* Raid::CreateApp()
{
	return new Game();
}