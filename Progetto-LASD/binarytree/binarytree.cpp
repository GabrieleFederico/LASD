
// #include "..."

namespace lasd {

/* ************************************************************************** */

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept{

    if(Element() != node.Element())
        return false;

    if(IsLeaf() ^ node.IsLeaf())
        return false;

    if(HasLeftChild() && node.HasLeftChild()){
        if(LeftChild() != node.LeftChild())
            return false;
    }
    else if(HasLeftChild() ^ node.HasLeftChild())
        return false;

    if(HasRightChild() && node.HasRightChild()){
            if(RightChild() != node.RightChild())
                return false;
    }
    else if(HasRightChild() ^ node.HasRightChild())
        return false;

    return true;
        
}

template<typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept{
    return !(*this == node);
}

template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& tree) const noexcept{

    try{
        return(Root() == tree.Root());
    }
    catch(std::length_error e){
        if(this->Empty() && tree.Empty())
            return true;

        return false;
    }

}

template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& tree) const noexcept{
    return !(*this == tree);
}

template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    if(!this->Empty())
        MapPreOrder(fun, par, Root());
}

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if(!this->Empty())
        FoldPreOrder(fun, par, acc, Root());
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
    if(!this->Empty())
        MapPostOrder(fun, par, Root());
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if(!this->Empty())
        FoldPostOrder(fun, par, acc, Root());
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
    if(!this->Empty())
        MapInOrder(fun, par, Root());
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if(!this->Empty())
        FoldInOrder(fun, par, acc, Root());
}

template<typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {
    if(!this->Empty())
        MapBreadth(fun, par, Root());
}

template<typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
    if(!this->Empty())
        FoldBreadth(fun, par, acc, Root());
}

template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node& root)  {
    fun(root.Element(), par);

    if(root.HasLeftChild())
        MapPreOrder(fun, par, root.LeftChild());
    
    if(root.HasRightChild())
        MapPreOrder(fun, par, root.RightChild());
}

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node& root) const {
    fun(root.Element(), par, acc);
    
    if(root.HasLeftChild())
        FoldPreOrder(fun, par, acc, root.LeftChild());
    
    if(root.HasRightChild())
        FoldPreOrder(fun, par, acc, root.RightChild());
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node& root){

    if(root.HasLeftChild())
        MapPostOrder(fun, par, root.LeftChild());
    
    if(root.HasRightChild())
        MapPostOrder(fun, par, root.RightChild());

    fun(root.Element(), par);
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node& root) const {
    
    if(root.HasLeftChild())
        FoldPostOrder(fun, par, acc, root.LeftChild());
    
    if(root.HasRightChild())
        FoldPostOrder(fun, par, acc, root.RightChild());

    fun(root.Element(), par, acc);
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node& root) {
    if(root.HasLeftChild())
        MapInOrder(fun, par, root.LeftChild());

    fun(root.Element(), par);

    if(root.HasRightChild())
        MapInOrder(fun, par, root.RightChild());
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node& root) const {


    if(root.HasLeftChild())
        FoldInOrder(fun, par, acc, root.LeftChild());
    
    fun(root.Element(), par, acc);

    if(root.HasRightChild())
        FoldInOrder(fun, par, acc, root.RightChild());

}

template<typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node& root) {
    QueueLst<Node*> queue;
    queue.Enqueue(&root);
    Node* curr;

    while(!queue.Empty()){
        curr = queue.HeadNDequeue();

        fun(curr->Element(), par);

        if(curr->HasLeftChild())
            queue.Enqueue(&curr->LeftChild());

        if(curr->HasRightChild())
            queue.Enqueue(&curr->RightChild());
        
    }

}

template<typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node& root) const {
    QueueLst<Node*> queue;
    queue.Enqueue(&root);
    Node* curr;

    while(!queue.Empty()){
        curr = queue.HeadNDequeue();

        fun(curr->Element(), par, acc);

        if(curr->HasLeftChild())
            queue.Enqueue(&curr->LeftChild());

        if(curr->HasRightChild())
            queue.Enqueue(&curr->RightChild());
        
    }
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree){
    if(!tree.Empty())
        curr = &tree.Root();
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& iterator){
    curr = iterator.curr;
    stack = iterator.stack;
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(stack, iterator.stack);
}

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& iterator){
    BTPreOrderIterator<Data>* temp = new BTPreOrderIterator<Data>(iterator); 
    std::swap(*this, temp);
    delete temp;
    return *this;
}

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(stack, iterator.stack);
    return *this;
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& iterator) const noexcept{
    if(stack != iterator.stack)
        return false;
    
    return (curr == iterator.curr);
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& iterator) const noexcept{
    return !(*this == iterator);
}

