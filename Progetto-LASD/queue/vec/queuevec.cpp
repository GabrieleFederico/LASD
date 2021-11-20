
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueVec<Data>::QueueVec(){
    size = 2;
    Elems = new Data[size] {};
    head = 0;
    tail = 0;

}

template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& container){
    size = (ulong)container.Size()*1.5;
    if(size < 2)
        size = 2;
        
    Elems = new Data[size] {};
    for(ulong i = 0; i < container.Size(); i++)
        Enqueue(container[i]);
    head = 0;
    tail = container.Size();

}

template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& queue){

    size = queue.size;
    head = queue.head;
    tail = queue.tail;
    Elems = new Data[size];
    std::copy(queue.Elems, queue.Elems + queue.size, Elems);

}

template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept{

    std::swap(Elems, queue.Elems);
    std::swap(size, queue.size);
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);

}

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue){
    QueueVec<Data>* tempqueue = new QueueVec<Data>(queue);
    std::swap(*tempqueue, *this);
    delete tempqueue;
    return *this;
}

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept{
    std::swap(Elems, queue.Elems);
    std::swap(size, queue.size);
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);

    return *this;
}

template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept{

    if(Size() == queue.Size()){  
        for(ulong i = 0; i < Size(); i++){
            if(Elems[(i + head) % size] != queue.Elems[(i + queue.head) % queue.size])
                return false;
        }
            
    }
    else
        return false;

    return true;
}

template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept{
    return !(*this == queue);
}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data& val){
    if(Size() == (size-1))
        Expand();
    
    Elems[tail] = val;    
    tail = (tail+1) % size;
    

}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& val) noexcept{
 
    if(Size() == (size-1))
        Expand();

    std::swap(Elems[tail], val);  
    tail = (tail+1) % size;

}

template<typename Data>
Data& QueueVec<Data>::Head(){
    if(Empty())
        throw std::length_error("Length error");

    return Elems[head];

}

template<typename Data>
void QueueVec<Data>::Dequeue(){
    if(head == tail)
        throw std::length_error("Length error");
    
    head = (head + 1) % size;
    if(Size() <= size/4)
        Reduce();
    
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    Data res = Head();
    Dequeue();
    return res;
}

template<typename Data>
bool QueueVec<Data>::Empty() const noexcept {
    
    return (Size() == 0);
}

template<typename Data>
ulong QueueVec<Data>::Size() const noexcept {
    if(head <= tail)
        return (tail - head);
    else
        return (size - head - tail);

}

template<typename Data>
void QueueVec<Data>::Clear(){
    size = 2;
    delete[] Elems;
    Elems = new Data[size];
    head = 0;
    tail = 0;

}

template<typename Data>
void QueueVec<Data>::Expand(){

    if(head > tail)
        SwapVectors();

    ulong newsize = size + (size/2);
    Vector<Data>::Resize(newsize);
}

template<typename Data>
void QueueVec<Data>::Reduce(){

    SwapVectors();

    ulong newsize = (size/2);
    if(newsize < 2)
        newsize = 2;
    Vector<Data>::Resize(newsize);
}

template<typename Data>
void QueueVec<Data>::SwapVectors(){

    Data* vector = new Data[size] {};
    for(ulong i = 0; i < Size(); i++)
        vector[i] = Elems[(i+head) % size];
        
    delete[] Elems;
    Elems = vector;
    tail = Size();
    head = 0;
}


/* ************************************************************************** */

}
