#ifndef				COMPONENTMANAGER_HH_
# define			COMPONENTMANAGER_HH_

# include			"Singleton.hpp"

class				ComponentManager : public Singleton<ComponentManager>
{
  friend class Singleton<ComponentManager>;

public:
  ComponentManager(void);
  ~ComponentManager();

protected:

private:
  ComponentManager 			&operator=(const ComponentManager &other);
  ComponentManager(const ComponentManager &other);
};

#endif				/* !COMPONENTMANAGER_HH_ */
