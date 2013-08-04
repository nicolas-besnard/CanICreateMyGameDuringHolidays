#ifndef					INPUTMOVEMENTCOMPONENT_HPP_
# define				INPUTMOVEMENTCOMPONENT_HPP_

# include				"components/Base.hpp"

struct					InputMovement : public Component::Base
{
  int					keyUp;
  int					keyDown;
  int					keyLeft;
  int					keyRight;
  int					keyShoot;
  int					keyMissile;
  float					x;
  float					y;
};

#endif					/* !INPUTMOVEMENTCOMPONENT_HPP_ */
