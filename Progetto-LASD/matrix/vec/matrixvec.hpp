
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

// #include "../../vector/vector.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixVec : virtual public Matrix<Data>,
                  virtual protected Vector<Data>{ // Must extend Matrix<Data>

private:

  // ...

protected:

  // using Matrix<Data>::???;
  using Matrix<Data>::rownum;
  using Matrix<Data>::colnum;
  using Vector<Data>::size;
  using Vector<Data>::Elems;

  // ...

public:

  // Default constructor
  // MatrixVec() specifiers;
  MatrixVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // MatrixVec(argument) specifiers; // A matrix of some specified dimension
  MatrixVec(const ulong, const ulong);

  /* ************************************************************************ */

  // Copy constructor
  // MatrixVec(argument) specifiers;
  MatrixVec(const MatrixVec&);

  // Move constructor
  // MatrixVec(argument) specifiers;
  MatrixVec(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~MatrixVec() specifiers;
  ~MatrixVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  MatrixVec& operator=(const MatrixVec&);

  // Move assignment
  // type operator=(argument) specifiers;
  MatrixVec& operator=(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const MatrixVec&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const MatrixVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  // type RowResize() specifiers; // Override Matrix member
  void RowResize(const ulong) override;
  // type ColumnResize() specifiers; // Override Matrix member
  void ColumnResize(const ulong) override;

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

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  using Vector<Data>::MapPreOrder;
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member
  using Vector<Data>::MapPostOrder;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  using Vector<Data>::FoldPreOrder;
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member
  using Vector<Data>::FoldPostOrder;

};

/* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif
