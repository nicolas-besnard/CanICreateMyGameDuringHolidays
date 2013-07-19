#ifndef					SMARTPOINTER_HH_
# define				SMARTPOINTER_HH_

# include				<cstdlib>
# include				<algorithm>

# include				"SmartPointerPolicies.hpp"

template				<class T, template <class> class Ownership = ExternalRef>
class					SmartPointer : private Ownership<T>
{
public:
  SmartPointer()
    : data_(NULL)
  {}

  SmartPointer(const SmartPointer<T, Ownership> &other)
    : Ownership<T>(other),
      data_(this->clone(other.data_))
  {}

  SmartPointer(T *other)
    : data_(other)
  {}

  virtual ~SmartPointer()
  {
    Ownership<T>::release(data_);
  }

  T					&operator*()
  {
    Assert(data_ != NULL);
    return *data_;
  }

  T					*operator->()
  {
    Assert(data_ != NULL);
    return data_;
  }

  const SmartPointer<T, Ownership>	&operator=(SmartPointer<T, Ownership> &other)
  {
    SmartPointer<T, Ownership>(other).swap(*this);
    return *this;
  }

  const SmartPointer<T, Ownership>	&operator =(T *ptr)
  {
    if (this->data_ != ptr)
      {
	SmartPointer<T, Ownership>(ptr).swap(*this);
      }
    return *this;
  }

  operator				T*() const
  {
    return data_;
  }

protected:

private:
  void					swap_(SmartPointer<T, Ownership> &other)
  {
    Ownership<T>::swap(other);
    std::swap(data_, other.data_);
  }

  T				*data_;
};

template <typename T, template <class> class Ownership>
T					*&getPointer(SmartPointer<T, Ownership> &pointer)
{
  return pointer.data_;
}

#endif				/* !SMARTPOINTER_HH_ */
