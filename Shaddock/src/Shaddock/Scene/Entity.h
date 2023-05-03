#pragma once
#include "Shaddock/Scene/Scene.h"
#include "entt/entity/registry.hpp"

namespace Shaddock {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			//SD_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent()
		{
			//SD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		template<typename T>
		bool HasComponent()
		{
			return false;
			//return m_Scene->m_Registry.get
		}
		template<typename T>
		void RemoveComponent()
		{
			//SD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityHandle{ entt::null };
	};
}