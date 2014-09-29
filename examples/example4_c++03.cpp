// C++03 - use assertions, observe reports with expression left and right side expanded.

#include "lest_cpp03.hpp"

using namespace lest;

char a() { return 'a'; }
char b() { return 'b'; }

int  x() { return 3; }
int  y() { return 7; }

double pi() { return 3.14; }
double  e() { return 2.72; }

bool t() { return true; }
bool f() { return false; }

void * ptr() { return 0; }

class C {};

std::string std_hello( "hello" );
std::string std_world( "world" );

char const* hello = "hello";
char const* world = "world";

#define CASE( name ) lest_CASE( specification, name )

test_specification specification;

CASE( "character" )
{
    EXPECT( a() < b() );
    EXPECT( b() < a() );
}

CASE( "integral" )
{
    EXPECT(  x() != y() );
    EXPECT(  x() == y() );
}

CASE( "real" )
{
    EXPECT(  pi() != e() );
    EXPECT(  pi() != pi() );
}

CASE( "mixed real, integral" )
{
    EXPECT(  pi() != x() );
    EXPECT(  pi() == x() );
}

CASE( "mixed integral, real" )
{
    EXPECT(  x() != pi() );
    EXPECT(  x() == pi() );
}

CASE( "boolean")
{
    EXPECT(  t() == t() );
    EXPECT(  t() == f() );
}

CASE( "pointer")
{
#if __cplusplus >= 201103L
    EXPECT(  ptr() == nullptr );
    EXPECT(  ptr() != nullptr );
#else
    EXPECT(  ptr() == (void*)NULL );
    EXPECT(  ptr() != (void*)NULL );
#endif
}

CASE( "class object pointer" )
{
    C a; C b;
    EXPECT(  &a == &a );
    EXPECT(  &a == &b );
}

CASE( "std::string" )
{
    EXPECT( std_world > std_hello );
    EXPECT( std_world < std_hello );
}

CASE( "C-string" )
{
    EXPECT( world > std_hello );
    EXPECT( world < std_hello );
}

CASE( "single evaluation" )
{
    int n = 0;
    EXPECT( 1 == ++n );
}

CASE( "duplicate evaluation" )
{
    int n = 0;
    EXPECT( 2 == ++n );
}

int main( int argc, char * argv[] )
{
    return lest::run( specification, argc, argv );
}

// cl -nologo -W3 -EHsc -I.. example4_c++03.cpp && example4_c++03
// cl -nologo -Wall -EHsc -I.. example4_c++03.cpp && example4_c++03
// g++ -Wall -Wextra -std=c++11 -I.. -o example4_c++03.exe example4_c++03.cpp && example4_c++03
// g++ -Wall -Wextra -std=c++03 -I.. -o example4_c++03.exe example4_c++03.cpp && example4_c++03

// example4_c++03.cpp:36: failed: character: b() < a() for 'b' < 'a'
// example4_c++03.cpp:42: failed: integral: x() == y() for 3 == 7
// example4_c++03.cpp:48: failed: real: pi() != pi() for 3.14 != 3.14
// example4_c++03.cpp:54: failed: mixed real, integral: pi() == x() for 3.14 == 3
// example4_c++03.cpp:60: failed: mixed integral, real: x() == pi() for 3 == 3.14
// example4_c++03.cpp:66: failed: boolean: t() == f() for true == false
// example4_c++03.cpp:76: failed: pointer: ptr() != (void*)NULL for 0 != 0
// example4_c++03.cpp:84: failed: class object pointer: &a == &b for 0x28fc27 == 0x28fc26
// example4_c++03.cpp:90: failed: std::string: std_world < std_hello for "world" < "hello"
// example4_c++03.cpp:96: failed: C-string: world < std_hello for "world" < "hello"
// example4_c++03.cpp:108: failed: duplicate evaluation: 2 == ++n for 2 == 1
// 11 out of 12 selected tests failed.
