#ifndef					ENTITY_HPP_
# define				ENTITY_HPP_

# include				"Component.hh"

class					Entity
{
  typedef std::vector<Component *>	ComponentVector;
  typedef ComponentVector::iterator	ComponentVectorIT;
  typedef ComponentVector::const_iterator	ComponentVectorConstIT;

public:
  Entity(unsigned int id)
    : id_(id)
  {}
  ~Entity() {}

  void					addComponent(Component &component)
  {
    componentCollection_.push_back(&component);
  }

protected:

private:
  Entity				&operator=(const Entity &other);
  Entity(const Entity &other);

  ComponentVector			componentCollection_;
  unsigned int				id_;
};

#endif					/* !ENTITY_HPP_ */
