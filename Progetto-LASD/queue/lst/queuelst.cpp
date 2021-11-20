
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& container){
    size = container.Size();

    if(size > 0){

        head = new Node(container[0]);
        Node* curr = head;
        
        for(ulong i = 1; i < size; i++){
            Node* temp = new Node (container[i]);
            curr->next = temp; 
            curr = curr->next;
        }
        tail = curr;
    }  
    else{
        tail = head = nullptr;
    }
}

template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst& queue){
    size = queue.size;

    if(!(queue.Empty())){
        head = new Node(queue[0]);
        Node* curr = (queue.head)->next;
        Node* curr2 = head;

        while(curr != nullptr) {
            
            Node* temp = new Node(curr->data);
            curr2->next = temp;
            curr2 = curr2->next;
            curr = curr->next;
        }
        tail = curr2;
    }
    else
        tail = head = nullptr;
}

template<typename Data>
QueueLst<Data>::QueueLst(QueueLst&& queue) noexcept{
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(size, queue.size);

}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue){
    QueueLst<Data>* tempList = new QueueLst<Data>(queue);
    std::swap(*this, *tempList);
    delete tempList;
    return *this;
}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept{
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(size, queue.size);
    return *this;
}

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst& queue) const noexcept{
    return List<Data>::operator==(queue);

}

template<typename Data>
bool QueueLst<Data>::operator!=(const QueueLst& queue) const noexcept{
    return !(*this == queue);
}

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& val){
    if(head == nullptr){
        head = new Node(val);
        tail = head;
    }
    else{
        Node* temp = new Node(val);
        tail->next = temp;
        tail = tail->next;
        temp = nullptr;
        delete temp;
    }
    size++;
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& val) noexcept{
    
    if(head == nullptr){
        head = new Node(val);
        tail = head;
    }
    else{
        Node* temp = new Node(val);
        tail->next = temp;
        tail = tail->next;
        temp = nullptr;
        delete temp;
    }
    size++;

}

template<typename Data>
Data& QueueLst<Data>::Head(){
    if(head == nullptr)
        throw std::length_error("Length error");
    return head->data;
}

template<typename Data>
void QueueLst<Data>::Dequeue(){
    if(head == nullptr)
        throw std::length_error("Length error");

    if(head == tail)
        tail = nullptr;
    
    Node *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete temp;

    size--;

}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue(){
    Data res = Head();
    Dequeue();
    return res;
}

template<typename Data>
void QueueLst<Data>::Clear(){
    List<Data>::Clear();
    tail = nullptr;
}


/* ************************************************************************** */

}
