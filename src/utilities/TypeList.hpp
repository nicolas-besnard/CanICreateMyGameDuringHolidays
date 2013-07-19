#ifndef					TYPELIST_HH_
# define				TYPELIST_HH_

template <class T1, class T2>
struct TypeList
{
  typedef T1 Head;
  typedef T2 Tail;
};

struct NullType {};

#define TYPELIST_1(t1)                                 TypeList<t1, NullType>
#define TYPELIST_2(t1, t2)                             TypeList<t1, TYPELIST_1(t2) >
#define TYPELIST_3(t1, t2, t3)                         TypeList<t1, TYPELIST_2(t2, t3) >
#define TYPELIST_4(t1, t2, t3, t4)                     TypeList<t1, TYPELIST_3(t2, t3, t4) >
#define TYPELIST_5(t1, t2, t3, t4, t5)                 TypeList<t1, TYPELIST_4(t2, t3, t4, t5) >
#define TYPELIST_6(t1, t2, t3, t4, t5, t6)             TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6) >
#define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7)         TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7) >
#define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8)     TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8) >
#define TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) TypeList<t1, TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9) >

// Recherche le N-ième élément d'une typelist
// template <std::size_t N, class List>
// struct NthElement
// {
//   typedef typename NthElement<N - 1, typename List::Tail>::Result Result;
// };

// template <class List>
// struct NthElement<0, List>
// {

//   typedef typename List::Head Result;

// };

// Détermine de la taille d'une typelist
// template <class List>
// struct Size
// {
//   enum {Result = Size<typename List::Tail>::Result + 1};
// };

// template <>
// struct Size<NullType>
// {
//   enum {Result = 0};
// };

// Recherche la position d'un élément dans une typelist
// template <class ToFind, class ToCompare, class List>

// struct Find_
// {
//   enum {Result = Find<ToFind, List>::Result + 1};
// };

// template <class ToFind, class List>
// struct Find_<ToFind, ToFind, List>
// {
//   enum {Result = 0};
// };

// template <class ToFind, class List>
// struct Find
// {
//   enum {Result = Find_<ToFind, typename List::Head, typename List::Tail>::Result};
// };


// Ajoute un élément à la fin d'une typelist
// template <class T, class List>
// struct PushBack
// {
//   typedef TypeList<typename List::Head, typename PushBack<T, typename List::Tail>::Result> Result;
// };

// template <class T>
// struct PushBack<T, NullType>
// {
//   typedef TypeList<T, NullType> Result;
// };

// Ajoute d'un élément au début d'une typelist
// template <class T, class List>
// struct PushFront
// {
//   typedef TypeList<T, List> Result;
// }

// Concatène 2 typelists
// template <class List1, class List2>
// struct Concat
// {
//   typedef typename Concat<typename PushBack<typename List2::Head, List1>::Result, typename List2::Tail>::Result Result;
// };

// template <class List1>
// struct Concat<List1, NullType>
// {
//   typedef List1 Result;
// };

#endif					/* !TYPELIST_HH_ */
