#include "portal.hpp"

#include "engine.hpp"

namespace town
{
    Portal::Portal(sf::Vector2i pos1, sf::Vector2i pos2) :
        _pos1(pos1), _pos2(pos2), _inUse(false), _rotation(0.0f)
    {

    }
    Portal::~Portal()
    {

    }

    sf::Vector2i Portal::pos1() const
    {
        return _pos1;
    }
    sf::Vector2i Portal::pos2() const
    {
        return _pos2;
    }

    void Portal::setInUse(bool inUse, float rotation)
    {
        _inUse = inUse;
        _rotation = rotation;
    }
    bool Portal::isInUse() const
    {
        return _inUse;
    }

    void Portal::update(float dt)
    {

    }
    void Portal::draw(Engine *engine, sf::RenderTarget &target)
    {
        auto index = _inUse ? 2 : 0;

        drawSprite(engine, target, _pos1, _rotation, index);
        drawSprite(engine, target, _pos2, _rotation + 180.0f, index);
    }

    void Portal::drawSprite(Engine *engine, sf::RenderTarget &target, sf::Vector2i position, float rotation, int index)
    {
        const float size = engine->spriteSize();
        const float scale = engine->spriteScale();
        const float combinedScale = engine->spriteScaleCombined();

        const sf::Vector2f halfSize(size * 0.5f, size * 0.5f);

        auto sprite = engine->portalTiles()->getSprite(index);
        sprite->setOrigin(halfSize);

        auto pos = (sf::Vector2f(position) * combinedScale) + (halfSize * scale);
        sprite->setPosition(pos);
        sprite->setRotation(rotation);

        target.draw(*sprite);
    }
} // namespace town
