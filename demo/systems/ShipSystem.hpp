#ifndef					SHIPSYSTEM_HPP_
# define				SHIPSYSTEM_HPP_

# include				<allegro5/allegro.h>
# include				<cmath>

# include				"systems/Base.hpp"
# include				"EntityManager.hh"

# include				"components/ShipComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/OrientationComponent.hpp"

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

  virtual void				update(double, const ALLEGRO_EVENT &)
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
	    Position			*p = EntityManager::getInstance().getComponent<Position>(*(*actualEntity));
	    Ship			*s = EntityManager::getInstance().getComponent<Ship>(*(*actualEntity));
	    Orientation			*o = EntityManager::getInstance().getComponent<Orientation>(*(*actualEntity));

	    if (p && s)
	      al_draw_filled_rectangle(p->x, p->y, p->x + s->size, p->y + s->size, al_map_rgb(255, 0, 0));
	    if (o && p)
	      {
		// double dirX = (p->x + 25) + cos(o->radian) * 200;
		// double dirY = (p->y + 25) + sin(o->radian) * 200;
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		double dirX1 = state.x - (p->x + 25);
		double dirY1 = state.y - (p->y + 25);

		double a = atan2(dirY1, dirX1);
		// if (a < 0)
		  // a = M_PI * 2 + a;
		double dirX = (p->x + 25) + cos(a) * 200;
		double dirY = (p->y + 25) + sin(a) * 200;

		al_draw_line(p->x + 25, p->y + 25, dirX, dirY, al_map_rgb(0, 0, 255), 1);

		double xdif = (p->x + 25) - dirX;
		double ydif = (p->y + 25) - dirY;
		double a1 = (p->x + 25) - ydif / 2;
		double b1 = (p->y + 25) + xdif / 2;
		double a2 = (p->x + 25) + ydif / 2;
		double b2 = (p->y + 25) - xdif / 2;

		al_draw_line(a1, b1, a2, b2, al_map_rgb(0, 0, 255), 1);
	      }
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
