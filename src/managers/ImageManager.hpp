#ifndef					IMAGEMANAGER_HPP_
# define				IMAGEMANAGER_HPP_

# include				<string>
# include				<map>
# include				<allegro5/allegro.h>

# include				"Singleton.hpp"
# include				"utilities/File.hpp"

class					ImageManager : public Singleton<ImageManager>
{
  friend class Singleton<ImageManager>;

  typedef std::map<std::string, ALLEGRO_BITMAP *>	ImageMap;
  typedef std::pair<std::string, ALLEGRO_BITMAP *>	ImageMapPair;
  typedef ImageMap::iterator				ImageMapIT;
  typedef ImageMap::const_iterator			ImageMapConstIT;

public:
  void					addImage(const std::string &name, const std::string &path)
  {
    ImageMapIT				find = images_.find(name);

    // Name doesn't exist
    if (find == images_.end())
      {
	File				file(path);

	if (file.exists())
	  {
	    std::cout << "Load of " << path << std::endl;
	    ALLEGRO_BITMAP		*image = al_load_bitmap(path.c_str());

	    if (image)
	      {
		images_.insert(ImageMapPair(name, image));
	      }
	    else
	      {
		std::cout << "File failed to be loaded" << std::endl;
	      }
	  }
	else
	  {
	    std::cout << "File doesn't exist" << std::endl;
	  }
      }
    else
      {
	std::cout << "File already in loaded" << std::endl;
      }
  }

  ALLEGRO_BITMAP			*getImage(const std::string &name)
  {
    ImageMapIT				find = images_.find(name);

    if (find != images_.end())
      {
	return (*find).second;
      }
    return NULL;
  }

protected:

private:
  ImageManager(void)
  {}

  virtual ~ImageManager()
  {}

  ImageManager					&operator=(const ImageManager &other);
  ImageManager(const ImageManager &other);

  ImageMap				images_;
};


#endif					/* !IMAGEMANAGER_HPP_ */
