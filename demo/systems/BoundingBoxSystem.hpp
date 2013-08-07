#ifndef					BOUNDINGBOXSYSTEM_HPP_
# define				BOUNDINGBOXSYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/PositionComponent.hpp"
# include				"components/BoundingBoxComponent.hpp"
# include				"components/TagComponent.hpp"

class					BoundingBoxSystem : public System::Base
{
public:
  BoundingBoxSystem(void)
    : System::Base()
  {}

  virtual ~BoundingBoxSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double, const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<BoundingBox>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    EntityManager::VectorEntityIT	otherActualEntity = entities->begin();
	    EntityManager::VectorEntityIT	otherLastEntity = entities->end();

	    for (; otherActualEntity != otherLastEntity; ++otherActualEntity)
	      {
		if (otherActualEntity != actualEntity)
		  {
		    Entity			&otherEntity = *(*otherActualEntity);
		    if (collide_(entity, otherEntity))
		      {
			Tag			*t1 = EntityManager::getInstance().getComponent<Tag>(entity);
			Tag			*t2 = EntityManager::getInstance().getComponent<Tag>(otherEntity);

			if (((t1->name == "Bullet" || t1->name == "Missile") && t2->name == "Enemy") || ((t2->name == "Bullet" || t2->name == "Missile") && t1->name == "Enemy"))
			  {
			    EntityManager::getInstance().deleteEntity(entity);
			    EntityManager::getInstance().deleteEntity(otherEntity);
			    return ;
			  }
		      }
		  }
	      }
	  }
	delete entities;
      }
  }

  virtual void				draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<BoundingBox>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    BoundingBox			*bb = EntityManager::getInstance().getComponent<BoundingBox>(entity);

	    if (p && bb)
	      al_draw_rectangle(p->x, p->y, p->x + bb->sizeX, p->y + bb->sizeY, al_map_rgb(0, 255, 0), 1);
	  }
	delete entities;
      }
  }

protected:

private:
  BoundingBoxSystem			&operator=(const BoundingBoxSystem &other);
  BoundingBoxSystem(const BoundingBoxSystem &other);

  bool					collide_(Entity &entity1, Entity &entity2) const
  {
    Position				*p1 = EntityManager::getInstance().getComponent<Position>(entity1);
    BoundingBox				*bb1 = EntityManager::getInstance().getComponent<BoundingBox>(entity1);
    Position				*p2 = EntityManager::getInstance().getComponent<Position>(entity2);
    BoundingBox				*bb2 = EntityManager::getInstance().getComponent<BoundingBox>(entity2);

    if (p1 && p2 && bb1 && bb2)
      {
	if ( (abs(p1->x - p2->x) * 2 < (bb1->sizeX + bb2->sizeX)) &&
	     (abs(p1->y - p2->y) * 2 < (bb1->sizeY + bb2->sizeY))
	     )
	  return true;
	return false;
      }
    return false;
  }
};

#endif					/* !BOUNDINGBOXSYSTEM_HPP_ */
