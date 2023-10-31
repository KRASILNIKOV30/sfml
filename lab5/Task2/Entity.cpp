#include "Entity.h"


Entity::Entity(std::string const& filename, std::optional<sf::Vector2f> const size)
{
	LoadImage(filename, size);
}

void Entity::Draw(sf::RenderWindow& window) const
{
	window.draw(m_image);
}

sf::Vector2f Entity::GetSize() const
{
	return static_cast<sf::Vector2f>(m_image.getTexture()->getSize());
}

sf::Sprite& Entity::GetImage()
{
	return m_image;
}

void Entity::Flip()
{
	m_image.scale(-1, 1);
	m_flipped = !m_flipped;
}

bool Entity::IsFlipped() const
{
	return m_flipped;
}

void Entity::LoadImage(std::string const& filename, std::optional<sf::Vector2f> const size)
{
	if (!m_texture.loadFromFile(filename))
	{
		throw std::exception(std::string("Can not load img ").append(filename).c_str());
	}
	m_image.setTexture(m_texture);
	const sf::Vector2f textureSize = static_cast<sf::Vector2f>(m_texture.getSize());
	const sf::Vector2f newSize = size.has_value() ? size.value() : textureSize;
	m_image.setScale(newSize.x / textureSize.x, newSize.y / textureSize.y);
}