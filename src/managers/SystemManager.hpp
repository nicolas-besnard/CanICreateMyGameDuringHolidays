#ifndef					SYSTEMMANAGER_HPP_
# define				SYSTEMMANAGER_HPP_

# include				<typeinfo>
# include				<map>
# include				<allegro5/allegro.h>

# include				"Singleton.hpp"
# include				"systems/Base.hpp"

class					SystemManager : public Singleton<SystemManager>
{
  friend class Singleton<SystemManager>;
  typedef std::map<const char *, System::Base *>	MapSystem;
  typedef MapSystem::iterator				MapSystemIT;
  typedef MapSystem::const_iterator			MapSystemConstIT;
  typedef std::pair<const char *, System::Base *>	MapSystemPair;

  typedef std::multimap<int, System::Base *, std::greater<int> >	MapSystemDraw;
  typedef MapSystemDraw::const_iterator			MapSystemDrawConstIT;
  typedef std::pair<int, System::Base *>		MapSystemDrawPair;

public:
  template				<typename T>
  void					addSystem(int priority = 0, bool haveToDraw = false)
  {
    const char				*systemName = typeid(T).name();
    MapSystemIT				find = systems_.find(systemName);

    if (find == systems_.end())
      {
	T				*system = new T;

	systems_.insert(MapSystemPair(systemName, system));
	if (haveToDraw)
	  {
	    std::cout << "add" << std::endl;
	    systemsWhoDraw_.insert(MapSystemDrawPair(priority, system));
	  }
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

  void					draw(void) const
  {
    MapSystemDrawConstIT		actualSystem = systemsWhoDraw_.begin();
    MapSystemDrawConstIT		lastSystem = systemsWhoDraw_.end();

    for (; actualSystem != lastSystem; ++actualSystem)
      {
	(*actualSystem).second->draw();
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
  MapSystemDraw				systemsWhoDraw_;
};

#endif					/* !SYSTEMMANAGER_HPP_ */
