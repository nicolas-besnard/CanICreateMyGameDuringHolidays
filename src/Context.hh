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
# include			"AEntity.hpp"

class				Context : public Singleton<Context>
{
  friend class			Singleton<Context>;

public:
  typedef std::vector<AObserver *>		ObserverVector;
  typedef ObserverVector::iterator		ObserverVectorIT;
  typedef ObserverVector::const_iterator	ObserverVectorConstIT;

  typedef std::vector<AEntity *>		EntityVector;
  typedef EntityVector::iterator		EntityVectorIT;
  typedef EntityVector::const_iterator		EntityVectorConstIT;

public:
  void				init(int width, int height);
  void				loop();
  void				addEventListener(AObserver &observer);
  void				addEntity(AEntity &entity);
  void				removeEntity(AEntity &entity);
  void				drawEntity() const;
  void				updateEntity() const;
  const EntityVector		&getEntities() const { return entityCollection_; }
protected:

private:
  Context();
  ~Context();
  Context 			&operator=(const Context &other);
  Context(const Context &other);

  void				notifyNewEvent_(ALLEGRO_EVENT &event) const;

  ALLEGRO_EVENT_QUEUE		*eventQueue_;
  ALLEGRO_TIMER			*timer_;
  OptionValue<bool>		*isRunning_;
  OptionValue<bool>		*canDraw_;
  ObserverVector		eventListener_;
  EntityVector			entityCollection_;
};

#endif				/* !CONTEXT_HH_ */
