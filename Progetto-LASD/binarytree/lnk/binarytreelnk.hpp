
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data>{ // Must extend BinaryTree<Data>

private:

  // ...

protected:

  // using BinaryTree<Data>::???;
  using BinaryTree<Data>::size;


  struct NodeLnk : virtual public BinaryTree<Data>::Node{ // Must extend Node

  private:

  protected:

  public:

    Data info = Data {};
    NodeLnk* right = nullptr;
    NodeLnk* left = nullptr;


    NodeLnk() = default;

    NodeLnk(const Data&);

    NodeLnk(Data&&) noexcept;

    NodeLnk(const NodeLnk&);

    NodeLnk(NodeLnk&&) noexcept;
    
    ~NodeLnk();

    NodeLnk& operator=(const NodeLnk&);

    NodeLnk& operator=(NodeLnk&&) noexcept;

    bool operator==(const NodeLnk&) const noexcept;

    bool operator!=(const NodeLnk&) const noexcept;

    Data& Element() noexcept override;

    const Data& Element() const noexcept override;

    bool IsLeaf() const noexcept override;

    bool HasLeftChild() const noexcept override;

    bool HasRightChild() const noexcept override;

    NodeLnk& LeftChild() const override;

    NodeLnk& RightChild() const override;

  };

  NodeLnk* root = nullptr;

public:

  using typename BinaryTree<Data>::Node;

  // Default constructor
  // BinaryTreeLnk() specifiers;
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a LinearContainer
  BinaryTreeLnk(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BinaryTreeLnk(argument) specifiers;
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  // BinaryTreeLnk(argument) specifiers;
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BinaryTreeLnk() specifiers;
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>& tree);

  // Move assignment
  // type operator=(argument) specifiers;
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&& tree) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BinaryTreeLnk<Data>& tree) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BinaryTreeLnk<Data>& tree) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
  Node& Root() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member
  void Clear() override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
