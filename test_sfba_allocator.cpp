#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sfba_Alloc.h"
#include "sfba.h"

#include <vector>
using namespace std;

static constexpr uint32_t heap_size = 16;
using elem_ty = int;

namespace
{
  // The fixture for testing class Foo.
  class SFBA_Alloc_Test : public ::testing::Test
  {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    SFBA_Alloc_Test() 
    {
      // You can do set-up work for each test here.
    }

    virtual ~SFBA_Alloc_Test()
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

    std::vector<int, SFBAllocator<int>> v;

  };

  // ------------------------------------------------------------------------------
  // TESTS HERE
  //

  TEST_F(SFBA_Alloc_Test, vectorInitialCondition)
  {
    ASSERT_EQ(0, v.size());
  }

  TEST_F(SFBA_Alloc_Test, vectorInitialAlloc)
  {
    v.push_back(int{});
    ASSERT_EQ(1, v.size());
  }

  TEST_F(SFBA_Alloc_Test, VectorInitialAllocValue)
  {
    v.push_back(int{42});
    ASSERT_EQ(42, v[0]);
    ASSERT_EQ(42, v.front());
  }

  TEST_F(SFBA_Alloc_Test, multiple_Alloc)
  {
    v.push_back(int{42});
    v.push_back(int{43});
    v.push_back(int{44});
    v.push_back(int{45});
    ASSERT_EQ(42, v[0]);
    ASSERT_EQ(43, v[1]);
    ASSERT_EQ(44, v[2]);
    ASSERT_EQ(45, v[3]);
    ASSERT_EQ(42, v.front());
    ASSERT_EQ(4, v.size());
  }
}
