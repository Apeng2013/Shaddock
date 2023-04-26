#include "sdpch.h"
#include "Shaddock/Scene/Entity.h"

namespace Shaddock {
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

	Entity::~Entity()
	{

	}
}