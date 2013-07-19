#ifndef				SINGLETON_H_
# define			SINGLETON_H_

# include			<cstdlib>

template <typename T>
class				Singleton
{
public:
  static T			&getInstance()
  {
    if (!that_)
      that_ = new T;
    return *that_;
  }

  static void			destroy()
  {
    if (that_)
      {
	delete that_;
	that_ = NULL;
      }
  }
protected:
  Singleton() {}
  ~Singleton() {}

private:
  Singleton 			&operator=(const Singleton &other);
  Singleton(const Singleton &other);

  static T			*that_;
};

template <typename T>
T				*Singleton<T>::that_ = NULL;

#endif				/* !SINGLETON_H_ */
