
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
                 protected List<Data>{ // Must extend Stack<Data> and List<Data>

private:

  // ...

protected:

  // using List<Data>::???;
  using List<Data>::size;
  using typename List<Data>::Node;
  using List<Data>::head;

  // ...

public:

  // Default constructor
  // StackLst() specifier;
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  // StackLst(argument) specifiers; // A stack obtained from a LinearContainer
  StackLst(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // StackLst(argument);
  StackLst(const StackLst&);

  // Move constructor
  // StackLst(argument);
  StackLst(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~StackLst() specifier;
  ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument);
  StackLst& operator=(const StackLst&);

  // Move assignment
  // type operator=(argument);
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const StackLst&) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // type Push(argument) specifiers; // Override Stack member (copy of the value)
  void Push(const Data&) override;

  // type Push(argument) specifiers; // Override Stack member (move of the value)
  void Push(Data&&) noexcept override;

  // type Top() specifiers; // Override Stack member (must throw std::length_error when empty)
  Data& Top() override;

  // type Pop() specifiers; // Override Stack member (must throw std::length_error when empty)
  void Pop() override;

  // type TopNPop() specifiers; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member
  void Clear() override;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
