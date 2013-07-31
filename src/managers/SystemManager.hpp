#ifndef					SYSTEMMANAGER_HPP_
# define				SYSTEMMANAGER_HPP_

# include				<typeinfo>
# include				<allegro5/allegro.h>

# include				"Singleton.hpp"
# include				"systems/System.hpp"

class					SystemManager : public Singleton<SystemManager>
{
  friend class Singleton<SystemManager>;
  typedef std::map<const char *, System *>	MapSystem;
  typedef MapSystem::iterator			MapSystemIT;
  typedef std::pair<const char *, System *>	MapSystemPair;

public:
  template				<typename T>
  void					addSystem(void)
  {
    const char				*systemName = typeid(T).name();
    MapSystemIT				find = systems_.find(systemName);

    if (find == systems_.end())
      {
	T				*system = new T;
	systems_.insert(MapSystemPair(systemName, system));
	system->init();
      }
  }

  template				<typename T>
  T					*getSystem(void)
  {
    const char				*systemName = typeid(T).name();
    MapSystemIT				find = systems_.find(systemName);

    if (find != systems_.end())
      {
	return (T *)((*find).second);
      }
    return NULL;
  }

  void					update(const ALLEGRO_EVENT &event)
  {
    MapSystemIT				actualSystem = systems_.begin();
    MapSystemIT				lastSystem = systems_.end();

    for (; actualSystem != lastSystem; ++actualSystem)
      {
	(*actualSystem).second->update(event);
      }
  }

protected:

private:
  SystemManager(void)
  {}
  virtual ~SystemManager()
  {}
  SystemManager				&operator=(const SystemManager &other);
  SystemManager(const SystemManager &other);

  MapSystem				systems_;
};

#endif					/* !SYSTEMMANAGER_HPP_ */
