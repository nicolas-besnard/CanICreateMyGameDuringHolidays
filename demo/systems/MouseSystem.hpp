#ifndef					MOUSESYSTEM_HPP_
# define				MOUSESYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/MouseComponent.hpp"


#include			<iostream>

class					MouseSystem : public System::Base
{
public:
  MouseSystem(void)
    : System::Base()
  {}

  virtual ~MouseSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double, const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Mouse>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);

	    ALLEGRO_MOUSE_STATE		state;
	    al_get_mouse_state(&state);

	    p->x = state.x;
	    p->y = state.y;
	  }
      }
  }

  virtual void				draw(void) const
  {}

protected:

private:
  MouseSystem					&operator=(const MouseSystem &other);
  MouseSystem(const MouseSystem &other);
};

#endif					/* !MOUSESYSTEM_HPP_ */
