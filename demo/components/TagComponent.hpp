#ifndef					TAGCOMPONENT_HPP_
# define				TAGCOMPONENT_HPP_

# include				<string>

# include				"components/Base.hpp"

struct					Tag : public Component::Base
{
  std::string				name;
};

#endif					/* !TAGCOMPONENT_HPP_ */
