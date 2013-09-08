#ifndef					MOVEMENTSYSTEM_HPP_
# define				MOVEMENTSYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/MovementComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/OrientationComponent.hpp"

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

  virtual void				update(double dt, const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Movement>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);
	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    Velocity			*v = EntityManager::getInstance().getComponent<Velocity>(entity);

	    p->x += v->x * dt;
	    p->y += v->y * dt;

	    if (p->x > 800)
	      {
		EntityManager::getInstance().deleteEntity(entity);
	      }
	    if (p->x <= 0)
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
