#ifndef					BASESYSTEM_HPP_
# define				BASESYSTEM_HPP_

# include				<allegro5/allegro.h>

namespace				System
{
  struct				Base
  {
    virtual void			init(void) = 0;
    virtual void			update(double dt, const ALLEGRO_EVENT &event) = 0;
    virtual void			draw() const = 0;
  };
}

#endif					/* !BASESYSTEM_HPP_ */
