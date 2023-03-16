#pragma once

#include "Shaddock/Core/Layer.h"
#include "Shaddock/Events/KeyEvent.h"
#include "Shaddock/Events/ApplicationEvent.h"
#include "Shaddock/Events/MouseEvent.h"

namespace Shaddock {

	class SHADDOCK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}