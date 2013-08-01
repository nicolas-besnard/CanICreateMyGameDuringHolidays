#ifndef					CREATEENEMYSYSTEM_HPP_
# define				CREATEENEMYSYSTEM_HPP_

# include				"systems/Base.hpp"
# include				"EntityFactory.hpp"

class					CreateEnemySystem : public System::Base
{
public:
  CreateEnemySystem(void)
    : System::Base()
  {

  }

  virtual ~CreateEnemySystem()
  {

  }

  virtual void				init(void)
  {

  }

  virtual void				update(const ALLEGRO_EVENT &event)
  {
    if ((rand() % 500) == 0)
      {
	EntityFactory::getInstance().createComet(800, 30 + rand() % (600 - 60));
      }
  }

protected:

private:
  CreateEnemySystem					&operator=(const CreateEnemySystem &other);
  CreateEnemySystem(const CreateEnemySystem &other);
};

#endif					/* !CREATEENEMYSYSTEM_HPP_ */
