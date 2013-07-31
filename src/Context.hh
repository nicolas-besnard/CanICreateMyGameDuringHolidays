#ifndef				CONTEXT_HH_
# define			CONTEXT_HH_

# include			<vector>
# include			<algorithm>

# include			<allegro5/allegro.h>
# include			<allegro5/allegro_image.h>
# include			<allegro5/allegro_primitives.h>

# include			"Singleton.hpp"
# include			"Exception.hh"

class				Context : public Singleton<Context>
{
  friend class			Singleton<Context>;

public:
  void				init(int width, int height);

protected:

private:
  Context();
  ~Context();
  Context 			&operator=(const Context &other);
  Context(const Context &other);
};

#endif				/* !CONTEXT_HH_ */
