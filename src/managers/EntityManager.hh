#ifndef				ENTITYMANAGER_HH_
# define			ENTITYMANAGER_HH_

# include			"Singleton.hpp"
# include			"Entity.hpp"

class				EntityManager : public Singleton<EntityManager>
{
  friend class Singleton<EntityManager>;

public:
  Entity			&getNewEntity()
  {
    Entity			*e = new Entity(idCounter_++);
    return *e;
  }

private:
  EntityManager(void)
    : idCounter_(0)
  {}

  virtual ~EntityManager() {}
  entitymanager 			&operator=(const entitymanager &other);
  EntityManager(const EntityManager &other);

  int				idCounter_;
};

#endif				/* !ENTITYMANAGER_HH_ */
