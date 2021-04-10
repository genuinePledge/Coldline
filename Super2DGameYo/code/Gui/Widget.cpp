#include "Widget.h"

entt::entity& gui::Widget::getEntity()
{
	return m_entity;
}

gui::Widget::Widget(entt::entity e)
	: m_entity(e)
{ }
