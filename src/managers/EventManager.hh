#ifndef					EVENTMANAGER_HH_
# define				EVENTMANAGER_HH_

# include				<allegro5/allegro.h>
# include				<iostream>

# include				"Singleton.hpp"
# include				"AObserver.hh"
# include				"OptionManager.hpp"
# include				"Context.hh"
# include				"SystemManager.hpp"

# include				"systems/ShipSystem.hpp"
# include				"systems/BoundingBoxSystem.hpp"
# include				"systems/AggroCircleSystem.hpp"
# include				"EntityFactory.hpp"

class					EventManager : public Singleton<EventManager>
{
  friend class Singleton<EventManager>;

  // typedef std::vector<AObserver *>		ObserverVector;
  // typedef ObserverVector::iterator		ObserverVectorIT;
  // typedef ObserverVector::const_iterator	ObserverVectorConstIT;

public:
  void					init(void);
  void					loop(void);
  // void					addEventListener(AObserver &observer)
protected:

private:
  EventManager(void);
  virtual ~EventManager();
  EventManager				&operator=(const EventManager &other);
  EventManager(const EventManager &other);

  // void					notifyNewEvent_(ALLEGRO_EVENT &event) const

  bool					isRunning_;
  bool					canDraw_;
  ALLEGRO_EVENT_QUEUE			*eventQueue_;
  ALLEGRO_TIMER				*timer_;
};

#endif					/* !EVENTMANAGER_HH_ */
