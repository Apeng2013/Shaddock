#pragma once

#include "Shaddock/Core/Layer.h"
#include "Shaddock/Events/KeyEvent.h"
#include "Shaddock/Events/ApplicationEvent.h"
#include "Shaddock/Events/MouseEvent.h"

namespace Shaddock {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}