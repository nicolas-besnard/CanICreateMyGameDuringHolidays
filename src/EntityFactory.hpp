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

class					EntityFactory : public Singleton<EntityFactory>
{
  friend class Singleton<EntityFactory>;

public:
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

    Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
    s.size = 10;

    Position				*parentPosition = EntityManager::getInstance().getComponent<Position>(parent);
    Ship				*parentShip = EntityManager::getInstance().getComponent<Ship>(parent);
    Orientation				*parentOrientaion = EntityManager::getInstance().getComponent<Orientation>(parent);
    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);

    p.x = parentPosition->x + (parentShip->size / 2);
    p.y = parentPosition->y + (parentShip->size / 2);

    BoundingBox				&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
    bb.sizeX = 10;
    bb.sizeY = 10;

    Speed				&speed = EntityManager::getInstance().addComponent<Speed>(entity);
    speed.value = 500;

    Tag					&t = EntityManager::getInstance().addComponent<Tag>(entity);
    t.name = "Bullet";

    Orientation				&o = EntityManager::getInstance().addComponent<Orientation>(entity);
    o.radian = parentOrientaion->radian;

    return				entity;
  }

  Entity				&createMissile(Entity &parent) const
  {
    Entity				&entity = getEntity_();

    Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
    s.size = 10;

    Position				*parentPosition = EntityManager::getInstance().getComponent<Position>(parent);
    Ship				*parentShip = EntityManager::getInstance().getComponent<Ship>(parent);
    Orientation				*parentOrientaion = EntityManager::getInstance().getComponent<Orientation>(parent);
    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);
    p.x = parentPosition->x + (parentShip->size / 2);
    p.y = parentPosition->y + (parentShip->size / 2);

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
    o.radian = parentOrientaion->radian;

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
