
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
                 virtual protected Vector<Data> { // Must extend Queue<Data> and Vector<Data>

private:

  // ...

protected:

  // using Vector<Data>::???;
  using Vector<Data>::size;
  using Vector<Data>::Elems;
  ulong head = 0;
  ulong tail = 0;

  // ...

public:

  // Default constructor
  // QueueVec() specifier;
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  // QueueVec(argument) specifiers; // A queue obtained from a LinearContainer
  QueueVec(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // QueueVec(argument);
  QueueVec(const QueueVec&);

  // Move constructor
  // QueueVec(argument);
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~QueueVec() specifier;
  ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument);
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  // type operator=(argument);
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const QueueVec&) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  // type Enqueue(argument) specifiers; // Override Queue member (copy of the value)
  void Enqueue(const Data&) override;

  // type Enqueue(argument) specifiers; // Override Queue member (move of the value)
  void Enqueue(Data&&) noexcept override;

  // type Head() specifiers; // Override Queue member (must throw std::length_error when empty)
  Data& Head() override;

  // type Dequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override;

  // type HeadNDequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Empty() specifiers; // Override Container member
  bool Empty() const noexcept override;

  // type Size() specifiers; // Override Container member
  ulong Size() const noexcept override;

  // type Clear() specifiers; // Override Container member
  void Clear() override;

protected:

  // Auxiliary member functions

  // type Expand() specifiers;
  void Expand();

  // type Reduce() specifiers;
  void Reduce();

  // type SwapVectors(arguments) specifiers;
  void SwapVectors();

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
