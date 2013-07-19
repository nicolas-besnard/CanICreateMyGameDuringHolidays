#ifndef				OPTIONMANAGER_HPP_
# define			OPTIONMANAGER_HPP_

# include			<map>
# include			<string>

# include			"Singleton.hpp"

// Generic class

class				Option
{
public:
  Option()
  {}
  virtual ~Option()
  {}

};

template			<typename T>
class				OptionValue : public Option
{
public:
  // ATTRIBUTS
private:
  T				value_;

  // CTOR - DTOR
public:
  OptionValue<T>(T value)
    : value_(value)
  {}
  virtual ~OptionValue<T>()
  {}
  OptionValue<T>(OptionValue const &);

  // OPERATOR
public:
  OptionValue &			operator=(OptionValue const &);

  // SETTER
public:
  void				set(T const &value) { this->value_ = value; }

  // GETTER
public:
  T const			&get(void) const { return this->value_; }
};


class				OptionManager : public Singleton<OptionManager>
{
  friend class			Singleton<OptionManager>;
  typedef std::map<std::string, Option *>	OptionMap;
  typedef OptionMap::iterator			OptionMapIT;
  typedef OptionMap::const_iterator		OptionMapConstIT;
  typedef std::pair<std::string, Option *>	optionPair;

public:
  ~OptionManager()
  {
    OptionMapIT			optionActual = this->collection_.begin();
    OptionMapIT			optionEnd = this->collection_.end();

    for (; optionActual != optionEnd; ++optionActual)
      {
	delete optionActual->second;
      }
    this->collection_.clear();
  }

  template <typename T>
  void				add(std::string const &key, T const &value)
  {
    OptionMapIT			option;

    if ((option = this->collection_.find(key)) != this->collection_.end())
      {
	(dynamic_cast<OptionValue<T> *>(option->second))->set(value);
      }
    else
      {
	this->create_(key, value);
      }
  }

  template <typename T>
  T					get(std::string const &key, T &value) const
  {
    OptionMapConstIT			option;

    if ((option = this->collection_.find(key)) != this->collection_.end())
      {
	value = (dynamic_cast<OptionValue<T> *>(option->second))->get();
      }
    return value;
  }

  template <typename T>
  OptionValue<T>			*get(std::string const &key) const
  {
    OptionMapConstIT			option;

    if ((option = this->collection_.find(key)) != this->collection_.end())
      {
	return (dynamic_cast<OptionValue<T> *>(option->second));
      }
    return NULL;
  }

private:
  OptionManager(void) {}
  OptionManager(OptionManager const &);
  OptionManager &			operator=(OptionManager const &);
  template <typename T>
  void				create_(std::string const &key, T const &value)
  {
    Option				*tmp = new OptionValue<T>(value);
    this->collection_.insert(optionPair(key, tmp));
  }

  OptionMap			collection_;

};

#endif				/* !OPTIONMANAGER_HPP_ */
