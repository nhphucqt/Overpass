#include <Train.hpp>

Train::Train(const TextureManager& textures): 
Entity(textures.get(TextureID::Train)) {
	sprite.setOrigin(0, sprite.getGlobalBounds().height);
	scale(0.5, 0.5);
}

unsigned int Train::getCategory() const {
    return Category::Train;
}

sf::FloatRect Train::getBoundingRect() const {
    sf::FloatRect rect = Entity::getBoundingRect();
	rect.top = rect.top + 54;
	rect.height = 128;
	return rect;
}

Train::TrainData Train::serialize() const {
	TrainData data;
	data.posX = getPosition().x;
	data.posY = getPosition().y;
	data.vx = getVelocity().x;
	data.vy = getVelocity().y;
	data.scaleX = getScale().x;
	data.scaleY = getScale().y;

	return data;
}

void Train::deserialize(Train::TrainData& data) {
	setPosition(data.posX, data.posY);
	setVelocity(data.vx, data.vy);
	setScale(data.scaleX, data.scaleY);
}
