#ifndef					IMAGECOMPONENT_HPP_
# define				IMAGECOMPONENT_HPP_

# include				<string>

# include				<allegro5/allegro_image.h>

# include				"components/Base.hpp"

struct					Image : public Component::Base
{
  bool					isInit;
  std::string				url;
  ALLEGRO_BITMAP			*image;
};

#endif					/* !IMAGECOMPONENT_HPP_ */
