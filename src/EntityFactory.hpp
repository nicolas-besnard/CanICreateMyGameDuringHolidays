#ifndef					ENTITYFACTORY_HPP_
# define				ENTITYFACTORY_HPP_

# include				<cmath>

# include				"Singleton.hpp"

# include				"managers/EntityManager.hh"

# include				"components/ShipComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/BoundingBoxComponent.hpp"
# include				"components/AggroCircleComponent.hpp"
# include				"components/TagComponent.hpp"
# include				"components/SpeedComponent.hpp"
# include				"components/OrientationComponent.hpp"
# include				"components/VelocityComponent.hpp"
# include				"components/MovementComponent.hpp"
# include				"components/MouseComponent.hpp"
# include				"components/ImageComponent.hpp"

class					EntityFactory : public Singleton<EntityFactory>
{
  friend class Singleton<EntityFactory>;

public:
  Entity				&createCrosshair(void) const
  {
    Entity				&entity = getEntity_();

    EntityManager::getInstance().addComponent<Mouse>(entity);
    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);
    p.x = 0;
    p.y = 0;

    Tag					&t = EntityManager::getInstance().addComponent<Tag>(entity);
    t.name = "crosshair";

    return				entity;
  }

  Entity				&createComet(float posX, float posY) const
  {
    Entity				&entity = getEntity_();

    Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
    s.size = 50;

    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);
    p.x = posX;
    p.y = posY;

    BoundingBox				&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
    bb.sizeX = 50;
    bb.sizeY = 50;

    AggroCircle				&ac = EntityManager::getInstance().addComponent<AggroCircle>(entity);
    ac.radius = 200;
    ac.entitySize = s.size;

    Speed				&speed = EntityManager::getInstance().addComponent<Speed>(entity);
    speed.value = 500;

    Tag					&t = EntityManager::getInstance().addComponent<Tag>(entity);
    t.name = "Enemy";

    return				entity;
  }


  Entity				&createBullet(Entity &parent) const
  {
    Entity				&entity = getEntity_();

    EntityManager::getInstance().addComponent<Movement>(entity);

    Image				&image = EntityManager::getInstance().addComponent<Image>(entity);
    image.isInit = false;
    image.url = "./assets/images/missile.png";

    Position				*parentPosition = EntityManager::getInstance().getComponent<Position>(parent);
    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);
    p.x = parentPosition->x + 10;
    p.y = parentPosition->y + 10;

    BoundingBox				&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
    bb.sizeX = 10;
    bb.sizeY = 10;

    Speed				&speed = EntityManager::getInstance().addComponent<Speed>(entity);
    speed.value = 500;

    Tag					&t = EntityManager::getInstance().addComponent<Tag>(entity);
    t.name = "Bullet";

    Orientation				*parentOrientation = EntityManager::getInstance().getComponent<Orientation>(parent);
    Velocity				&v = EntityManager::getInstance().addComponent<Velocity>(entity);
    v.x = cos(parentOrientation->radian - M_PI / 2) * speed.value;
    v.y = sin(parentOrientation->radian - M_PI / 2) * speed.value;

    return				entity;
  }

  Entity				&createMissile(Entity &parent) const
  {
    Entity				&entity = getEntity_();

    Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
    s.size = 10;

    Position				*parentPosition = EntityManager::getInstance().getComponent<Position>(parent);
    Orientation				*parentOrientation = EntityManager::getInstance().getComponent<Orientation>(parent);
    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);

    p.x = parentPosition->x + 1;
    p.y = parentPosition->y + 1;

    BoundingBox				&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
    bb.sizeX = 10;
    bb.sizeY = 10;

    Speed				&speed = EntityManager::getInstance().addComponent<Speed>(entity);
    speed.value = 200;

    AggroCircle				&ac = EntityManager::getInstance().addComponent<AggroCircle>(entity);
    ac.radius = 50;
    ac.entitySize = s.size;

    Tag					&t = EntityManager::getInstance().addComponent<Tag>(entity);
    t.name = "Missile";

    Orientation				&o = EntityManager::getInstance().addComponent<Orientation>(entity);
    Velocity				&v = EntityManager::getInstance().addComponent<Velocity>(entity);

    v.x = cos(parentOrientation->radian) * speed.value;
    v.y = sin(parentOrientation->radian) * speed.value;

    return				entity;
  }

protected:

private:
  EntityFactory(void)
  {

  }

  ~EntityFactory()
  {

  }
  EntityFactory					&operator=(const EntityFactory &other);
  EntityFactory(const EntityFactory &other);

  Entity				&getEntity_(void) const
  {
    return EntityManager::getInstance().getNewEntity();
  }
};

#endif					/* !ENTITYFACTORY_HPP_ */
