#ifndef					ARESOURCE_HH_
# define				ARESOURCE_HH_

# include				<string>

class					AResource
{
  friend class				ResourceManager;

public:
  AResource(const std::string &name);
  virtual ~AResource() = 0;

  const std::string			&getName() const { return name_; }
  void					setName(const std::string &name) { name_ = name; }
  void					addRef() { ++count_; }
  int					release();

protected:

private:
  AResource				&operator=(const AResource &other);
  AResource(const AResource &other);

  std::string				name_;
  int					count_;
};

#endif					/* !ARESOURCE_HH_ */
