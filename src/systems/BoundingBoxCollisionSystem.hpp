#ifndef					BOUNDINGBOXCOLLISIONSYSTEM_HPP_
# define				BOUNDINGBOXCOLLISIONSYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/PositionComponent.hpp"
# include				"components/BoundingBoxComponent.hpp"

class					BoundingBoxCollisionSystem : public System::Base
{
public:
  BoundingBoxCollisionSystem(void)
    : System::Base()
  {

  }

  ~BoundingBoxCollisionSystem()
  {

  }

  virtual void				init(void)
  {

  }

  virtual void				update(const ALLEGRO_EVENT &)
  {

  }

protected:

private:
  BoundingBoxCollisionSystem					&operator=(const BoundingBoxCollisionSystem &other);
  BoundingBoxCollisionSystem(const BoundingBoxCollisionSystem &other);
};


#endif					/* !BOUNDINGBOXCOLLISIONSYSTEM_HPP_ */
