#ifndef				CONTEXT_HH_
# define			CONTEXT_HH_

# include			<allegro5/allegro.h>
# include			<allegro5/allegro_image.h>
# include			<allegro5/allegro_primitives.h>

# include			"Singleton.hpp"
# include			"Exception.hh"
# include			"ALogger.hh"
# include			"LoggerConsole.hh"

class				Context : public Singleton<Context>
{
  friend class			Singleton<Context>;

public:
  void				init(int width, int height);
  void				loop();

protected:

private:
  Context();
  ~Context();
  Context 			&operator=(const Context &other);
  Context(const Context &other);

  ALLEGRO_EVENT_QUEUE		*eventQueue_;
  ALLEGRO_TIMER			*timer_;
  bool				isRunning_;
};

#endif				/* !CONTEXT_HH_ */
