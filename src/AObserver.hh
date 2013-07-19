#ifndef				AOBSERVER_HH_
# define			AOBSERVER_HH_

# include			<allegro5/allegro.h>

class				AObserver
{
public:
  virtual ~AObserver() {}

  virtual void			notify(ALLEGRO_EVENT &event) = 0;

protected:
  AObserver() {}

private:
  AObserver 			&operator=(const AObserver &other);
  AObserver(const AObserver &other);
};

#endif				/* !AOBSERVER_HH_ */
