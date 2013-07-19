#include				"AResource.hh"
#include				"ResourceManager.hpp"

// CTOR - DTOR

AResource::AResource(const std::string &name)
  : name_(name),
    count_(0)
{
  ResourceManager::getInstance().add(name, this);
}

AResource::~AResource()
{
  ResourceManager::getInstance().remove(name_);
}

// PUBLIC METHODS

int				AResource::release()
{
  int				count = --count_;

  if (count <= 0)
    delete this;
  return count;
}
