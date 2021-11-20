
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~Iterator() specifiers
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  Iterator& operator=(const Iterator&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  Iterator& operator=(Iterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const Iterator&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const Iterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type operator*() specifiers; // (concrete function must throw std::out_of_range when terminated)
  virtual Data& operator*() const = 0;

  // type Terminated() specifiers; // (concrete function should not throw exceptions)
  virtual bool Terminated() const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{ // Must extend Iterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~ForwardIterator() specifiers
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  ForwardIterator& operator=(const ForwardIterator&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  ForwardIterator& operator=(ForwardIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const ForwardIterator&) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const ForwardIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type operator++() specifiers; // (concrete function must throw std::out_of_range when terminated)
  virtual void operator++() = 0;

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data>{ // Must extend Iterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~BackwardIterator() specifiers
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  BackwardIterator& operator=(const BackwardIterator&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  BackwardIterator& operator=(BackwardIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const BackwardIterator&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const BackwardIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type operator--() specifiers; // (concrete function must throw std::out_of_range when terminated)
  virtual Data& operator--() = 0;

};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator : virtual public ForwardIterator<Data>,
                              virtual public BackwardIterator<Data>{ // Must extend ForwardIterator and BackwardIterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~BidirectionalIterator() specifiers
  virtual ~BidirectionalIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  BidirectionalIterator& operator=(const BidirectionalIterator&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const BidirectionalIterator&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator!=(const BidirectionalIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Terminated() specifiers; // Override Iterator member
  inline bool Terminated() noexcept override{
    return(ForwardTerminated() && BackwardTerminated());
  }

  // type ForwardTerminated() specifiers; // (concrete function should not throw exceptions)
  virtual bool ForwardTerminated() noexcept = 0;

  // type BackwardTerminated() specifiers; // (concrete function should not throw exceptions)
  virtual bool BackwardTerminated() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
