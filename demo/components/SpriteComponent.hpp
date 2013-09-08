#ifndef					SPRITECOMPONENT_HPP_
# define				SPRITECOMPONENT_HPP_

# include				<string>

# include				<allegro5/allegro_image.h>

# include				"components/Base.hpp"

struct					Sprite : public Component::Base
{
  bool					isInit;
  std::string				url;
  ALLEGRO_BITMAP			*image;
  int					columnNumber;
  int					partWidth;
  int					partHeight;
  int					from;
  int					stepNumber;
  int					currentStep;
  int					speed;
  int					timeCounter;
};

#endif					/* !SPRITECOMPONENT_HPP_ */
