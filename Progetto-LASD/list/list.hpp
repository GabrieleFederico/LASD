
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public LinearContainer<Data>,
             virtual public MappableContainer<Data>,
             virtual public FoldableContainer<Data>{ // Must extend LinearContainer<Data>, MappableContainer<Data>, and FoldableContainer<Data>

private:

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    // Data
    Data data = Data {};
    Node* next = nullptr;

    /* ********************************************************************** */

    Node() = default;

    // Specific constructors
    Node(const Data&);
    Node(Data&&) noexcept;
    Node(const Data&, const Node*);


    /* ********************************************************************** */

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node();

    /* ********************************************************************** */

    Node& operator= (const Node&);
    Node& operator= (Node&&) noexcept;

    // Comparison operators
    inline bool operator== (const Node&) const noexcept;
    inline bool operator!= (const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    typedef std::function<void(Data&, void*) noexcept> MapFunctor;
    void AuxMapPostOrder(const MapFunctor, void*);

    typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;
    void AuxFoldPostOrder(const FoldFunctor, const void*, void *) const;

  };

  struct Node* head = nullptr;

  // ...

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a LinearContainer
  List(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // List(argument) specifiers;
  List(const List&);

  // Move constructor
  // List(argument) specifiers;
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~List() specifiers;
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  List& operator= (const List&);

  // Move assignment
  // type operator=(argument) specifiers;
  List& operator= (List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator== (const List&) const noexcept;

  // type operator!=(argument) specifiers;
  inline bool operator!= (const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type InsertAtFront(argument) specifier; // Copy of the value
  void InsertAtFront(const Data&);

  // type InsertAtFront(argument) specifier; // Move of the value
  void InsertAtFront(Data&&) noexcept;

  // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
  void RemoveFromFront();

  // type FrontNRemove() specifier; // (must throw std::length_error when empty)
  Data FrontNRemove();

  // type InsertAtBack(argument) specifier; // Copy of the value
  void InsertAtBack(const Data&);

  // type InsertAtBack(argument) specifier; // Move of the value
  void InsertAtBack(Data&&) noexcept;

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

protected:

  // Auxiliary member functions (for MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  void MapPreOrder(const MapFunctor, void*, const ulong);

  // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  void MapPostOrder(const MapFunctor, void*, const ulong);

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  void FoldPreOrder(const FoldFunctor, const void*, void*, const ulong) const;

  // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(const FoldFunctor, const void*, void*, const ulong) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
