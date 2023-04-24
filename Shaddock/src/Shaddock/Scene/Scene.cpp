#include "sdpch.h"

#include "Shaddock/Scene/Scene.h"
#include "Shaddock/Scene/Component.h"
#include "Shaddock/Renderer/Renderer2D.h"

namespace Shaddock {
	Scene::Scene()
		: m_Registry()
	{
	}
	Scene::~Scene()
	{
	}
	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}
	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}