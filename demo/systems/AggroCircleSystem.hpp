#ifndef					AGGROCIRCLESYSTEM_HPP_
# define				AGGROCIRCLESYSTEM_HPP_

# include				<cmath>

# include				"systems/Base.hpp"

# include				"components/AggroCircleComponent.hpp"
# include				"components/PositionComponent.hpp"
# include				"components/TagComponent.hpp"
# include				"components/SpeedComponent.hpp"

class					AggroCircleSystem : public System::Base
{
public:
  AggroCircleSystem(void)
    : System::Base()
  {}

  virtual ~AggroCircleSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double dt, const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<AggroCircle>();

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
		    Entity		&otherEntity = *(*otherActualEntity);
		    Tag			*t1 = EntityManager::getInstance().getComponent<Tag>(entity);
		    Tag			*t2 = EntityManager::getInstance().getComponent<Tag>(otherEntity);

		    if (t1->name == t2->name)
		      continue;
		    if (collide_(entity, otherEntity))
		      {
			if (t1->name == "Player" && t2->name == "Enemy")
			  moveEnemyToPlayer_(otherEntity, entity, dt);
			else if (t1->name == "Enemy" && t2->name == "Player")
			  moveEnemyToPlayer_(entity, otherEntity, dt);
			if (t1->name == "Missile" && t2->name == "Enemy")
			  moveMissileToEnemy_(entity, otherEntity, dt);
			else if (t1->name == "Enemy" && t2->name == "Missile")
			  moveMissileToEnemy_(otherEntity, entity, dt);
		      }
		  }
	      }
	  }
	delete entities;
      }
  }

  virtual void				draw(void) const
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<AggroCircle>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    AggroCircle			*ac = EntityManager::getInstance().getComponent<AggroCircle>(entity);
	    if (p && ac)
	      al_draw_circle(p->x + (ac->entitySize / 2), p->y + (ac->entitySize / 2), ac->radius, al_map_rgb(0, 255, 0), 1);
	  }
	delete entities;
      }
  }

protected:

private:
  AggroCircleSystem			&operator=(const AggroCircleSystem &other);
  AggroCircleSystem(const AggroCircleSystem &other);

  bool					collide_(Entity &entity1, Entity &entity2) const
  {
    Position			*p1 = EntityManager::getInstance().getComponent<Position>(entity1);
    AggroCircle			*ac1 = EntityManager::getInstance().getComponent<AggroCircle>(entity1);
    Position			*p2 = EntityManager::getInstance().getComponent<Position>(entity2);
    AggroCircle			*ac2 = EntityManager::getInstance().getComponent<AggroCircle>(entity2);

    int dx = (p1->x + (ac1->entitySize / 2)) - (p2->x + (ac2->entitySize / 2));
    int dy = (p1->y + (ac1->entitySize / 2)) - (p2->y + (ac2->entitySize / 2));
    int radii = ac1->radius + ac2->radius;
    if (((dx * dx)  + (dy * dy)) < (radii * radii))
      return true;
    return false;
  }

  void					moveEnemyToPlayer_(Entity &enemyEntity, Entity &playerEntity, double dt)
  {
    Position				*playerPosition = EntityManager::getInstance().getComponent<Position>(playerEntity);
    Position				*enemyPosition = EntityManager::getInstance().getComponent<Position>(enemyEntity);

    float				dirX = playerPosition->x - enemyPosition->x;
    float				dirY = playerPosition->y - enemyPosition->y;
    float				hyp = sqrt(dirX * dirX + dirY * dirY);

    if (hyp > 60)
      {
	if (((dirX / hyp) == 0) || ((dirY / hyp) == 0))
	  return ;
	enemyPosition->x += (dirX / hyp) * dt;
	enemyPosition->y += (dirY / hyp) * dt;
      }
  }

  void					moveMissileToEnemy_(Entity &missileEntity, Entity &enemyEntity, double dt)
  {
    Position				*enemyPosition = EntityManager::getInstance().getComponent<Position>(enemyEntity);
    Position				*missilePosition = EntityManager::getInstance().getComponent<Position>(missileEntity);
    Speed				*missileSpeed = EntityManager::getInstance().getComponent<Speed>(missileEntity);

    float				dirX = enemyPosition->x - missilePosition->x;
    float				dirY = enemyPosition->y - missilePosition->y;
    float				hyp = sqrt(dirX * dirX + dirY * dirY);

    if ((dirX / hyp) == 0 || (dirY / hyp) == 0)
      return ;
    missilePosition->x += (dirX / hyp) * 1.5 * missileSpeed->x * dt;
    missilePosition->y += (dirY / hyp) * 1.5 * missileSpeed->x * dt;
  }
};

#endif					/* !AGGROCIRCLESYSTEM_HPP_ */
