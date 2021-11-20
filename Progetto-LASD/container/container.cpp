
namespace lasd {

/* ************************************************************************** */

template<typename Data>
void AuxFoldExists(const Data& elem, const void* value, void* check){

    if(elem == *((Data*)value))
        *((bool* )check) = true;
}

template<typename Data>
bool FoldableContainer<Data>::Exists(const Data& elem) const noexcept{
    bool check = false;
    FoldPreOrder(&AuxFoldExists<Data>, &elem, &check);
    return check;
}

/* ************************************************************************** */

}
