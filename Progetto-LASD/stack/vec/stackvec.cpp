
namespace lasd {

/* ************************************************************************** */


template<typename Data>
StackVec<Data>::StackVec(){
    size = 2;
    usedSize = 0;
    Elems = new Data[size] {};

}

template<typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& container){
    size = (ulong)container.Size()*1.5;
    usedSize = container.Size();
    Elems = new Data[size] {};
    for(ulong i = 0; i < usedSize; i++)
        Elems[i] = container[i];


}

template<typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stack){

    size = stack.size;
    Elems = new Data[size];
    std::copy(stack.Elems, stack.Elems + stack.usedSize, Elems);
    usedSize = stack.usedSize;
}

template<typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stack) noexcept{
    std::swap(Elems, stack.Elems);
    std::swap(size, stack.size);
    std::swap(usedSize, stack.usedSize);
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stack){

    StackVec<Data>* tempstack = new StackVec<Data>(stack);
    std::swap(*tempstack, *this);
    delete tempstack;
    return *this;
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stack) noexcept{
    std::swap(Elems, stack.Elems);
    std::swap(size, stack.size);
    std::swap(usedSize, stack.usedSize);
    return *this;
}

template<typename Data>
bool StackVec<Data>::operator==(const StackVec& stack) const noexcept{
    
    if(usedSize != stack.usedSize)
        return false;

    for(ulong i = 0; i < usedSize; i++){
        if(Elems[i] != stack.Elems[i])
            return false;
    }

    return true;
}

template<typename Data>
bool StackVec<Data>::operator!=(const StackVec& stack) const noexcept{
    return !(*this == stack);
}

template<typename Data>
void StackVec<Data>::Push(const Data& val){
    
    if(usedSize == size){
        Expand();
    }

    Elems[usedSize] = val;
    usedSize++;
    
}

template<typename Data>
void StackVec<Data>::Push(Data&& val) noexcept{
    if(usedSize == size){
        Expand();
    }
    std::swap(Elems[usedSize], val);
    usedSize++;
    
}

template<typename Data>
Data& StackVec<Data>::Top(){
    
    if(usedSize == 0)
        throw std::length_error("Length error");
    return Elems[usedSize-1];
}

template<typename Data>
void StackVec<Data>::Pop(){
    if(Empty())
        throw std::length_error("Length error");
    usedSize--;
    if(usedSize < (size/4)){
        Reduce();
    }
}

template<typename Data>
Data StackVec<Data>::TopNPop(){
    Data res = Top();
    Pop();
    return res;
}

template<typename Data>
bool StackVec<Data>::Empty() const noexcept{
    return (usedSize == 0);
}

template<typename Data>
ulong StackVec<Data>::Size() const noexcept{
    return usedSize;
}

template<typename Data>
void StackVec<Data>::Clear(){
    delete[] Elems;
    size = 2;
    Elems = new Data[size] {};
    usedSize = 0;
}

template<typename Data>
void StackVec<Data>::Expand(){
    ulong newsize = size + (size/2);
    Vector<Data>::Resize(newsize);
}

template<typename Data>
void StackVec<Data>::Reduce(){
    ulong newsize = size - (size/2);
    Vector<Data>::Resize(newsize);
}

/* ************************************************************************** */

}
