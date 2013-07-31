#ifndef					BOUNDINGBOXCOMPONENT_HPP_
# define				BOUNDINGBOXCOMPONENT_HPP_

# include				"components/Base.hpp"

struct					BoundingBox : public Component::Base
{
  int					sizeX;
  int					sizeY;
};

#endif					/* !BOUNDINGBOXCOMPONENT_HPP_ */
