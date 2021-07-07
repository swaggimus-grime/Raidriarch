#pragma once

#include "Raid/Renderer/Framebuffer.h"

namespace Raid {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferProperties& props);
		virtual ~OpenGLFramebuffer();

		void Reset();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		virtual const FramebufferProperties& GetProperties() const override { return m_Properties; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthStencilAttachment;
		FramebufferProperties m_Properties;
	};

}