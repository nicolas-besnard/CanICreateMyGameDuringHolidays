#ifndef					SYSTEM_HPP_
# define				SYSTEM_HPP_

# include				<allegro5/allegro.h>

struct					System
{
  virtual void				update(const ALLEGRO_EVENT &event) = 0;
  virtual void				init(void) = 0;
};

#endif					/* !SYSTEM_HPP_ */
