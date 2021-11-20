#include "list.hpp"
namespace lasd {

/* ************************************************************************** */

template<typename Data>
List<Data>::Node::Node(const Data& val){
    data = val;
    next = nullptr;
}

template<typename Data>
List<Data>::Node::Node(Data&& val) noexcept{
    std::swap(data, val);
}

template<typename Data>
List<Data>::Node::Node(const Data& val, const Node* next){
    data = val;
    this.next = next;
}

template<typename Data>
List<Data>::Node::Node(const Node& val){
    this->data = val.data;
    this->next = val.next;
}

template<typename Data>
List<Data>::Node::Node(Node&& val) noexcept{
    std::swap(data, val.data);
    std::swap(next, val.data);

}

template<typename Data>
List<Data>::Node::~Node(){
    delete next;
}

template<typename Data>
typename List<Data>::Node& List<Data>::Node::operator= (const Node& val){
    Node* temp = new Node(val);
    std::swap(*this, *temp);
    delete temp;
    return *this;

}

template<typename Data>
typename List<Data>::Node& List<Data>::Node::operator= (Node&& val) noexcept{
    std::swap(data, val->data);
    std::swap(next, val->next);
    return *this;
}

template<typename Data>
inline bool List<Data>::Node::operator== (const Node& val) const noexcept{
    return (data == val.data && next == val.next);
}

template<typename Data>
inline bool List<Data>::Node::operator!= (const Node& val) const noexcept{
    return !(this == val);
}

template<typename Data>
void List<Data>::Node::AuxMapPostOrder(const MapFunctor fun, void* par){
    if(next != nullptr)
        next->AuxMapPostOrder(fun, par);
    fun(data, par); 
}

template<typename Data>
void List<Data>::Node::AuxFoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    if(next != nullptr)
        next->AuxFoldPostOrder(fun, par, acc);
    fun(data, par, acc);    
}

template<typename Data>
List<Data>::List(const LinearContainer<Data>& container){
    
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
List<Data>::List(const List<Data>& val){
    
    size = val.size;

    if(!(val.Empty())){
        head = new Node(val[0]);
        Node* curr = (val.head)->next;
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
List<Data>::List(List<Data>&& val) noexcept{

    std::swap(size, val.size);
    std::swap(head, val.head);

}

template<typename Data>
List<Data>::~List(){
    delete head;

}

template<typename Data>
List<Data>& List<Data>::operator= (const List<Data>& val){
    
    List<Data>* tempList = new List<Data>(val);
    std::swap(*this, *tempList);
    
    return *this;
}

template<typename Data>
List<Data>& List<Data>::operator= (List&& val) noexcept{

    std::swap(head, val.head);
    std::swap(size, val.size);

    return *this;
}

template<typename Data>
bool List<Data>::operator==(const List<Data>& val) const noexcept{

    if(size == val.size){
        Node* head1 = head, *head2 = val.head;

        while(head1 != nullptr){
            if((head1->data) != (head2->data))
                return false;

            head1 = head1->next;
            head2 = head2->next;
        }
        return true;

    }
    else
        return false;
}

template<typename Data>
inline bool List<Data>::operator!= (const List<Data>& val) const noexcept{
    return !(*this == val);
}

template<typename Data>
void List<Data>::InsertAtFront(const Data& val){
    Node* temp = new Node(val);
    temp->next = head;
    head = temp;

    ++size;
}

template<typename Data>
void List<Data>::InsertAtFront(Data&& val) noexcept{
    Node* temp = new Node(std::move(val));
    temp->next = head;
    head = temp;

    ++size;
}

template<typename Data>
void List<Data>::RemoveFromFront(){
    if(this->Empty())
        throw std::length_error("La lista è vuota");

    Node* temp = head;
    head = head->next;
    temp->next = nullptr;
    --size;
    delete temp;

}

template<typename Data>
Data List<Data>::FrontNRemove(){
    if(this->Empty())
        throw std::length_error("La lista è vuota");

    Data res = head->data;
    this->RemoveFromFront();

    return res;

}

template<typename Data>
void List<Data>::InsertAtBack(const Data& val){
    Node* temp = new Node(val);
    Node* curr = head;
    if(head != nullptr){
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    else
        head = new Node(val);

    ++size;
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept{


    if(head != nullptr){
        Node* temp = new Node(std::move(val));
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    else
        head = new Node(val);
    
    ++size;
}

template<typename Data>
void List<Data>::Clear(){

    delete head;
    head = nullptr;
    size = 0;

}

template<typename Data>
Data& List<Data>::Front() const {

    if(size == 0)
        throw std::length_error("Length error");

    return (head->data);

}

template<typename Data>
Data& List<Data>::Back() const {

    if(size == 0)
        throw std::length_error("Length error");

    return (*this)[size-1];

}

template<typename Data>
Data& List<Data>::operator[] (const ulong idx) const{

    if(idx < size){
        Node* temp = new Node(*head);
        for(ulong i = 0; i < idx; i++){
            temp = temp->next;

        }
    return temp->data;
    }
    else
        throw std::out_of_range("Length error");

}

template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par){
    
    //La versione commentata funziona su tutta la struttura ignorando eventuali indici, 
    //poi modificata chiamando la funzione ausiliaria che funziona a partire da un determinato indice passandogli 0
    // Node* temp = head;
    // while(temp != nullptr){
    //     fun(temp->data, par);
    //     temp = temp->next;
    // }
    MapPreOrder(fun, par, 0);
}

template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par){

    //if(head != nullptr)
    //    head->AuxMapPostOrder(fun, par);
    MapPostOrder(fun, par, 0);

}

template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
    // Node* temp = head;
    // while(temp != nullptr){
    //     fun(temp->data, par, acc);
    //     temp = temp->next;
    // }
    FoldPreOrder(fun, par, acc, 0);
}

template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    // if(head != nullptr)
    //     head->AuxFoldPostOrder(fun, par, acc);
    FoldPostOrder(fun, par, acc, 0);
}

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par, ulong idx){


    Node* temp = head;
    for(ulong i = 0; i < idx; i++)
        temp = temp->next;
        
    while(temp != nullptr){
        fun(temp->data, par);
        temp = temp->next;
    }
    

}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par, ulong idx){

    ulong i = 0;
    Node* temp = head;
    while (i < idx && temp != nullptr){
        temp = temp->next;
        ++i;
    }
    if(temp != nullptr)
        temp->AuxMapPostOrder(fun, par);
        
        
}

template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, const ulong idx) const{

    ulong i = 0; 
    Node* temp = head;
    while(i < idx && temp != nullptr){
        temp = temp->next;
        i++;
    }
        
    while(temp != nullptr){
        fun(temp->data, par, acc);
        temp = temp->next;
    }
    

}

template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, const ulong idx) const{

    ulong i = 0;
    Node* temp = head;
    while (i < idx && temp != nullptr){
        temp = temp->next;
        ++i;
    }
    if(temp != nullptr)
        temp->AuxFoldPostOrder(fun, par, acc);
        
}

/* ************************************************************************** */

}
