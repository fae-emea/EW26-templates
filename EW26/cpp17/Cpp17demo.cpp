/*
 * Copyright 2022-2026 IAR Systems AB.
 *
 * Cpp17demo.cpp
 *
 */

#include <bitset>
#include <iomanip>
#include <iostream>
#include <typeinfo>
#include <vector>

template<class A, class B>
auto add(A a, B b) -> decltype(a + b)
{
    return a + b;
}

//!< --- Use case: deprecated function
[[deprecated("use newFoo() instead")]]
void oldFoo(void) { };

void main()
{
  //!< --- Call to deprecated function
  oldFoo(); //Compiler Warning[Pe1444]: function "oldFoo" was declared deprecated ("use newFoo() instead")

  //!< --- Use case with automatic type inference
  std::cout << '\n';
  std::cout << "### Use case: type inference" << std::endl;
  {
    auto a = 2 + 4;
    auto b = add(3, 5.2f);
    std::cout << "Type of `a` is: " << typeid(a).name() << '\n';
    std::cout << "type of `b` is: " << typeid(b).name() << '\n';
  }
  std::cout << '\n';

  //!< --- Use case: dec/hex/oct/bin literals - all equals to 2^21
  std::cout << "### Use case: dec/hex/oct/bin literals w/ digit separators" << std::endl;
  {
    auto dec_val=2'097'152;
    auto hex_val=0x20'0000;
    auto oct_val=010'000'000;
    auto bin_val=0b0010'0000'0000'0000'0000'0000;
    std::cout << "dec_val = " << std::dec << std::setw(24) << dec_val << '\n';
    std::cout << "hex_val = " << std::hex << std::setw(24) << hex_val << '\n';
    std::cout << "oct_val = " << std::oct << std::setw(24) << oct_val << '\n';
    std::cout << "bin_val = " << std::bitset<24>(bin_val)   << std::endl;
    if ((dec_val & hex_val & oct_val & bin_val) == (1u << 21)) {
      std::cout << "Result  = All values equal to 2^21" << std::endl;
    }
  }
  std::cout << '\n';

  //!< --- Use case: generic lambdas
  std::cout << "### Use case: generic lambdas" << std::endl;
  {
    auto some_lambda = [](const auto& y, auto &x) {
      const std::type_info& ty = typeid(y);
      const std::type_info& tx = typeid(x);
      std::cout << "Data types: ";
      std::cout << "(`y`->" << ty.name() << ",`x`->" << tx.name() << ") => " << "(y - x)=";
      if (*tx.name() == 'f' || *ty.name() == 'f') std::cout << std::fixed;
      std::cout << (y - x) << std::endl;
    };
    {
      auto y = 8, x = 3;
      some_lambda(y, x); // y - x = 5
    }
    {
      auto y = 8.354531f, x = 3.019600f;
      some_lambda(y, x); // y - x = 5.334931
    }
    {
      auto y = 8.354531f; auto x = 3;
      some_lambda(y, x); // y - x = 5.354531
    }
    {
      auto y = 8; auto x = 3.019600f;
      some_lambda(y, x); // y - x = 4.980400
    }
  }
  std::cout << '\n';

  //!< --- Use case: range based for-loop + case ranges
  std::cout << "### Use case: range based for-loops + case ranges" << std::endl;
  {
    auto some_func = [numbers = std::vector<int>{0,1,2,3,4,5,6,7}]() {
      for (auto n : numbers) {
        switch (n) {
        case 0:
          std::cout << "n < 4 => ( ";
        case 1 ... 3:
          std::cout << n;
          break;
        case 4:
          std::cout << ") ::: n > 3 => ( ";
        case 5 ... 7:
          std::cout << n;
        default:
          break;
        }
        std::cout << ' ';
      }
      std::cout << ")\n";
    };
    some_func();
  }
}
