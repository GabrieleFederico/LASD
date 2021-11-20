
namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const ulong newsize){

    Elems = new Data[newsize] {};
    size = newsize;
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& container){

    size = container.Size();
    Elems = new Data[size];

    for(ulong i = 0; i < size; i++)
        Elems[i] = container[i];
}

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vettore){

    size = vettore.size;
    Elems = new Data[size];
    std::copy(vettore.Elems, vettore.Elems + vettore.size, Elems);
    
}

template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vettore) noexcept{

    std::swap(Elems, vettore.Elems);
    std::swap(size, vettore.size);
}

template<typename Data>
Vector<Data>::~Vector(){
    delete[] Elems;
    size = 0;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator= (const Vector<Data>& vettore){

    Vector<Data>* tempvett = new Vector<Data>(vettore);
    std::swap(*tempvett, *this);
    delete tempvett;
    return *this;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator= (Vector<Data>&&vettore){

    std::swap(Elems, vettore.Elems);
    std::swap(size, vettore.size);
    return *this;
}

template<typename Data>
bool Vector<Data>::operator== (const Vector<Data>& vettore) const noexcept{
    
    if(size == vettore.size){
        for(ulong i = 0; i < size; i++){
            if(Elems[i] != vettore.Elems[i]){
                return false;
            }
        }
        return true;
    }
    else 
        return false;
}

template<typename Data>
inline bool Vector<Data>::operator!= (const Vector<Data>& vettore) const noexcept{
    return !(*this == vettore);
}

template<typename Data>
void Vector<Data>::Resize(const ulong newsize){
    
    if(newsize == 0){
        Clear();
    }
    else if(size != newsize){

        ulong limit = (size < newsize) ? size : newsize;
        Data* tempElems = new Data[newsize] {};

        for(ulong i = 0; i < limit; i++){

            std::swap(Elems[i], tempElems[i]);
        }

        std::swap(Elems, tempElems);
        size = newsize;
        delete[] tempElems;

    }
}

template<typename Data>
void Vector<Data>::Clear(){

    delete[] Elems;
    Elems = nullptr;
    size = 0;
}

template<typename Data>
Data& Vector<Data>::Front() const{

    if(size == 0)
        throw std::length_error("Length error");
    else 
        return Elems[0];
}

template<typename Data>
Data& Vector<Data>::Back() const{

    if(size == 0)
        throw std::length_error("Length error");
    else 
        return Elems[size-1];
}

template<typename Data>
Data& Vector<Data>::operator[] (const ulong idx) const{
    
    if(idx < size)
        return Elems[idx];
    else
        throw std::out_of_range("Out of range error");
}

template<typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par){

    for(ulong i = 0; i < size; i++)
        fun(Elems[i], par);
}

template<typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par){

    ulong i = size;
    while(i > 0)
        fun(Elems[--i], par);
}

template<typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{

    for(ulong i = 0; i < size; i++)
        fun(Elems[i], par, acc);
}

template<typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    
    ulong i = size;
    while(i > 0)
        fun(Elems[--i], par, acc);
}


/* ************************************************************************** */

}
