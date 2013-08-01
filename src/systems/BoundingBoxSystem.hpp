#ifndef					BOUNDINGBOXSYSTEM_HPP_
# define				BOUNDINGBOXSYSTEM_HPP_

# include				"systems/Base.hpp"

# include				"components/PositionComponent.hpp"
# include				"components/BoundingBoxComponent.hpp"

class					BoundingBoxSystem : public System::Base
{
public:
  BoundingBoxSystem(void)
    : System::Base()
  {

  }

  virtual ~BoundingBoxSystem()
  {

  }

  virtual void				init(void)
  {

  }

  virtual void				update(const ALLEGRO_EVENT &)
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
		      return ;


		  }
	      }
	  }
      }
  }

  void					draw(void)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<BoundingBox>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			&p = EntityManager::getInstance().getComponent<Position>(entity);
	    BoundingBox			&bb = EntityManager::getInstance().getComponent<BoundingBox>(entity);
	    al_draw_rectangle(p.x, p.y, p.x + bb.sizeX, p.y + bb.sizeY, al_map_rgb(0, 255, 0), 1);
	  }
      }
  }

protected:

private:
  BoundingBoxSystem			&operator=(const BoundingBoxSystem &other);
  BoundingBoxSystem(const BoundingBoxSystem &other);

  bool					collide_(Entity &entity1, Entity &entity2) const
  {
    Position				&p1 = EntityManager::getInstance().getComponent<Position>(entity1);
    BoundingBox				&bb1 = EntityManager::getInstance().getComponent<BoundingBox>(entity1);
    Position				&p2 = EntityManager::getInstance().getComponent<Position>(entity2);
    BoundingBox				&bb2 = EntityManager::getInstance().getComponent<BoundingBox>(entity2);

    if ( (abs(p1.x - p2.x) * 2 < (bb1.sizeX + bb2.sizeX)) &&
    	 (abs(p1.y - p2.y) * 2 < (bb1.sizeY + bb2.sizeY))
    	 )
    // if ( ((p1.x + bb1.sizeX) >= p2.x) &&
    // 	 (p1.x <= (p2.x + bb2.sizeX)) &&
    // 	 ((p1.y + bb1.sizeY) >= p2.y) &&
    // 	 (p1.y <= (p2.y + bb2.sizeY))
    // 	 )
      return true;
    return false;
  }
};

#endif					/* !BOUNDINGBOXSYSTEM_HPP_ */
