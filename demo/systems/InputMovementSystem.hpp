#ifndef					INPUTMOVEMENTSYSTEM_HPP_
# define				INPUTMOVEMENTSYSTEM_HPP_

# include				<cmath>

# include				"components/PositionComponent.hpp"
# include				"components/InputMovementComponent.hpp"
# include				"components/OrientationComponent.hpp"

# include				"systems/Base.hpp"
# include				"systems/InputSystem.hpp"

# include				"managers/EntityManager.hh"

# include				"EntityFactory.hpp"

class					InputMovementSystem : public System::Base
{
public:
  InputMovementSystem(void)
    : System::Base()
  {}

  virtual ~InputMovementSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double dt,const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<InputMovement>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    // Get component
	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    InputMovement		*m = EntityManager::getInstance().getComponent<InputMovement>(entity);
	    Orientation			*o = EntityManager::getInstance().getComponent<Orientation>(entity);

	    // Get system handling input
	    InputSystem			*input = SystemManager::getInstance().getSystem<InputSystem>();

	    if (input)
	      {
		ALLEGRO_MOUSE_STATE state;

		al_get_mouse_state(&state);

		double dirX1 = state.x - (p->x + 25);
		double dirY1 = state.y - (p->y + 25);
		double a = atan2(dirY1, dirX1);
		o->radian = a;
		// double dirX = cos(o->radian);
		// double dirY = sin(o->radian);
		double dirX = cos(a);
		double dirY = sin(a);

		if (input->isKeyDown(m->keyUp))
		  {
		    p->x += 1000 * dirX * dt;
		    p->y += 1000 * dirY * dt;
		  }
		if (input->isKeyDown(m->keyDown))
		  {
		    p->x -= 1000 * dirX * dt;
		    p->y -= 1000 * dirY * dt;
		  }
		if (input->isKeyDown(m->keyLeft))
		  {
		    double dirX2 = (p->x + 25) + cos(dirX) * 200;
		    double dirY2 = (p->y + 25) + cos(dirX) * 200;

		    double xdif = (p->x + 25) - dirX;
		    double ydif = (p->y + 25) - dirY;
		    double a1 = (p->x + 25) - ydif / 2;
		    double b1 = (p->y + 25) + xdif / 2;
		    double a2 = (p->x + 25) + ydif / 2;
		    double b2 = (p->y + 25) - xdif / 2;

		    double dirX3 = a2 - a1;
		    double dirY3 = b2 - b1;
		    double b = atan2(dirX3, dirY3);
		    double dirX4 = cos(b);
		    double dirY4 = cos(a);
		    p->x += 1000 * dirX4 * dt;
		    p->y += 1000 * dirY4 * dt;
		    // o->radian += 5 * dt;
		    // if (o->radian > M_PI)
		    //   o->radian = -M_PI;
		    // else if (o->radian < -M_PI)
		    //   o->radian = M_PI;
		  }
		if (input->isKeyDown(m->keyRight))
		  {
		    // o->radian -= 5 * dt;
		    // if (o->radian > M_PI)
		    //   o->radian = -M_PI;
		    // else if (o->radian < -M_PI)
		    //   o->radian = M_PI;
		  }
		if (input->isKeyDown(m->keyShoot))
		  {
		    EntityFactory::getInstance().createBullet(entity);
		    input->setOff(m->keyShoot);
		  }
		if (input->isKeyDown(m->keyMissile))
		  {
		    EntityFactory::getInstance().createMissile(entity);
		    input->setOff(m->keyMissile);
		  }
	      }
	    else
	      {
		std::cout << "OMG ERROR" << std::endl;
	      }
	  }
	delete entities;
      }
  }

  virtual void				draw(void) const
  {}

protected:

private:
  InputMovementSystem			&operator=(const InputMovementSystem &other);
  InputMovementSystem(const InputMovementSystem &other);
};


#endif					/* !INPUTMOVEMENTSYSTEM_HPP_ */
