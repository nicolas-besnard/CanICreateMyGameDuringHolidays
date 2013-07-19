#ifndef					SMARTPOINTERDEFAULTPOLICY_HH_
# define				SMARTPOINTERDEFAULTPOLICY_HH_

template <typename T>
struct					Policy
{
  T					*clone(T *);
  void					release(T *);
  void					swap(Policy &);
};

#endif					/* !SMARTPOINTERDEFAULTPOLICY_HH_ */
