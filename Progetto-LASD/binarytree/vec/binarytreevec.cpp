
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& val){
    info = val;
}

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& val) noexcept{
    std::swap(val, info);
}

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& node){
    info = node.info;
    right = node.right;
    left = node.left;
    index = node.index;
}

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& node) noexcept{
    std::swap(info, node.info);
    std::swap(right, node.right);
    std::swap(left, node.left);
    std::swap(index, node.index);
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& node){
    NodeVec* temp = new NodeVec(node);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& node) noexcept{
    std::swap(info, node.info);
    std::swap(right, node.right);
    std::swap(left, node.left);
    std::swap(index, node.index);
    return *this;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator==(const NodeVec& node) const noexcept{
    return (info == node.info && right == node.right && left == node.left && index == node.index);
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator!=(const NodeVec& node) const noexcept{
    return !(*this == node);
}

template<typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return info;
}

template<typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return info;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
    return (!HasRightChild() && !HasLeftChild());
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (left != nullptr);
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return (right != nullptr);
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!HasLeftChild())
        throw std::out_of_range("Out of range");
    return *left;
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(!HasRightChild())
        throw std::out_of_range("Out of range");
    return *right;
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& container){
    size = container.Size();

    if(size > 0){
        vector = Vector<NodeVec>(size);
        for(ulong i = 0; i < size; i++){
            vector[i] = NodeVec(container[i]);
            vector[i].index = i;

            if(((i+1)*2-1) < size)
                vector[i].left = &vector[(i+1)*2-1];
                
            if(((i+1)*2) < size)
                vector[i].right = &vector[(i+1)*2];
        }
    }
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& tree){
    size = tree.size;
    if(size > 0)
        vector = tree.vector;
    
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& tree) noexcept{
    std::swap(size, tree.size);
    std::swap(vector, tree.vector);
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& tree){
    BinaryTreeVec<Data>* temp = new BinaryTreeVec<Data>(tree);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& tree) noexcept{
    std::swap(size, tree.size);
    std::swap(vector, tree.vector);

    return *this;
}

template<typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& tree) const noexcept{
    return (vector == tree.vector);

}

template<typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& tree) const noexcept{
    return !(*this == tree);
}

template<typename Data>
typename BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::Root() const {
    if(size == 0)
        throw std::length_error("Length error");

    return vector[0];
}

template<typename Data>
void BinaryTreeVec<Data>::Clear(){
    vector.Clear();
    size = 0;
}

template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* par) {
    for(ulong i = 0; i < size; i++)
        fun(vector[i].info, par);
}

template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
    for(ulong i = 0; i < size; i++)
        fun(vector[i].info, par, acc);
}

/* ************************************************************************** */

}
