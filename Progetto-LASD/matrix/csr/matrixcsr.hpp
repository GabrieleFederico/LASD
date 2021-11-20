
#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP

/* ************************************************************************** */

#include "../matrix.hpp"
#include <utility>
#include <iostream>
// #include "../../list/list.hpp"
#include "../../list/list.hpp"
// #include "../../vector/vector.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixCSR : virtual public Matrix<Data>,
                  virtual protected List<std::pair<Data, ulong>>{ // Must extend Matrix<Data>

private:

  // ...

protected:

  // using Matrix<Data>::???;
  using Matrix<Data>::rownum;
  using Matrix<Data>::colnum;
  using List<std::pair<Data, ulong>>::size;
  using typename List<std::pair<Data, ulong>>::Node;
  using List<std::pair<Data, ulong>>::head;
  Vector<Node**> Rows = Vector<Node**>(1);

  // ...

public:

  // Default constructor
  // MatrixCSR() specifiers;
  MatrixCSR();

  /* ************************************************************************ */

  // Specific constructors
  // MatrixCSR(argument) specifiers; // A matrix of some specified dimension
  MatrixCSR(const ulong, const ulong);

  /* ************************************************************************ */

  // Copy constructor
  // MatrixCSR(argument) specifiers;
  MatrixCSR(const MatrixCSR&);

  // Move constructor
  // MatrixCSR(argument) specifiers;
  MatrixCSR(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~MatrixCSR() specifiers;
  ~MatrixCSR() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  MatrixCSR& operator=(const MatrixCSR&);

  // Move assignment
  // type operator=(argument) specifiers;
  MatrixCSR& operator=(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const MatrixCSR&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const MatrixCSR&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  // type RowResize() specifiers; // Override Matrix member
  void RowResize(ulong) override;
  // type ColumnResize() specifiers; // Override Matrix member
  void ColumnResize(ulong) override;

  // type ExistsCell() specifiers; // Override Matrix member (should not throw exceptions)
  bool ExistsCell(const ulong, const ulong) const noexcept override;

  // type operator()() specifiers; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  Data& operator()(const ulong, const ulong) override;
  // type operator()() specifiers; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)
  const Data& operator()(const ulong, const ulong) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member
  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  using typename Matrix<Data>::MapFunctor;

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  void MapPreOrder(const MapFunctor, void*) override;
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  using typename Matrix<Data>::FoldFunctor;

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;


};

/* ************************************************************************** */

}

#include "matrixcsr.cpp"

#endif
