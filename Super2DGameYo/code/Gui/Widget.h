#pragma once
#include "entt/entt.hpp"

namespace gui
{
	class Widget
	{
	public:

		entt::entity& getEntity();

	protected:
		Widget(entt::entity e);

		entt::entity m_entity;
	private:
	};
}