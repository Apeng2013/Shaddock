#pragma once

#include "Shaddock/Core/Core.h"
#include "Shaddock/Events/Event.h"
#include "Shaddock/Core/Timestep.h"


namespace Shaddock {
	class SHADDOCK_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}
		
		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}