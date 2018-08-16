//
//  operator_acception.h
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


#ifndef operator_acception_h
#define operator_acception_h

#include "type_finder/includes/type_finder.h" 

namespace operator_acception { 


    // operator flag types
    namespace flag { 
      struct OR      {  };
      struct AND     {  };
      struct NOT     {  };
      struct XOR     {  };
      struct L_SHIFT {  };
      struct R_SHIFT {  };

      struct PLUS    {  };
      struct MINUS   {  };
      struct MULTPLY {  };
      struct DIVIDE  {  };
      
      struct INCL {  };
      struct DECL {  };

      struct ALL {  };
    }



  struct flagger_template {  

    private: 
      template < typename Target, typename... Args > 
        using finder = typename type_finder :: is_same_base < Target, Args... >;

      template < typename... Args > 
        using all_checker = finder < flag :: ALL, Args... >;

  
    protected: 
      template < typename Flag, typename... Args  >
        struct is_accept { 
          static constexpr bool value = all_checker< Args... > :: value || finder< Flag, Args... > :: value ;
        };
  };

  namespace bit {

    // bit operation flagger
    template < typename... Args > 
    struct flagger : public flagger_template {

        static constexpr bool 
            OR      = is_accept< flag :: OR,      Args... > :: value
          , AND     = is_accept< flag :: AND,     Args... > :: value 
          , NOT     = is_accept< flag :: NOT,     Args... > :: value 
          , XOR     = is_accept< flag :: XOR,     Args... > :: value 
          , L_SHIFT = is_accept< flag :: L_SHIFT, Args... > :: value 
          , R_SHIFT = is_accept< flag :: R_SHIFT, Args... > :: value ;
    };

    // specialization entry point for bit operation enablling
    template < typename T, typename U = T > 
    struct accepter { 
      using flagger = bit :: flagger<>;
    };

    //get <T, U> specialized or flag
    template < typename T, typename U = T > 
    struct is_or_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: OR;
    };

    //get <T, U> specialized and flag
    template < typename T, typename U = T > 
    struct is_and_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: AND; 
    };
    
   //get < T > specialized not flag
   template < typename T > 
    struct is_not_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: NOT; 
    };

    //get <T, U> specialized xor flag
    template < typename T, typename U = T >
    struct is_xor_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: XOR; 
    };

    //get < T > specialized l_shift flag
    template < typename T > 
    struct is_l_shift_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: L_SHIFT; 
    };

    //get < T > specialized r_shift flag
    template < typename T > 
    struct is_r_shift_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: R_SHIFT; 
    };


  }

  namespace logical { 

    // logical operation flagger
    template < typename... Args > 
    struct flagger : public flagger_template { 

      static constexpr bool 
          OR  = is_accept< flag :: OR,  Args... > :: value 
        , AND = is_accept< flag :: AND, Args... > :: value 
        , NOT = is_accept< flag :: NOT, Args... > :: value ;
    };

    //specialization entry point for logical operation enablling
    template < typename T, typename U = T > 
    struct accepter { 
      using flagger = logical :: flagger<>;
    };

    //get < T, U > specialized or flag
    template < typename T, typename U = T > 
    struct is_or_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: OR; 
    };

    //get < T, U > specialized and flag
    template < typename T, typename U = T > 
    struct is_and_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: AND; 
    };

    //get < T > specialized not flag
    template < typename T > 
    struct is_not_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: NOT; 
    };

  }

  namespace arithmetic { 

    //arithmetic operation flagger
    template < typename... Args > 
    struct flagger : public flagger_template { 
    
      static constexpr bool
          PLUS    = is_accept< flag :: PLUS,    Args... > :: value 
        , MINUS   = is_accept< flag :: MINUS,   Args... > :: value 
        , MULTPLY = is_accept< flag :: MULTPLY, Args... > :: value 
        , DIVIDE  = is_accept< flag :: DIVIDE,  Args... > :: value 
        , INCL    = is_accept< flag :: INCL,    Args... > :: value 
        , DECL    = is_accept< flag :: DECL,    Args... > :: value ;

    };

    // specialization entry point for arithmetic operation enabling
    template < typename T, typename U = T > 
    struct accepter { 
      using flagger = arithmetic :: flagger<>;
    };

    //get < T, U > specialized plus flag
    template < typename T, typename U = T > 
    struct is_plus_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: PLUS;
    };

    //get < T, U > specialized minus flag
    template < typename T, typename U = T > 
    struct is_minus_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: MINUS; 
    };

    //get < T, U > specialized multply flag
    template < typename T, typename U = T > 
    struct is_multply_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: MULTPLY; 
    };

    //get < T, U > specialized divide flag
    template < typename T, typename U = T > 
    struct is_divide_accepted { 
      static constexpr bool value = accepter< T, U > :: flagger :: DIVIDE; 
    };

    //get < T > specialized increment flag
    template < typename T > 
    struct is_incl_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: INCL; 
    };

    //get < T, U > specialized declement flag
    template < typename T > 
    struct is_decl_accepted { 
      static constexpr bool value = accepter< T > :: flagger :: DECL; 
    };

  }
}


#endif /* operator_acception_h */
