#pragma once

#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/Timestep.h"
#include "Shaddock/Events/Event.h"


namespace Shaddock {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}
		
		const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}