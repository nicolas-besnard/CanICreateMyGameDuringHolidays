#ifndef					MEDIAMANAGER_HH_
# define				MEDIAMANAGER_HH_

# include				<string>
# include				<set>
# include				<vector>

# include				"TypeList.hpp"
# include				"GenHierarchies.hpp"
# include				"SmartPointer.hpp"
# include				"ALoader.hpp"
# include				"File.hpp"
# include				"Image.hh"
# include				"string.hpp"


#include			<iostream> // D E B U G


typedef	TYPELIST_1(Image)		MediaList;

template <class T>
struct					MediaHolder
{
  typedef std::map<std::string, SmartPointer<ALoader<T> > > LoaderMap;
  LoaderMap				loaders;
};

class					MediaManager :
  public Singleton<MediaManager>,
  public CScatteredHierarchy<MediaList, MediaHolder>
{
  friend class				Singleton<MediaManager>;
  typedef std::set<std::string>		StringSet;
  typedef StringSet::const_iterator	StringSetConstIT;
  typedef StringSet::iterator		StringSetIT;

public:
  template <typename T>
  void					load(const File &file) const
  {
    File				path;

    path = findMedia_(file);
    findLoader_<T>(path).load(path.getFullName());
  }

  void					addSearchPath(const std::string &path)
  {
    if (path.empty() || (*path.rbegin() == '\\' || (*path.rbegin() == '/')))
      paths_.insert(path);
    else
      paths_.insert(path + "\\");
  }

  void					clearSearchPath()
  {
    this->paths_.clear();
  }

  template <typename T>
  inline void				registerLoader(ALoader<T> *loader, const std::string &extensions)
  {
    std::vector<std::string>		ext;
    SmartPointer<ALoader<T> >		ptr;
    std::vector<std::string>::iterator	it;

    split(extensions, ext, " /\\*.,;|-_\t\n'\"");

    ptr = loader;
    it = ext.begin();
    while (it != ext.end())
      {
	MediaHolder<T>::loaders[(*it)] = ptr;
	std::cout << "Register loader for '" << (*it) << "'" << std::endl;
	++it;
      }
  }

  template <typename T>
  void					save(const T *object, const File &file) const
  {
    findLoader_<T>(file).save(object, file.getFullName());
  }

  // template <typename T>
  // T					*loadMediaFromFile(const File &filename)
  // {
  //   for (StringSetConstIT actualString = paths_.begin(); actualString != paths_.end(); ++actualString)
  //     {
  // 	File				tmpFile = *actualString + filename.getFullName();

  // 	if (tmpFile.exists())
  // 	  return tmpFile;
  //     }
  //   throw LoadingFailed(filename.getFullName(), "Can't found file.");
  // }

private:
  MediaManager() { paths_.insert(""); }

  ~MediaManager() {}
  MediaManager(const MediaManager &other);
  MediaManager				&operator=(const MediaManager &other);

  File					findMedia_(const File &file) const
  {
    StringSetConstIT			it = paths_.begin();

    while (it != paths_.end())
      {
	File				f = (*it) + file.getFileName();

	if (f.exists())
	  return f;
	++it;
      }
    throw LoadingFailed(file.getFullName(), "File cannot be found.");
  }

  template <typename T>
  inline ALoader<T>			&findLoader_(const File &file) const
  {
    typename MediaHolder<T>::LoaderMap::const_iterator it;

    it = MediaHolder<T>::loaders.find(file.getExtension());
    std::cout << "Looking for loader for : '" << file.getExtension() << "'" << std::endl;
    if (it != MediaHolder<T>::loaders.end() && it->second)
      {
	return *(it->second);
      }
    throw LoadingFailed(file.getFullName(), "No loader handle this type of file.");
  }

  StringSet				paths_;
};

#endif					/* !MEDIAMANAGER_HH_ */
