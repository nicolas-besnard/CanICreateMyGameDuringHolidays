#ifndef					MOVEMENTSYSTEM_HPP_
# define				MOVEMENTSYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/SpeedComponent.hpp"
# include				"components/PositionComponent.hpp"

class					MovementSystem : public System::Base
{
public:
  MovementSystem(void)
    : System::Base()
  {}

  virtual ~MovementSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Speed>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();
	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);
	    Speed			&s = EntityManager::getInstance().getComponent<Speed>(entity);
	    Position			&p = EntityManager::getInstance().getComponent<Position>(entity);

	    p.x += s.x;
	    p.y += s.y;

	    if (p.x > 800)
	      {
		EntityManager::getInstance().deleteEntity(entity);
	      }
	    if (p.x <= 0)
	      {
		EntityManager::getInstance().deleteEntity(entity);
	      }
	  }
	delete entities;
      }
  }

  virtual void				draw() const
  {}

protected:

private:
  MovementSystem			&operator=(const MovementSystem &other);
  MovementSystem(const MovementSystem &other);
};


#endif					/* !MOVEMENTSYSTEM_HPP_ */
