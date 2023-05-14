#pragma once

#include "Shaddock/Core/Base.h"
#include "Shaddock/Scene/Scene.h"
#include "Shaddock/Scene/Entity.h"

namespace Shaddock {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene> context);

		void SetContext(const Ref<Scene> context);

		void OnImGuiRender();

		Entity GetSelectedEntity() { return m_SelectionContext; }

	private:
		void DrawEntityNode(Entity& entity);
		void DrawComponents(Entity& entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}