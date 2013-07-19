#ifndef					RESOURCEMANAGER_HH_
# define				RESOURCEMANAGER_HH_

# include				<string>
# include				<map>

# include				"Singleton.hpp"
# include				"AResource.hh"
# include				"ALogger.hh"
# include				"Exception.hh"
# include				"MediaManager.hpp"


# include				<iostream> // DEBUG


class					ResourceManager : public Singleton<ResourceManager>
{
  friend class					Singleton<ResourceManager>;
  typedef std::map<std::string, AResource *>	ResourceMap;
  typedef ResourceMap::iterator			ResourceMapIT;
  typedef ResourceMap::const_iterator		ResourceMapConstIT;

public:
  template <class T>
  T					*get(const std::string &name) const
  {
    ResourceMapConstIT			it = this->list_.find(name);

    if (it != this->list_.end())
      {
	it->second->addRef();
	return static_cast<T *>(it->second);
      }
    MediaManager::getInstance().load<T>(name);
    return find_<T>(name);
  }

  void					add(const std::string &name, AResource *resource)
  {
    Assert(resource != NULL);
    if (list_.find(name) != list_.end())
      ALogger::log("%s already loaded.\n", name.c_str());
    list_[name] = resource;
    resource->setName(name);
  }

  void					remove(const std::string &name)
  {
    ResourceMapIT			resource = list_.find(name);

    if (resource == list_.end())
      {
	ALogger::log("%s delete but not loaded\n", name.c_str());
	return ;
      }
    list_.erase(resource);
  }


protected:

private:
  ResourceManager() {}
  ~ResourceManager()
  {
    if (!list_.empty())
      {
	ALogger::log("Resource not empty");
	for (ResourceMapConstIT actualResource = list_.begin(); actualResource != list_.end(); ++actualResource)
	  {
	    ALogger::log("%s\n", actualResource->second->getName().c_str());
	  }
      }
  }
  ResourceManager(const ResourceManager &other);
  ResourceManager			&operator=(const ResourceManager &other);

  template <typename T>
  inline T*				find_(const std::string &name) const
  {
    ResourceMapConstIT			it = list_.find(name);

    if (it != list_.end())
      return static_cast<T *>(it->second);
    throw LoadingFailed(name, "This file is not loaded and can not be found.");
    return NULL;
  }

  ResourceMap				list_;
};

#endif					/* !RESOURCEMANAGER_HH_ */
