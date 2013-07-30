#ifndef					POSITIONSYSTEM_HPP_
# define				POSITIONSYSTEM_HPP_

# include				"System.hpp"
# include				"EntityManager.hh"
# include				"components/Position.hh"

class					PositionSystem : public System
{
public:
  PositionSystem(void)
    : System()
  {}
  virtual ~PositionSystem()
  {}

  virtual void				update(void)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Position>();

    if (entities)
      {
	std::cout << "FIND ENTITY" << std::endl;
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Position			&p = EntityManager::getInstance().getComponent<Position>(*(*actualEntity));
	    std::cout << "Position [" << p.x << "; " << p.y << "]" << std::endl;
	    p.x += 1;
	  }
      }
    else
      {
	std::cout << "DON'T FIND ENTITY" << std::endl;
      }
  }

protected:

private:
  PositionSystem					&operator=(const PositionSystem &other);
  PositionSystem(const PositionSystem &other);
};

#endif					/* !POSITIONSYSTEM_HPP_ */
