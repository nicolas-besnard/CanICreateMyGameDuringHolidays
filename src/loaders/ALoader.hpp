#ifndef					ALOADER_HH_
# define				ALOADER_HH_

# include				<string>

# include				"Exception.hh"
# include				"File.hpp"

template <typename T>
class					ALoader
{
public:
  virtual ~ALoader() {}

  virtual T				*load(const File &filename)
  {
    throw LoadingFailed(filename.getFullName(), "Loader doesn't exist.");
  }

  virtual void				save(const T *, const std::string &filename)
  {
    throw LoadingFailed(filename, "Loader doesn't exist.");
  }

protected:
  ALoader() {}
};

#endif					/* !ALOADER_HH_ */
