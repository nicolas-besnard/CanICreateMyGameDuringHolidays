#ifndef					INPUTMOVEMENTSYSTEM_HPP_
# define				INPUTMOVEMENTSYSTEM_HPP_

# include				"components/PositionComponent.hpp"
# include				"components/InputMovementComponent.hpp"

# include				"systems/Base.hpp"
# include				"systems/InputSystem.hpp"

# include				"managers/EntityManager.hh"

class					InputMovementSystem : public System::Base
{
public:
  InputMovementSystem(void)
    : System::Base()
  {

  }

  virtual ~InputMovementSystem()
  {

  }

  virtual void				init(void)
  {

  }

  virtual void				update(const ALLEGRO_EVENT &)
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
	    Position &p = EntityManager::getInstance().getComponent<Position>(entity);
	    InputMovement &m = EntityManager::getInstance().getComponent<InputMovement>(entity);

	    // Get system handling input
	    InputSystem			*input = SystemManager::getInstance().getSystem<InputSystem>();

	    if (input)
	      {
		if (input->isKeyDown(m.keyUp))
		  {
		    p.y -= 1;
		  }
		if (input->isKeyDown(m.keyDown))
		  {
		    p.y += 1;
		  }
		if (input->isKeyDown(m.keyLeft))
		  {
		    p.x -= 1;
		  }
		if (input->isKeyDown(m.keyRight))
		  {
		    p.x += 1;
		  }
	      }
	    else
	      {
		std::cout << "OMG ERROR" << std::endl;
	      }
	  }
      }
  }


protected:

private:
  InputMovementSystem					&operator=(const InputMovementSystem &other);
  InputMovementSystem(const InputMovementSystem &other);
};


#endif					/* !INPUTMOVEMENTSYSTEM_HPP_ */
