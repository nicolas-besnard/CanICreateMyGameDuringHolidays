#ifndef					ENTITYFACTORY_HPP_
# define				ENTITYFACTORY_HPP_

# include				"Singleton.hpp"

# include				"managers/EntityManager.hh"

# include				"components/ShipComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/BoundingBoxComponent.hpp"
# include				"components/AggroCircleComponent.hpp"

class					EntityFactory : public Singleton<EntityFactory>
{
  friend class Singleton<EntityFactory>;

public:
  Entity				&createComet(void) const
  {
    Entity				&entity = EntityManager::getInstance().getNewEntity();

    Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
    s.size = 50;

    Position				&p = EntityManager::getInstance().addComponent<Position>(entity);
    p.x = 600;
    p.y = 400;

    BoundingBox				&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
    bb.sizeX = 50;
    bb.sizeY = 50;

    AggroCircle				&ac = EntityManager::getInstance().addComponent<AggroCircle>(entity);
    ac.radius = 200;
    ac.entitySize = s.size;
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
};

#endif					/* !ENTITYFACTORY_HPP_ */
