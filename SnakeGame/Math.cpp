#include "Math.h"

namespace SnakeGame 
{
	bool DoShapesCollide(const Rectangle& rectangle1, const Rectangle& rectangle2)
	{
		return rectangle1.position.x < rectangle2.position.x + rectangle2.size.x &&
			rectangle1.position.x + rectangle1.size.x > rectangle2.position.x &&
			rectangle1.position.y < rectangle2.position.y + rectangle2.size.y &&
			rectangle1.position.y + rectangle1.size.y > rectangle2.position.y;
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return{
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		//Calculate total width/height of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getLocalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height = itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}

			totalRect.left = position.x - origin.x * totalRect.width;
			totalRect.top = position.y - origin.y * totalRect.height;
			sf::Vector2f currentPos = { totalRect.left, totalRect.top };

			for (auto it = items.begin(); it != items.end(); ++it)
			{
				sf::FloatRect itemRect = (*it)->getLocalBounds();
				sf::Vector2f itemOrigin;

				if (orientation == Orientation::Horizontal)
				{
					itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Mid ? 0.5f : 1.f;
					itemOrigin.x = 0.f;
					currentPos.y = totalRect.top, +itemOrigin.y * totalRect.height;
				}
				else
				{
					itemOrigin.y = 0.f;
					itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Mid ? 0.5f : 1.f;
					currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
				}

				(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
				(*it)->setPosition(currentPos);
				window.draw(**it);

				if (orientation == Orientation::Horizontal)
				{
					currentPos.x += itemRect.width + spacing;
				}
				else
				{
					currentPos.y += itemRect.height + spacing;
				}
			}
		}
	}
}
