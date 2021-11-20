
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

protected:

  ulong size = 0;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  virtual Container& operator= (const Container&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  virtual Container& operator= (Container&&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const Container&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const Container&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Empty() specifiers; // (concrete function should not throw exceptions)
  virtual inline bool Empty() const noexcept{
    return (Container::size == 0);
  } 

  // type Size() specifiers; // (concrete function should not throw exceptions)
  virtual inline ulong Size() const noexcept{
    return Container::size;
  }

  // type Clear() specifiers;
  virtual void Clear() = 0;

};

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public Container{ // Must extend Container

private:

protected:

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  LinearContainer& operator= (const LinearContainer&) = delete; 

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  LinearContainer& operator= (LinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const LinearContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const LinearContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Front() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data& Front() const = 0;

  // type Back() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data& Back() const = 0;

  // type operator[](argument) specifiers; // (concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[] (ulong idx) const = 0;

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container{ // Must extend Container

private:

protected:

public:

  // Destructor
  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  TestableContainer& operator= (const TestableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  TestableContainer& operator= (TestableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const TestableContainer&) const noexcept= delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const TestableContainer&) const noexcept= delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Exists(argument) specifiers; // (concrete function should not throw exceptions)
  virtual bool Exists(const Data&) const noexcept = 0; 

};

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public Container{ // Must extend Container

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  MappableContainer& operator= (const MappableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  MappableContainer& operator= (MappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const MappableContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const MappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void MapPreOrder(const MapFunctor, void*) = 0;
  virtual void MapPostOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer : virtual public TestableContainer<Data>{ // Must extend TestableContainer

private:

protected:

public:

  // Destructor
  virtual ~FoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  FoldableContainer& operator= (const FoldableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  FoldableContainer& operator= (FoldableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const FoldableContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const FoldableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;

  virtual void FoldPreOrder(const FoldFunctor, const void*, void*) const = 0;
  
  virtual void FoldPostOrder(const FoldFunctor, const void*, void*) const = 0;

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer : virtual public MappableContainer<Data>{ // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~InOrderMappableContainer() specifiers
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const InOrderMappableContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // using typename MappableContainer<Data>::MapFunctor;
  using typename MappableContainer<Data>::MapFunctor;

  // type MapInOrder(arguments) specifiers;
  virtual void MapInOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer : virtual public FoldableContainer<Data>{ // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~InOrderFoldableContainer() specifiers
  virtual ~InOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  InOrderFoldableContainer& operator=(const InOrderFoldableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  InOrderFoldableContainer& operator=(InOrderFoldableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const InOrderFoldableContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderFoldableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // using typename MappableContainer<Data>::MapFunctor;
  using typename FoldableContainer<Data>::FoldFunctor;

  // type FoldInOrder(arguments) specifiers;
  virtual void FoldInOrder(const FoldFunctor, const void*, void*) const = 0;

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer : virtual public MappableContainer<Data>{ // Must extend MappableContainer

private:

protected:

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  BreadthMappableContainer& operator= (const BreadthMappableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  BreadthMappableContainer& operator= (BreadthMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const BreadthMappableContainer&) const noexcept = delete;
  
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const BreadthMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapBreadth(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer : virtual public FoldableContainer<Data>{ // Must extend FoldableContainer

private:

protected:

public:

  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  BreadthFoldableContainer& operator= (const BreadthFoldableContainer&) = delete;


  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  BreadthFoldableContainer& operator= (BreadthFoldableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator== (const BreadthFoldableContainer&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!= (const BreadthFoldableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldBreadth(const FoldFunctor, const void*, void*) const = 0;

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
