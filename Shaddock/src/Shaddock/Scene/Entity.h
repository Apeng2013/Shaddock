#pragma once
#include "Shaddock/Scene/Scene.h"
#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/Log.h"
#include "Shaddock/Core/UUID.h"
#include "Shaddock/Scene/Component.h"
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
			SD_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}
		template<typename T>
		T& GetComponent()
		{
			SD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			SD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() { return m_EntityHandle != entt::null; }
		operator uint32_t() { return (uint32_t)m_EntityHandle; }
		operator entt::entity() { return m_EntityHandle; }
		bool operator==(const Entity& other) { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) { return !(*this == other); }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; };

	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityHandle{ entt::null };
	};
}