template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Out of range");

    return curr->Element();
}

template<typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    
    return (stack.Empty() && curr == nullptr);
}

template<typename Data>
void BTPreOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Out of range");

    if(curr->HasRightChild())
        stack.Push(&curr->RightChild());

    if(curr->HasLeftChild())
        stack.Push(&curr->LeftChild());

    if(!stack.Empty())
        curr = stack.TopNPop();
    else 
        curr = nullptr;
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree){
    if(!tree.Empty()){

        curr = &(tree.Root());
        stack.Push(curr);
        
        while(!curr->IsLeaf()){

            if(curr->HasLeftChild())
                stack.Push(&curr->LeftChild());

            else
                stack.Push(&curr->RightChild());


            curr = stack.Top();
        }

        stack.Pop();
    }

}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& iterator){
    curr = iterator.curr;
    stack = iterator.stack;
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(stack, iterator.stack);
}

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& iterator){
    BTPostOrderIterator<Data>* temp = new BTPostOrderIterator<Data>(iterator); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(stack, iterator.stack);
    return *this;
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& iterator) const noexcept{
    if(stack != iterator.stack)
        return false;

    return (curr == iterator.curr);
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& iterator) const noexcept{
    return !(*this == iterator);
}

template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Out of range");

    return curr->Element();
}

template<typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    return (stack.Empty() && curr == nullptr);
}

template<typename Data>
void BTPostOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Out of range");

    if(!stack.Empty()){
        typename BinaryTree<Data>::Node* temp = stack.Top();

        if(temp->HasLeftChild() && temp->HasRightChild()){
            if(curr == &(temp->LeftChild())){

                temp = &temp->RightChild();
                stack.Push(temp);

                while(!temp->IsLeaf()){

                    if(temp->HasLeftChild())
                        stack.Push(&temp->LeftChild());
                    else
                        stack.Push(&temp->RightChild());

                    temp = stack.Top();
                }
                
            }
        }
        curr = stack.TopNPop();
    }
    else
        curr = nullptr;
    
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree){
    if(!tree.Empty()){
        curr = &tree.Root();
        stack.Push(curr);

        while(curr->HasLeftChild()){

            stack.Push(&curr->LeftChild());

            curr = stack.Top();
        }
        stack.Pop();
    }
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& iterator){
    curr = iterator.curr;
    stack = iterator.stack;
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& iterator) noexcept{
    std::swap(stack, iterator.stack);
    std::swap(curr, iterator.curr);
}

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& iterator){
    BTInOrderIterator<Data>* temp = new BTInOrderIterator<Data>(iterator); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& iterator) noexcept{
    std::swap(stack, iterator.stack);
    std::swap(curr, iterator.curr);
    return *this;
}

template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator& iterator) const noexcept{
    if(stack != iterator.stack)
        return false;

    return (curr == iterator.curr);
}

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator& iterator) const noexcept{
    return !(*this == iterator);
}

template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Out of range");

    return curr->Element();
}

template<typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept{
    return (stack.Empty() && curr == nullptr);
}

template<typename Data>
void BTInOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Out of range");

    if(curr->HasRightChild()){
        typename BinaryTree<Data>::Node* temp = &curr->RightChild();
        stack.Push(temp);

        while(temp->HasLeftChild()){

            stack.Push(&temp->LeftChild());

            temp = stack.Top();
        }
    }

    if(!stack.Empty())
        curr = stack.TopNPop();
    else 
        curr = nullptr;

}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree){
    if(!tree.Empty())
        curr = &tree.Root();

}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& iterator){
    curr = iterator.curr;
    queue = iterator.queue;
}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(queue, iterator.queue);
}

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& iterator){
    BTBreadthIterator<Data>* temp = new BTBreadthIterator<Data>(iterator); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& iterator) noexcept{
    std::swap(curr, iterator.curr);
    std::swap(queue, iterator.queue);
    return *this;
}

template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator& iterator) const noexcept{
    if(queue != iterator.queue)
        return false;
    
    return (curr == iterator.curr);
}

template<typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator& iterator) const noexcept{
    return !(*this == iterator);
}

template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Out of range");

    return curr->Element();
}

template<typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return (queue.Empty() && curr == nullptr);
}

template<typename Data>
void BTBreadthIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Out of range");

    if(curr->HasLeftChild())
        queue.Enqueue(&curr->LeftChild());
        
    if(curr->HasRightChild())
        queue.Enqueue(&curr->RightChild());
    
    if(!queue.Empty())
        curr = queue.HeadNDequeue();
    else
        curr = nullptr;

}

/* ************************************************************************** */

}
