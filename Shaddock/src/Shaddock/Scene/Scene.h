#pragma once

#include "entt/entity/registry.hpp"
#include "Shaddock/Core/Timestep.h"

namespace Shaddock {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}