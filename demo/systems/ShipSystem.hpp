#ifndef					SHIPSYSTEM_HPP_
# define				SHIPSYSTEM_HPP_

# include				<allegro5/allegro.h>

# include				"systems/Base.hpp"
# include				"EntityManager.hh"

# include				"components/ShipComponent.hpp"
# include				"components/PositionComponent.hpp"

class					ShipSystem : public System::Base
{
public:
  ShipSystem(void)
    : System::Base()
  {}

  virtual ~ShipSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(const ALLEGRO_EVENT &)
  {}

  virtual void				draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Ship>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Position			&p = EntityManager::getInstance().getComponent<Position>(*(*actualEntity));
	    Ship			&s = EntityManager::getInstance().getComponent<Ship>(*(*actualEntity));
	    al_draw_filled_rectangle(p.x, p.y, p.x + s.size, p.y + s.size, al_map_rgb(255, 0, 0));
	  }
	delete entities;
      }
  }

protected:

private:
  ShipSystem				&operator=(const ShipSystem &other);
  ShipSystem(const ShipSystem &other);
};

#endif					/* !SHIPSYSTEM_HPP_ */
