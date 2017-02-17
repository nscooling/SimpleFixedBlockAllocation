#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "allocator.h"

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

  };

  // ------------------------------------------------------------------------------
  // TESTS HERE
  //

  TEST_F(Alloc_Test, initialCondition)
  {
    std:vector<int, Allocator<int>> v;
    ASSERT_EQ(0, v.size());
  }

  TEST_F(Alloc_Test, initialAlloc)
  {
    std:vector<int, Allocator<int>> v;
    v.push_back(1);
    ASSERT_EQ(1, v.size());
  }

  TEST_F(Alloc_Test, initialAllocValue)
  {
    std:vector<int, Allocator<int>> v;
    v.push_back(42);
    ASSERT_EQ(42, v[0]);
    ASSERT_EQ(42, v.at(0));
  }
}
