//
//  main.cpp
//
// MIT License
// 
// Copyright (c) 2018 leico
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


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





