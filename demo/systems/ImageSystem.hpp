#ifndef					IMAGESYSTEM_HPP_
# define				IMAGESYSTEM_HPP_

# include				<allegro5/allegro.h>
# include				<allegro5/allegro_image.h>

# include				"systems/Base.hpp"

# include				"components/ImageComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/OrientationComponent.hpp"

class					ImageSystem : public System::Base
{
public:
  ImageSystem(void)
    : System::Base()
  {}

  virtual ~ImageSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double dt, const ALLEGRO_EVENT &)
  {}

  virtual void				draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Image>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    Image			*i = EntityManager::getInstance().getComponent<Image>(entity);

	    Entity			*mouse = EntityManager::getInstance().getMouseEntity();
	    Position			*mousePosition = EntityManager::getInstance().getComponent<Position>(*mouse);

	    float			radian = atan2(mousePosition->y - (p->y + 24) , mousePosition->x - (p->x + 24)) + M_PI / 2;

	    if (i->isInit == false)
	      {
		i->image = al_load_bitmap(i->url.c_str());

		if (!i->image)
		  {
		    std::cout << "ERROR IMAGE" << std::endl;
		    std::cout << "Load " << i->url.c_str() << std::endl;
		    exit (0);
		  }
	      }
	    al_draw_bitmap(i->image, p->x, p->y, 0);
	  }
      }
  }

protected:

private:
  ImageSystem					&operator=(const ImageSystem &other);
  ImageSystem(const ImageSystem &other);
};

#endif					/* !IMAGESYSTEM_HPP_ */
