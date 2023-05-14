#pragma once

#include "entt/entity/registry.hpp"
#include "Shaddock/Core/Timestep.h"
#include "Shaddock/Renderer/EditorCamera.h"

namespace Shaddock {

	class Entity;
	class SceneHierarchyPanel;
	class SceneSerializer;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep& ts);
		void OnUpdateEditor(Timestep& ts, EditorCamera& camera);

		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	};
}