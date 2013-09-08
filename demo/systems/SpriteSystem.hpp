#ifndef					SPRITESYSTEM_HPP_
# define				SPRITESYSTEM_HPP_

# include				<allegro5/allegro.h>
# include				<allegro5/allegro_image.h>

# include				"systems/Base.hpp"

# include				"components/SpriteComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/OrientationComponent.hpp"

class					SpriteSystem : public System::Base
{
public:
  SpriteSystem(void)
    : System::Base()
  {}

  virtual ~SpriteSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double dt, const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Sprite>();

    if (entities)
      {
    	EntityManager::VectorEntityIT	actualEntity = entities->begin();
    	EntityManager::VectorEntityIT	lastEntity = entities->end();
    	for (; actualEntity != lastEntity; ++actualEntity)
    	  {
    	    Entity			&entity = *(*actualEntity);
    	    Sprite			*s = EntityManager::getInstance().getComponent<Sprite>(entity);

    	    // if (s->timeCounter == -1)
    	      // {
    		// s->timeCounter = dt;
    	      // }
    	    // if (dt - s->timeCounter < s->speed || s->stepNumber == 0)
    	      // return ;
    	    ++s->currentStep;
    	    if (s->currentStep >= s->stepNumber + s->from)
    	      s->currentStep = s->from;
    	    // s->timeCounter = dt;
    	  }
      }
  }

  virtual void				draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<Sprite>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    Sprite			*s = EntityManager::getInstance().getComponent<Sprite>(entity);
	    Orientation			*r = EntityManager::getInstance().getComponent<Orientation>(entity);
	    Entity			*mouse = EntityManager::getInstance().getMouseEntity();
	    Position			*mousePosition = EntityManager::getInstance().getComponent<Position>(*mouse);

	    r->radian = atan2(mousePosition->y - (p->y + 24) , mousePosition->x - (p->x + 24)) + M_PI / 2;
	    if (s->isInit == false)
	      {
		s->image = al_load_bitmap(s->url.c_str());
		if (!s->image)
		  {
		    std::cout << "ERROR IMAGE" << std::endl;
		    std::cout << "Load " << s->url.c_str() << std::endl;
		    exit (0);
		  }
	      }
	    // al_draw_bitmap(s->image, p->x, p->y, 0);
	    // al_draw_tinted_scaled_rotated_bitmap_region(s->image,
	    // 						(s->currentStep % s->columnNumber) * s->partWidth,
	    // 						(s->currentStep / s->columnNumber) * s->partHeight,
	    // 						s->partWidth,
	    // 						s->partHeight,
	    // 						al_map_rgba(255, 0, 0, 0),
	    // 						r->radian == 0 ? 0 : s->partWidth / 2,
	    // 						r->radian == 0 ? 0 : s->partHeight / 2,
	    // 						r->radian == 0 ? p->x : p->x + s->partWidth / 2,
	    // 						r->radian == 0 ? p->y : p->y + s->partHeight / 2,
	    // 						1,
	    // 						1,
	    // 						r->radian,
	    // 						0);
	    al_draw_tinted_scaled_rotated_bitmap_region(s->image,
							(s->currentStep % s->columnNumber) * s->partWidth,
							(s->currentStep / s->columnNumber) * s->partWidth,
							s->partWidth,
							s->partHeight,
							al_map_rgba(255, 255, 255, 0),
							r->radian == 0 ? 0 : s->partWidth / 2,
							r->radian == 0 ? 0 : s->partHeight / 2,
							r->radian == 0 ? p->x : p->x + s->partWidth / 2,
							r->radian == 0 ? p->y : p->y + s->partHeight / 2,
							1,
							1,
							r->radian,
							0);

	  }
      }
  }

protected:

private:
  SpriteSystem					&operator=(const SpriteSystem &other);
  SpriteSystem(const SpriteSystem &other);
};

#endif					/* !SPRITESYSTEM_HPP_ */
