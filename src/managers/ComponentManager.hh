#ifndef					COMPONENTMANAGER_HH_
# define				COMPONENTMANAGER_HH_

# include				<map>

# include				"Singleton.hpp"

class					ComponentManager : public Singleton<ComponentManager>
{
  friend class Singleton<ComponentManager>;

  typedef std::map<std::string, Component *>
public:
  template				<typename T>
  void					registerComponent(void)
  {

  }

protected:

private:
  ComponentManager(void);
  ~ComponentManager();
  ComponentManager 			&operator=(const ComponentManager &other);
  ComponentManager(const ComponentManager &other);


};

#endif					/* !COMPONENTMANAGER_HH_ */
