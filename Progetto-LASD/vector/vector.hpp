
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector :  virtual public LinearContainer<Data>,
                virtual public MappableContainer<Data>,
                virtual public FoldableContainer<Data>{ // Must extend LinearContainer<Data>, MappableContainer<Data>, and FoldableContainer<Data>

private:

protected:

  using LinearContainer<Data>::size;
  Data* Elems = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong); // A vector with a given initial dimension
  Vector(const LinearContainer<Data>&); // A vector obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  Vector& operator= (const Vector&);

  // Move assignment
  // type operator=(argument) specifiers;
  Vector& operator= (Vector&&);

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator== (const Vector&) const noexcept;
  
  // type operator!=(argument) specifiers;
  bool operator!= (const Vector&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type Resize(argument) specifiers; // Resize the vector to a given size
  void Resize(const ulong);

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member
  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Front() const override;
  
  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override;

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[] (const ulong) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  void MapPreOrder(const MapFunctor, void*) override;
  
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;
  
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
