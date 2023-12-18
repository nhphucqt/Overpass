#include <Green.hpp>

TextureID toTextureID(Green::Type type) {
	switch (type) {
	case Green::Tree:
		return TextureID::Tree;

	case Green::Bush:
		return TextureID::Bush;

    case Green::CircleBush:
        return TextureID::CircleBush;
	}
	return TextureID::Tree;
}

Green::Green(Type mType, const TextureManager &textures):
type(mType),
Entity(textures.get(toTextureID(mType)))
{
    if (type == Green::Tree)
        sprite.scale(6, 6);
    else if (type == Green::Bush)
        sprite.scale(5, 5);
    else if (type == Green::CircleBush)
        sprite.scale(3, 3);
    sf::FloatRect bounds = sprite.getLocalBounds();
    if (type == Green::Tree)
        sprite.setOrigin(bounds.width / 2.f, bounds.height);
    else
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Green::getCategory() const {
    return Category::Green;
}

void Green::setVelocity(sf::Vector2f velocity) {
}

void Green::setVelocity(float vx, float vy) {
}

void Green::accelerate(sf::Vector2f velocity) {
}

void Green::accelerate(float vx, float vy) {
}