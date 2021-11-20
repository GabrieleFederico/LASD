
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& val){
    info = val;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& val) noexcept{
    std::swap(val, info);
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& node){
    left = node.left;
    right = node.right;
    info = node.info;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& node) noexcept{
    std::swap(info, node.info);
    std::swap(right, node.right);
    std::swap(left, node.left);
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete left;
    delete right;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& node){
    NodeLnk* temp = new NodeLnk(node);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept{
    std::swap(info, node.info);
    std::swap(right, node.right);
    std::swap(left, node.left);
    return *this;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk& node) const noexcept{
    return(info == node.info && right == node.right && left == node.left);
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk& node) const noexcept{
    return !(*this == node);
}

template<typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
    return info;
}

template<typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept{
    return info;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept{

    return (left == nullptr && right == nullptr);
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{

    return (left != nullptr);
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (right != nullptr);
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(!HasLeftChild())
        throw std::out_of_range("Out of range");

    return *left;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(!HasRightChild())
        throw std::out_of_range("Out of range");

    return *right;
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& container){
    size = container.Size();

    if(size > 0){
        root = new NodeLnk(container[0]);

        QueueLst<NodeLnk*> queue {};
        queue.Enqueue(root);

        NodeLnk* curr = root;

        for(ulong i = 1; i < container.Size(); i++){
            if(!curr->HasLeftChild()){
                curr->left = new NodeLnk(container[i]);
                queue.Enqueue(curr->left);
            }
            else{
                curr->right = new NodeLnk(container[i]);
                queue.Enqueue(curr->right);

                queue.Dequeue();
                curr = queue.Head();
            }
        }
    }
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& tree){
    size = tree.size;

    if(size > 0){
        root = new NodeLnk(tree.root->info);
        BTBreadthIterator<Data> iterator = BTBreadthIterator<Data>(tree);

        QueueLst<NodeLnk*> queue {};
        queue.Enqueue(root);

        NodeLnk* curr = root;

        ++iterator;
        while(!iterator.Terminated()){
            if(!curr->HasLeftChild()){
                curr->left = new NodeLnk(*iterator);
                queue.Enqueue(curr->left);
                ++iterator;
            }
            else{
                curr->right = new NodeLnk(*iterator);
                queue.Enqueue(curr->right);

                queue.Dequeue();
                curr = queue.Head();
                ++iterator;
            }
        }

    }
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& tree) noexcept{
    std::swap(root, tree.root);
    std::swap(size, tree.size);
}

template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    delete root;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& tree){
    BinaryTreeLnk<Data>* temp = new BinaryTreeLnk<Data>(tree);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& tree) noexcept{
    std::swap(root, tree.root);
    std::swap(size, tree.size);
    return *this;
}

template<typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& tree) const noexcept{
    return BinaryTree<Data>::operator==(tree);
}

template<typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& tree) const noexcept{
    return BinaryTree<Data>::operator!=(tree);
}

template<typename Data>
typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const {
    if(root == nullptr)
        throw std::length_error("Length error");

    return *root;
}

template<typename Data>
void BinaryTreeLnk<Data>::Clear(){
    delete root;
    root = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
