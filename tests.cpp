#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sfba.h"

#include <vector>

static constexpr uint32_t heap_size = 32;
using elem_ty = int;


namespace
{
  // The fixture for testing class Foo.
  class SFBA_Test : public ::testing::Test
  {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    SFBA_Test() 
    {
      // You can do set-up work for each test here.
    }

    virtual ~SFBA_Test()
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


    sfba<elem_ty,heap_size> freeStore;

  };

  // ------------------------------------------------------------------------------
  // TESTS HERE
  //

  TEST_F(SFBA_Test, initialCondition)
  {
    ASSERT_EQ(heap_size, freeStore.size());
    ASSERT_EQ(heap_size, freeStore.capacity());
  }

  TEST_F(SFBA_Test, initialAllocation)
  {
    ASSERT_NE(nullptr, freeStore.malloc(1));
    ASSERT_EQ(heap_size-1, freeStore.capacity());
  }

  TEST_F(SFBA_Test, allocate2)
  {
    ASSERT_NE(nullptr, freeStore.malloc(2));
    ASSERT_EQ(heap_size-2, freeStore.capacity());
  }

  TEST_F(SFBA_Test, allocate4)
  {
    ASSERT_NE(nullptr, freeStore.malloc(4));
    ASSERT_EQ(heap_size-4, freeStore.capacity());
  }


  TEST_F(SFBA_Test, allocate8)
  {
    ASSERT_NE(nullptr, freeStore.malloc(8));
    ASSERT_EQ(heap_size-8, freeStore.capacity());
  }


  TEST_F(SFBA_Test, allocate16)
  {
    ASSERT_NE(nullptr, freeStore.malloc(16));
    ASSERT_EQ(heap_size-16, freeStore.capacity());
  }

  TEST_F(SFBA_Test, allocate32)
  {
    ASSERT_NE(nullptr, freeStore.malloc(32));
    ASSERT_EQ(heap_size-32, freeStore.capacity());
  }

  TEST_F(SFBA_Test, failToAllocate64)
  {
    ASSERT_EQ(nullptr, freeStore.malloc(64));
  }

  TEST_F(SFBA_Test, initialAllocationNum2x2)
  {
    ASSERT_NE(nullptr, freeStore.malloc(2));
    ASSERT_EQ(heap_size-2, freeStore.capacity());
    ASSERT_NE(nullptr, freeStore.malloc(2));
    ASSERT_EQ(heap_size-4, freeStore.capacity());
  }

  TEST_F(SFBA_Test, twoAllocationsAreNotEqual)
  {
    elem_ty* ptr1 = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr1);

    elem_ty* ptr2 = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr2);


    ASSERT_NE(ptr1, ptr2);
    ASSERT_EQ(heap_size-2, freeStore.capacity());
  }

  TEST_F(SFBA_Test, twoNumAllocationsAreNotEqual)
  {
    elem_ty* ptr1 = freeStore.malloc(2);
    ASSERT_NE(nullptr, ptr1);

    elem_ty* ptr2 = freeStore.malloc(2);
    ASSERT_NE(nullptr, ptr2);


    ASSERT_NE(ptr1, ptr2);
    ASSERT_EQ(heap_size-4, freeStore.capacity());
  }

  TEST_F(SFBA_Test, exhaustAllocation)
  {
    for(uint32_t counter = 0; counter < freeStore.size(); ++counter) {
      ASSERT_EQ(freeStore.size()-counter, freeStore.capacity());
      ASSERT_NE(nullptr, freeStore.malloc(1));
    }
    ASSERT_EQ(0, freeStore.capacity());
    ASSERT_EQ(nullptr, freeStore.malloc(1));
  }

  TEST_F(SFBA_Test, exhaustAllocationNum32)
  {
    ASSERT_NE(nullptr, freeStore.malloc(32));
    ASSERT_EQ(0, freeStore.capacity());
    ASSERT_EQ(nullptr, freeStore.malloc(1));
  }

  TEST_F(SFBA_Test, initialDeallocation)
  {
    elem_ty* ptr = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr);
    freeStore.free(ptr);
    ASSERT_EQ(heap_size, freeStore.capacity());
  }

  TEST_F(SFBA_Test, deallocate2)
  {
    elem_ty* ptr = freeStore.malloc(2);
    ASSERT_NE(nullptr, ptr);
    freeStore.free(ptr);
    ASSERT_EQ(heap_size, freeStore.capacity());
  }

  TEST_F(SFBA_Test, checkForOutOfOrderDealloc)
  {
    elem_ty* ptr1 = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr1);
    elem_ty* ptr2 = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr2);
    elem_ty* ptr3 = freeStore.malloc(1);
    ASSERT_NE(nullptr, ptr3);

    freeStore.free(ptr2);
    ASSERT_EQ(heap_size-2, freeStore.capacity());
  }

  TEST_F(SFBA_Test, checkForOutOfOrderDeallocMisc)
  {
    elem_ty* ptr1 = freeStore.malloc(2);
    ASSERT_NE(nullptr, ptr1);
    elem_ty* ptr2 = freeStore.malloc(4);
    ASSERT_NE(nullptr, ptr2);
    elem_ty* ptr3 = freeStore.malloc(8);
    ASSERT_NE(nullptr, ptr3);

    freeStore.free(ptr2);
    ASSERT_EQ(heap_size-10, freeStore.capacity());
  }

  TEST_F(SFBA_Test, shouldNotDealloc)
  {
    elem_ty* ptr = freeStore.malloc(1);
    elem_ty local{};
    freeStore.free(&local);
    ASSERT_EQ(heap_size-1, freeStore.capacity());
  }

  TEST_F(SFBA_Test, toEmptyAndBackToFull)
  {
    std::vector<elem_ty*> v;
    for(uint32_t counter = 0; counter < freeStore.size(); ++counter) {
      v.push_back(freeStore.malloc(1));
    }
    ASSERT_EQ(0, freeStore.capacity());

    int count{};
    for(auto ptr : v) {
      freeStore.free(ptr);
      ASSERT_EQ(++count, freeStore.capacity());
    }
  }
}  // namespace
