#ifndef					AGGROCIRCLESYSTEM_HPP_
# define				AGGROCIRCLESYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/AggroCircleComponent.hpp"
# include				"components/PositionComponent.hpp"

class					AggroCircleSystem : public System::Base
{
public:
  AggroCircleSystem(void)
    : System::Base()
  {

  }

  virtual ~AggroCircleSystem()
  {

  }

  virtual void				init(void)
  {

  }

  virtual void				update(const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<AggroCircle>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    EntityManager::VectorEntityIT	otherActualEntity = entities->begin();
	    EntityManager::VectorEntityIT	otherLastEntity = entities->end();

	    for (; otherActualEntity != otherLastEntity; ++otherActualEntity)
	      {
		if (otherActualEntity != actualEntity)
		  {
		    Entity			&otherEntity = *(*otherActualEntity);
		    if (collide_(entity, otherEntity))
		      std::cout << "AGGRO" << std::endl;
		  }
	      }
	  }
      }
  }

  void					draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<AggroCircle>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			&p = EntityManager::getInstance().getComponent<Position>(entity);
	    AggroCircle			&ac = EntityManager::getInstance().getComponent<AggroCircle>(entity);
	    al_draw_circle(p.x + (ac.entitySize / 2), p.y + (ac.entitySize / 2), ac.radius, al_map_rgb(0, 255, 0), 1);
	  }
      }
  }

protected:

private:
  AggroCircleSystem			&operator=(const AggroCircleSystem &other);
  AggroCircleSystem(const AggroCircleSystem &other);

  bool					collide_(Entity &entity1, Entity &entity2) const
  {
    Position			&p1 = EntityManager::getInstance().getComponent<Position>(entity1);
    AggroCircle			&ac1 = EntityManager::getInstance().getComponent<AggroCircle>(entity1);
    Position			&p2 = EntityManager::getInstance().getComponent<Position>(entity2);
    AggroCircle			&ac2 = EntityManager::getInstance().getComponent<AggroCircle>(entity2);

    int dx = (p1.x + (ac1.entitySize / 2)) - (p2.x + (ac2.entitySize / 2));
    int dy = (p1.y + (ac1.entitySize / 2)) - (p2.y + (ac2.entitySize / 2));
    int radii = ac1.radius + ac2.radius;
    if (((dx * dx)  + (dy * dy)) < (radii * radii))
      return true;
    return false;
  }
};

#endif					/* !AGGROCIRCLESYSTEM_HPP_ */
