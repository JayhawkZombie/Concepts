#include <iostream>

#include "Concepts/Concepts.hpp"

struct copy_const_able
{
  copy_const_able() { }
  copy_const_able(const copy_const_able &) noexcept { }
  copy_const_able(copy_const_able &&) noexcept { }
  copy_const_able& operator =(const copy_const_able&) noexcept { return *this; }
  copy_const_able& operator =(copy_const_able &&) noexcept { return *this; }
};

struct invocable_type
{
  void operator ()() { return; }
};

struct predicate_type
{
  bool operator()() { return true; }
};

struct predicate_type_with_args
{
  bool operator()(int, int) { return true; }
};

static_assert(CopyConstructable<copy_const_able>, "");
static_assert(Invocable<invocable_type>, "");
static_assert(Predicate<predicate_type>, "");
static_assert(Predicate<predicate_type_with_args, int, int>, "");

int main()
{
  return 0;
}