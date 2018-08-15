
# operator_acception

provide bit/logical/arithmetic operator overload acceptor 

depends leico/type_finder





## description

### brief

There are 3 namespaces, similarly functions are definited.

* `operator_acception :: bit`
    * for bit operators
* `operator_acception :: logical`
    * for logical operators
* `operator_acception :: arithmetic`
    * for arithmetic operators




### `... :: accepter`

Each operation accepter contains `... :: flagger`.
Set flags to enable operators,

ex. enable `||` operators between type `A` and `B`

```cpp
template<>
operator_acception :: logical :: accepter< A, B >{
  using flagger = flagger<
    flag :: OR
  >;
};
```

ex. enable all arithmetic operators between type `C` and `C`

```cpp
template<>
operator_acception :: arithmetic :: accepter< C >{ 
  using flagger = flagger< 
    flag :: ALL 
  >;
};
```




### `is_xxx_accepted` 

get `... :: accepter :: flagger :: xxx `  value. 
use to condition enable functions


### `operator_acception :: flag`

Set `flagger` s flag


## example 

```cpp
#include <iostream>
#include <type_traits> 
#include "operator_acception.h"
#include "../../includes/bool_checker/includes/bool_checker.h"


// acception conditon definition below
// * enable between T and U operation
// * definited `T.get` member function
// * definited `U.get` member function
// * T could constructed `T.get` returned value
template < typename T, typename U, template < typename, typename > class Accepter >
using acception = std :: enable_if<
    bool_checker :: anded_t<
        Accepter< T, U >
      , decltype( std :: declval < T >().get(), std :: true_type() )
      , decltype( std :: declval < U >().get(), std :: true_type() )
      , std :: is_constructible< T, decltype( std :: declval < T >().get() ) >
    > :: value
  , std :: nullptr_t 
>;

// namespace shortcut
namespace op_a = operator_acception :: arithmetic; 

// T + U definited, Accepter = is_plus_accepted
template < 
typename T
, typename U = T
, typename acception< T, U, op_a :: is_plus_accepted > :: type = nullptr
>
static constexpr T operator+ ( T t, U u ){ 
  return T( t.get() + u.get() );
}

// T - U definited, Accepter = is_minus_accepted
template < 
typename T
, typename U = T
, typename acception< T, U, op_a :: is_minus_accepted > :: type = nullptr
>
static constexpr T operator- ( T t, U u ){ 
  return T( t.get() - u.get() );
}


// T * U definited, Accepter = is_multply_accepted
template < 
typename T
, typename U = T
, typename acception< T, U, op_a :: is_multply_accepted > :: type = nullptr
>
static constexpr T operator* ( T t, U u ){ 
  return T( t.get() * u.get() );
}


// T / U definited, Accepter = is_divide_accepted
template < 
typename T
, typename U = T
, typename acception< T, U, op_a :: is_divide_accepted > :: type = nullptr
>
static constexpr T operator/ ( T t, U u ){ 
  return T( t.get() / u.get() );
}


// Test case class A, B, C
class A { 

  int _value;

  public: 
  explicit A(const int value) : _value(value) {}

  const int get(void) const { return _value ; }
};


class B { 

  int _a;
  int _b;

  public:
  explicit B (const int a, const int b = 0  ) : _a(a), _b(b) {  }

  const int get ( void ) const { return _a; }
};



class C { 

  int  _value;
  bool _state;

  public: 
  explicit C ( const int value, const bool state = false ) : 
    _value( value ), _state( state )
  {  }

  const int get ( void ) const { return _value; }
};


//shortcut for accepter
using op_a :: accepter;

//definited acception specialization 
// A and B enabled A + B, A - B
template < > 
struct accepter< A, B > { using flagger = flagger< flag :: PLUS, flag :: MINUS >; };

// A and A enabled A + A, A - B, A * B, A / B
template < > 
struct accepter< A >    { using flagger = flagger< flag :: ALL >; };

// A and C enabled A * C
template < >
struct accepter< A, C > { using flagger = flagger< flag :: MULTPLY >; };


//print function
template < typename T > 
void print(const T& t ){
  std :: cout << t.get() << std :: endl;
}


int main(int argc, const char * argv[]) {

  A a( 100 );
  B b( 10 );
  C c( -100 );

  print( a + a );
  print( a - a );
  print( a * a );
  print( a / a );
  
  print( a + b );
  print( a - b );
//  print( a * b ); //error
//  print( a / b ); //error

//  print( a + c ); //error
//  print( a - c ); //error
  print( a * c );
//  print( a / c ); //error

  return 0;
}
```




