#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MyAlloc.h"
#include "allocator.h"

#include <list>
#include <vector>
using namespace std;

namespace
{
  // The fixture for testing class Foo.
  class Alloc_Test : public ::testing::Test
  {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    Alloc_Test() 
    {
      // You can do set-up work for each test here.
    }

    virtual ~Alloc_Test()
    {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp()
    {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    virtual void TearDown()
    {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    //std::list<int, MyAlloc<int>> v;
    //std::list<int, Allocator<int>> v;
    std::vector<int, Allocator<int>> v;
        // an int/float map with special allocator
    // std::map<int,float,std::less<int>,
    //          MyAlloc<std::pair<const int,float>>> m;
  };

  // ------------------------------------------------------------------------------
  // TESTS HERE
  //

  TEST_F(Alloc_Test, vectorInitialCondition)
  {
    ASSERT_EQ(0, v.size());
  }

  TEST_F(Alloc_Test, vectorInitialAlloc)
  {
    v.push_back(int{});
    ASSERT_EQ(1, v.size());
  }

  TEST_F(Alloc_Test, VectorInitialAllocValue)
  {
    v.push_back(int{42});    
    v.push_back(int{42});    
    v.push_back(int{42});
    v.push_back(int{42});    
    v.push_back(int{42});    
    v.push_back(int{42});
    ASSERT_EQ(42, v.front());
  }
}
