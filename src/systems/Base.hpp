#ifndef					BASESYSTEM_HPP_
# define				BASESYSTEM_HPP_

# include				<allegro5/allegro.h>

namespace				System
{
  struct				Base
  {
    virtual void			init(void) = 0;
    virtual void			update(const ALLEGRO_EVENT &event) = 0;
  };
}

#endif					/* !BASESYSTEM_HPP_ */
