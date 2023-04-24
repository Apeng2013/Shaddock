#pragma once

#include "entt/entity/registry.hpp"
#include "Shaddock/Core/Timestep.h"

namespace Shaddock {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

	};
}