#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sfba_Alloc.h"

#include <list>
#include <vector>
using namespace std;

namespace
{
  // The fixture for testing class Foo.
  class List_Alloc_Test : public ::testing::Test
  {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    List_Alloc_Test() 
    {
      // You can do set-up work for each test here.
    }

    virtual ~List_Alloc_Test()
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

    std::list<int, SFBAllocator<int>> v;
  };

  // ------------------------------------------------------------------------------
  // TESTS HERE
  //

  TEST_F(List_Alloc_Test, initialCondition)
  {
    ASSERT_EQ(0, v.size());
  }

  TEST_F(List_Alloc_Test, initialAlloc)
  {
    v.push_back(int{});
    ASSERT_EQ(1, v.size());
  }

  TEST_F(List_Alloc_Test, listRange)
  {
    v.push_back(int{42});    
    v.push_back(int{43});    
    v.push_back(int{44});
    v.push_back(int{45});    
    v.push_back(int{46});    
    v.push_back(int{47});
    unsigned val{42};
    for(auto i : v) {
      ASSERT_EQ(val++,i);
    }
  }

  TEST_F(List_Alloc_Test, listPopAll)
  {
    v.push_back(int{42});    
    v.push_back(int{43});    
    v.push_back(int{44});
    v.push_back(int{45});    
    v.push_back(int{46});    
    v.push_back(int{47});

    ASSERT_EQ(42, v.front());
    v.pop_front();
    ASSERT_EQ(43, v.front());
    v.pop_front();
    ASSERT_EQ(44, v.front());
    v.pop_front();
    ASSERT_EQ(45, v.front());    
    v.pop_front();
    ASSERT_EQ(46, v.front());
    v.pop_front();
    ASSERT_EQ(47, v.front());
    v.pop_front();
    ASSERT_EQ(true, v.empty());
  }

  TEST_F(List_Alloc_Test, throwBadAlloc)
  {
    for(unsigned cnt = 0; cnt < 32; ++cnt) {
          v.push_back(int{});
    }
    ASSERT_THROW(v.push_back(int{}), std::bad_alloc);
  }
}
