#ifndef					AGGROCIRCLECOMPONENT_HPP_
# define				AGGROCIRCLECOMPONENT_HPP_

# include				"components/Base.hpp"

struct					AggroCircle : public Component::Base
{
  int					radius;
  int					entitySize;
};

#endif					/* !AGGROCIRCLECOMPONENT_HPP_ */
