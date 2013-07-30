#ifndef				EVENTMANAGER_HH_
# define			EVENTMANAGER_HH_

# include			<allegro5/allegro.h>

#include			<iostream>

# include			"Singleton.hpp"
# include			"AObserver.hh"
# include			"OptionManager.hpp"
# include			"Context.hh"

class				EventManager :
  public Singleton<EventManager>,
  public AObserver
{
public:
  EventManager(void);
  virtual ~EventManager();

  virtual void			notify(ALLEGRO_EVENT &event);
protected:

private:
  EventManager 			&operator=(const EventManager &other);
  EventManager(const EventManager &other);
};

#endif				/* !EVENTMANAGER_HH_ */
