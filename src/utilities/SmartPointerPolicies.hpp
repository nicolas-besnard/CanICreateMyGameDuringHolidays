#ifndef					SMARTPOINTERPOLICIES_HH_
# define				SMARTPOINTERPOLICIES_HH_

template <typename T>
class					ExternalRef
{
public:
  ExternalRef()
    : counter_(new int(1))
  {}

  T					*clone(T *ptr)
  {
    ++(*this->counter_);
    return ptr;
  }

  void					release(T *ptr)
  {
    if (--(this->counter_) == 0)
      {
	delete this->counter_;
	delete ptr;
      }
  }

  void					swap(ExternalRef &plc)
  {
    std::swap(plc.counter_, this->counter_);
  }

  int					getCounter() const
  {
    return *this->counter_;
  }

private:
  int					*counter_;
};

template <typename T>
class					InternalRef
{
 public:
  static T				*clone(T *ptr)
  {
    if (ptr)
      ptr->addRef();
    return ptr;
  }

  static void				release(T *ptr)
  {
    if (ptr)
      ptr->release();
  }

  static void				swap(InternalRef &)
  {}

  int					getCounter() const
  {
    return *this->counter_;
  }
private:
  int					*counter_;
};

#endif					/* !SMARTPOINTERPOLICIES_HH_ */
