// static_assert.hpp --- Unboost static_assert
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_STATIC_ASSERT_HPP_
#define UNBOOST_STATIC_ASSERT_HPP_

#include "unboost.h"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_STATIC_ASSERT) + defined(UNBOOST_USE_UNBOOST_STATIC_ASSERT) + defined(UNBOOST_USE_BOOST_STATIC_ASSERT)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_STATIC_ASSERT
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_STATIC_ASSERT
    #else
        #ifdef UNBOOST_CXX11   // C++11
            #define UNBOOST_USE_CXX11_STATIC_ASSERT
        #elif (defined(_MSC_VER) && _MSC_VER >= 1600)
            #ifndef UNBOOST_NO_CXX11
                #define UNBOOST_USE_CXX11_STATIC_ASSERT
            #else
                #define UNBOOST_USE_UNBOOST_STATIC_ASSERT
            #endif
        #else
            #define UNBOOST_USE_UNBOOST_STATIC_ASSERT
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_STATIC_ASSERT
    // static_assert is available
    #define UNBOOST_STATIC_ASSERT_MSG static_assert
#elif defined(UNBOOST_USE_BOOST_STATIC_ASSERT)
    #include <boost/static_assert.hpp>
    #define UNBOOST_STATIC_ASSERT_MSG BOOST_STATIC_ASSERT_MSG
#else
    #define UNBOOST_STATIC_ASSERT_MSG(x,y) \
        typedef char UNBOOST_STATIC_ASSERTION##__LINE__[(x) ? 1 : -1]
#endif

#if 0
    #undef UNBOOST_STATIC_ASSERT_MSG
    #define UNBOOST_STATIC_ASSERT_MSG(x,y) \
        typedef char UNBOOST_STATIC_ASSERTION##__LINE__[1]
#endif

#endif  // ndef UNBOOST_STATIC_ASSERT_HPP_
