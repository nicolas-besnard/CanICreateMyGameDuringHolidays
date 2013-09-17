#ifndef					IMAGECOMPONENT_HPP_
# define				IMAGECOMPONENT_HPP_

# include				<string>

# include				<allegro5/allegro_image.h>

# include				"components/Base.hpp"

struct					Image : public Component::Base
{
  ALLEGRO_BITMAP			*image;
  float					radian;
};

#endif					/* !IMAGECOMPONENT_HPP_ */
