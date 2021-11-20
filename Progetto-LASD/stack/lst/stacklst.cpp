
namespace lasd {

/* ************************************************************************** */

template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& container){
    
    size = container.Size();
    if(size > 0){

        head = new Node(container[0]);
        Node* curr = head;
        
        for(ulong i = 1; i < size; i++){
            Node* temp = new Node (container[i]);
            curr->next = temp; 
            curr = curr->next;
        }
    }   
    else
        head = nullptr;
    
    
}

template<typename Data>
StackLst<Data>::StackLst(const StackLst& stack){

    size = stack.size;

    if(!(stack.Empty())){
        head = new Node(stack.head->data);
        Node* curr = (stack.head)->next;
        Node* curr2 = head;

        while(curr != nullptr) {
            
            Node* temp = new Node(curr->data);
            curr2->next = temp;
            curr2 = curr2->next;
            curr = curr->next;
        }
    }
    else
        head = nullptr;
}

template<typename Data>
StackLst<Data>::StackLst(StackLst&& stack) noexcept{
    std::swap(head, stack.head);
    std::swap(size, stack.size);

}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst& stack){
    StackLst<Data>* tempList = new StackLst<Data>(stack);
    std::swap(*this, *tempList);
    delete tempList;
    return *this;
}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst&& stack) noexcept{
    std::swap(head, stack.head);
    std::swap(size, stack.size);
    return *this;
}

template<typename Data>
bool StackLst<Data>::operator==(const StackLst& stack) const noexcept{

    return List<Data>::operator==(stack);  
    
}

template<typename Data>
bool StackLst<Data>::operator!=(const StackLst& stack) const noexcept{
    return !(*this == stack);
}

template<typename Data>
void StackLst<Data>::Push(const Data& val) {
    List<Data>::InsertAtFront(val);
}

template<typename Data>
void StackLst<Data>::Push(Data&& val) noexcept{
    List<Data>::InsertAtFront(std::move(val));
}

template<typename Data>
Data& StackLst<Data>::Top(){
    return List<Data>::Front();
}

template<typename Data>
void StackLst<Data>::Pop(){
    List<Data>::RemoveFromFront();

}

template<typename Data>
Data StackLst<Data>::TopNPop(){
    return List<Data>::FrontNRemove();
}

template<typename Data>
void StackLst<Data>::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

}
