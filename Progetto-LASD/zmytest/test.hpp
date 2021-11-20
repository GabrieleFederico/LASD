
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../container/container.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

#include "../stack/vec/stackvec.hpp"

#include "../stack/lst/stacklst.hpp"

#include "../queue/vec/queuevec.hpp"

#include "../queue/lst/queuelst.hpp"

#include "../binarytree/vec/binarytreevec.hpp"

#include "../binarytree/lnk/binarytreelnk.hpp"

#include "../bst/bst.hpp"

#include "../matrix/vec/matrixvec.hpp"

#include "../matrix/csr/matrixcsr.hpp"

/* ************************************************************************** */
using namespace lasd;

void myTest();

void structureChoice();

void dataChoiceVector();

Vector<int> intVector(const ulong);

Vector<double> doubleVector(const ulong);

Vector<std::string> stringVector(const ulong);

template<typename Data>
void vectorTestChoice(Vector<Data>);

void dataChoiceList();

template<typename Data>
void listTestChoice(List<Data>);

template<typename Data>
void printPreOrder(MappableContainer<Data>&);

template<typename Data>
void printPostOrder(MappableContainer<Data>&);

template<typename Data>
void mapPrint(Data&, void*);

void specificTestFold(FoldableContainer<int>&);

void specificTestFold(FoldableContainer<double>&);

void specificTestFold(FoldableContainer<std::string>&);

void sumInt(const int&, const void*, void*);

void productDouble(const double&, const void*, void*);

void concatString(const std::string&, const void*, void*);

void specificTestMap(MappableContainer<int>&);

void specificTestMap(MappableContainer<double>&);

void specificTestMap(MappableContainer<std::string>&);

void intTimesPar(int&, void*);

void doublePowerOfPar(double&, void*);

void stringUppercase(std::string&, void*);

void structureTypeChoiceStack();

void structureTypeChoiceQueue();

void dataChoiceStackVec(const ulong);

void dataChoiceStackLst(const ulong);

void dataChoiceQueueVec(const ulong);

void dataChoiceQueueLst(const ulong);

template<typename Data>
void stackTestChoice(Stack<Data>&);

template<typename Data>
void queueTestChoice(Queue<Data>&);

void structureTypeChoiceBT();

void dataChoiceBTVec(const ulong);

void dataChoiceBTLnk(const ulong);

template<typename Data>
void btTestChoice(BinaryTree<Data>&);

template<typename Data>
void nodeNavigation(BinaryTree<Data>&);

template <typename Data>
void printBT(BinaryTree<Data>& tree);

void specificTestFold(BinaryTree<int>&);

void specificTestFold(BinaryTree<double>&);

void specificTestFold(BinaryTree<std::string>&);

void specificTestMap(BinaryTree<int>&);

void specificTestMap(BinaryTree<double>&);

void specificTestMap(BinaryTree<std::string>&);

void productInt(const int&, const void*, void*);

void sumDouble(const double&, const void*, void*);

void stringHeadConcat(std::string&, void*);

template<typename Data>
void iteratorChoice(BinaryTree<Data>&);

template<typename Data>
void iteratorVisit(ForwardIterator<Data>&);

void dataChoiceBST(const ulong);

template<typename Data>
void bstTestChoice(BST<Data>&);

template<typename Data>
void bstMaxMin(BST<Data>&);

template<typename Data>
void bstPredSucc(BST<Data>&);

void structureTypeChoiceMatrix();

void dataChoiceMatrixVec(const ulong, const ulong);

void dataChoiceMatrixCSR(const ulong, const ulong);

template<typename Data>
void matrixTestChoice(Matrix<Data>&);

MatrixVec<int> intMatrixVec(const ulong, const ulong, const ulong);

MatrixVec<double> doubleMatrixVec(const ulong, const ulong, const ulong);

MatrixVec<std::string> stringMatrixVec(const ulong, const ulong, const ulong);

MatrixCSR<int> intMatrixCSR(const ulong, const ulong, const ulong);

MatrixCSR<double> doubleMatrixCSR(const ulong, const ulong, const ulong);

MatrixCSR<std::string> stringMatrixCSR(const ulong, const ulong, const ulong);

/* ************************************************************************** */

#endif
