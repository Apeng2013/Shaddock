#pragma once
#include "Shaddock/Renderer/Framebuffer.h"

namespace Shaddock {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{ 
			SD_CORE_ASSERT(index < m_ColorAttachments.size(), "");
			return m_ColorAttachments[index];
		}
		virtual void ClearAttachment(uint32_t attachmentIndex, int value = 0) override;


		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

	private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;
	};
}