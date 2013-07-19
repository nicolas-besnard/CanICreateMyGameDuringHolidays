#ifndef				CONTEXT_HH_
# define			CONTEXT_HH_

# include			<vector>
# include			<algorithm>

# include			<allegro5/allegro.h>
# include			<allegro5/allegro_image.h>
# include			<allegro5/allegro_primitives.h>

# include			"Singleton.hpp"
# include			"Exception.hh"
# include			"ALogger.hh"
# include			"LoggerConsole.hh"
# include			"AObserver.hh"
# include			"OptionManager.hpp"

class				Context : public Singleton<Context>
{
  friend class			Singleton<Context>;
  typedef std::vector<AObserver *>		ObserverVector;
  typedef ObserverVector::iterator		ObserverVectorIT;
  typedef ObserverVector::const_iterator	ObserverVectorConstIT;

public:
  void				init(int width, int height);
  void				loop();
  void				addEventListener(AObserver &observer);

protected:

private:
  Context();
  ~Context();
  Context 			&operator=(const Context &other);
  Context(const Context &other);

  void				notifyNewEvent(ALLEGRO_EVENT &event) const;

  ALLEGRO_EVENT_QUEUE		*eventQueue_;
  ALLEGRO_TIMER			*timer_;
  OptionValue<bool>		*isRunning_;
  OptionValue<bool>		*canDraw_;
  ObserverVector		eventListener_;
};

#endif				/* !CONTEXT_HH_ */
