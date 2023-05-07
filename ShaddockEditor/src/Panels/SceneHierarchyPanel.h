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

	private:
		void DrawEntityNode(Entity& entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}