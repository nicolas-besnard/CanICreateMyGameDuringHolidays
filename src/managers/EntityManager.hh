#ifndef					ENTITYMANAGER_HH_
# define				ENTITYMANAGER_HH_

# include				<map>
# include				<typeinfo>

# include				"Singleton.hpp"
# include				"Entity.hpp"
# include				"Component.hh"

class					EntityManager : public Singleton<EntityManager>
{
  friend class Singleton<EntityManager>;

  typedef std::map<Entity *, Component *>	MapEntity;
  typedef std::pair<Entity *, Component *>	MapEntityPair;
  typedef MapEntity::iterator			MapEntityIT;

  typedef std::map<const char *, MapEntity>	MapComponentName;
  typedef std::pair<const char *, MapEntity>	MapComponentNamePair;
  typedef MapComponentName::iterator		MapComponentNameIT;

public:
  typedef std::vector<Entity *>			VectorEntity;
  typedef VectorEntity::iterator		VectorEntityIT;

public:
  Entity				&getNewEntity()
  {
    Entity				*e = new Entity(idCounter_++);
    return *e;
  }

  template				<typename T>
  T					&addComponent(Entity &entity)
  {
    const char				*componentName = typeid(T).name();
    T					*component = new T;

    listComponent_[componentName].insert(MapEntityPair(&entity, component));
    return (T &)(*component);
  }

  template				<typename T>
  T					&getComponent(Entity &entity)
  {
    return (T &)(*listComponent_[typeid(T).name()][&entity]);
  }

  template				<typename T>
  VectorEntity				*getAllEntitiesPosessingComponentOfClass(void)
  {
    const char				*componentName = typeid(T).name();
    MapComponentNameIT			c = listComponent_.find(componentName);

    if (c != listComponent_.end())
      {
	VectorEntity			*ret = new VectorEntity;
	MapEntityIT			actualEntity = (*c).second.begin();
	MapEntityIT			lastEntity =  (*c).second.end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    ret->push_back(actualEntity->first);
	  }
	return ret;
      }
    return NULL;
  }

private:
  EntityManager(void)
    : idCounter_(0)
  {}

  virtual ~EntityManager() {}
  EntityManager 			&operator=(const EntityManager &other);
  EntityManager(const EntityManager &other);

  int					idCounter_;
  MapComponentName			listComponent_;
};

#endif					/* !ENTITYMANAGER_HH_ */
