
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& container){
    for(ulong i = 0; i < container.Size(); i++)
        Insert(container[i]);
}

template<typename Data>
BST<Data>::BST(const BST<Data>& tree){
    BTBreadthIterator<Data> iterator(tree);
    while(!iterator.Terminated()){
        Insert(*iterator);
        ++iterator;
    }
}

template<typename Data>
BST<Data>::BST(BST<Data>&& tree) noexcept{
    std::swap(size, tree.size);
    std::swap(root, tree.root);
}

template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& tree){
    BinaryTreeLnk<Data>::operator=(tree);
    return *this;
}

template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& tree) noexcept{
    BinaryTreeLnk<Data>::operator=(std::move(tree));
    return *this;
}

//Fare ricorsivo
template<typename Data>
bool BST<Data>::operator==(const BST<Data>& tree) const noexcept{
    if(size != tree.size)
        return false;

    BTInOrderIterator<Data> iterator1 (*this);
    BTInOrderIterator<Data> iterator2 (tree);
    
    while(!iterator1.Terminated()){
        if(*iterator1 != *iterator2)
            return false;
        ++iterator1;
        ++iterator2;
    }

    return true;
}

template<typename Data>
bool BST<Data>::operator!=(const BST<Data>& tree) const noexcept{
    return !(*this == tree);
}

template<typename Data>
void BST<Data>::Insert(const Data& val) {
    NodeLnk*& temp = FindPointerTo(root, val);
    if(temp == nullptr){
        temp = new NodeLnk(val);
        size++;
    }
}

template<typename Data>
void BST<Data>::Insert(Data&& val) noexcept{
    NodeLnk*& temp = FindPointerTo(root, val);
    if(temp == nullptr){
        temp = new NodeLnk(std::move(val));
        size++;
    }
}

template<typename Data>
void BST<Data>::Remove(const Data& val) {
    delete Detach(FindPointerTo(root, val));
}

template<typename Data>
const Data& BST<Data>::Min() const{
    if(root == nullptr)
        throw std::length_error("Length error");
    
    return FindPointerToMin(root)->info;
}

template<typename Data>
Data BST<Data>::MinNRemove() {
    if(root == nullptr)
        throw std::length_error("Length error");
    
    return DataNDelete(DetachMin(root));
}

template<typename Data>
void BST<Data>::RemoveMin() {
    delete DetachMin(root);
}

template<typename Data>
const Data& BST<Data>::Max() const{
    if(root == nullptr)
        throw std::length_error("Length error");
    
    return FindPointerToMax(root)->info;
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
    if(root == nullptr)
        throw std::length_error("Length error");
    
    return DataNDelete(DetachMax(root));
}

template<typename Data>
void BST<Data>::RemoveMax() {
    delete DetachMax(root);
}

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& val) const{
    NodeLnk* const* temp = FindPointerToPredecessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");

    return (*temp)->info;
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& val){
    NodeLnk** temp = FindPointerToPredecessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");
    return DataNDelete(Detach(*temp));
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& val){
    NodeLnk** temp = FindPointerToPredecessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");

    delete Detach(*temp);
}

template<typename Data>
const Data& BST<Data>::Successor(const Data& val) const{
    NodeLnk* const* temp = FindPointerToSuccessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");

    return (*temp)->info;
}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& val){
    NodeLnk** temp = FindPointerToSuccessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");
    
    return DataNDelete(Detach(*temp));
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& val){
    NodeLnk** temp = FindPointerToSuccessor(root, val);
    if(temp == nullptr)
        throw std::length_error("Length error");

    delete Detach(*temp);
}

template<typename Data>
bool BST<Data>::Exists(const Data& val) const noexcept{
    return (FindPointerTo(root, val) != nullptr);
}

template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node){
    Data val {};
    std::swap(val, node->info);
    delete node;
    return val;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept{
    
    if(node == nullptr)
        return nullptr;
    
    if(node->left == nullptr)
        return SkipOnRight(node);
    else if(node->right == nullptr)
        return SkipOnLeft(node);
    else{
        NodeLnk* max = DetachMax(node->left);
        std::swap(node->info, max->info);
        return max;
    }
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept{
    return SkipOnRight(FindPointerToMin(node));
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept{
    return SkipOnLeft(FindPointerToMax(node));
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& node) noexcept{
    NodeLnk* temp = nullptr;
    if(node != nullptr){
        std::swap(temp, node->left);
        std::swap(temp, node);
        --size;
    }
    return temp;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& node) noexcept{
    NodeLnk* temp = nullptr;
    if(node != nullptr){
        std::swap(temp, node->right);
        std::swap(temp, node);
        --size;
    }
    return temp;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& root) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(root));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& root) const noexcept{
    NodeLnk* const* pointer = &root;
    NodeLnk* curr = root;
    if(curr != nullptr){
        while(curr->left != nullptr){
            pointer = &(curr->left);
            curr = curr->left;
        }
    }
    return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& root) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(root));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& root) const noexcept{
    NodeLnk* const* pointer = &root;
    NodeLnk* curr = root;

    if(curr != nullptr){
        while(curr->right != nullptr){
            pointer = &(curr->right);
            curr = curr->right;
        }
    }
    return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& root, const Data& val) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(root, val));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& root, const Data& val) const noexcept{
    NodeLnk* const* pointer = &root;
    NodeLnk* curr = root;

    if(curr != nullptr){
        while(curr != nullptr && curr->info != val){
            if(curr->info < val){
                pointer = &(curr->right);
                curr = curr->right;
            }
            else {
                pointer = &(curr->left);
                curr = curr->left;
            }
            
        }
    }
    return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& root, const Data& val) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(root, val));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& root, const Data& val) const noexcept{
    NodeLnk* const* pred = nullptr;
    NodeLnk* const* pointer = &root;
    NodeLnk* curr = root;

    if(curr != nullptr){
        while(curr != nullptr && curr->info != val){
            
            if(curr->info < val){
                pred = pointer;
                pointer = &curr->right;
                curr = curr->right;
            }
            else {
                pointer = &curr->left;
                curr = curr->left;
            }
        }
        if(curr != nullptr && curr->left != nullptr)
            pred = &FindPointerToMax(curr->left);

    }

    return pred;
}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& root, const Data& val) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(root, val));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& root, const Data& val) const noexcept{
    NodeLnk* const* succ = nullptr;
    NodeLnk* const* pointer = &root;
    NodeLnk* curr = root;

    if(curr != nullptr){
        while(curr != nullptr && curr->info != val){
            
            if(curr->info < val){
                pointer = &curr->right;
                curr = curr->right;
            }
            else {
                succ = pointer;
                pointer = &curr->left;
                curr = curr->left;
            }

        }
        if(curr != nullptr && curr->right != nullptr)
            succ = &FindPointerToMin(curr->right);
    }


    return succ;
}

/* ************************************************************************** */

}
