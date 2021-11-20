
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data>{ // Must extend BinaryTreeLnk<Data>

private:

  // ...

protected:

  // using BinaryTreeLnk<Data>::???;

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  using typename BinaryTreeLnk<Data>::NodeLnk;

  // Default constructor
  // BST() specifiers;
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  // BST(argument) specifiers; // A bst obtained from a LinearContainer
  BST(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BST(argument) specifiers;
  BST(const BST&);

  // Move constructor
  // BST(argument) specifiers;
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BST() specifiers;
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BST& operator=(const BST&);

  // Move assignment
  // type operator=(argument) specifiers;
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BST&) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type Insert(argument) specifiers; // Copy of the value
  void Insert(const Data&);
  // type Insert(argument) specifiers; // Move of the value
  void Insert(Data&&) noexcept;
  // type Remove(argument) specifiers;
  void Remove(const Data&);

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Min() const;
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  Data MinNRemove();
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
  void RemoveMin();

  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Max() const;
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove();
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
  void RemoveMax();

  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Predecessor(const Data&) const;
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&);
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&);
  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Successor(const Data&) const;
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&);
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data&) const noexcept override;

protected:

  // Auxiliary member functions

  // type DataNDelete(argument) specifiers;
  Data DataNDelete(NodeLnk*);

  // type Detach(argument) specifiers;
  NodeLnk* Detach(NodeLnk*&) noexcept;

  // type DetachMin(argument) specifiers;
  NodeLnk* DetachMin(NodeLnk*&) noexcept;
  // type DetachMax(argument) specifiers;
  NodeLnk* DetachMax(NodeLnk*&) noexcept;

  // type SkipOnLeft(argument) specifiers;
  NodeLnk* SkipOnLeft(NodeLnk*&) noexcept;
  // type SkipOnRight(argument) specifiers;
  NodeLnk* SkipOnRight(NodeLnk*&) noexcept;

  // type FindPointerToMin(argument) specifiers;
  NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;
  NodeLnk* const& FindPointerToMin(NodeLnk* const&) const noexcept;
  // type FindPointerToMax(argument) specifiers;
  NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;
  NodeLnk* const& FindPointerToMax(NodeLnk* const&) const noexcept;

  // type FindPointerTo(argument) specifiers;
  NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const& FindPointerTo(NodeLnk* const&, const Data&) const noexcept;

  // type FindPointerToPredecessor(argument) specifiers;
  NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const* FindPointerToPredecessor(NodeLnk* const&, const Data&) const noexcept;
  // type FindPointerToSuccessor(argument) specifiers;
  NodeLnk** FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const* FindPointerToSuccessor(NodeLnk* const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
