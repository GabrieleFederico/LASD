
namespace lasd {

/* ************************************************************************** */

template<typename Data>
MatrixVec<Data>::MatrixVec(const ulong rows, const ulong cols){
    rownum = rows;
    colnum = cols;
    size = rows * cols;
    Elems = new Data[size];
}

template<typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec& matrix){
    size = matrix.size;
    rownum = matrix.rownum;
    colnum = matrix.colnum;
    Elems = new Data[size];
    for(ulong i = 0; i < size; i++){
        Elems[i] = matrix.Elems[i];
    }

}

template<typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec&& matrix) noexcept{
    std::swap(size, matrix.size);
    std::swap(rownum, matrix.rownum);
    std::swap(colnum, matrix.colnum);
    std::swap(Elems, matrix.Elems);
}

template<typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& matrix){
    MatrixVec<Data>* temp = new MatrixVec<Data>(matrix);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept{
    std::swap(size, matrix.size);
    std::swap(rownum, matrix.rownum);
    std::swap(colnum, matrix.colnum);
    std::swap(Elems, matrix.Elems);
    return *this;
}

template<typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matrix) const noexcept{
    if(size != matrix.size)
        return false;

    if(rownum != matrix.rownum)
        return false;

    if(colnum != matrix.colnum)
        return false;

    for(ulong i = 0; i < size; i++){
        if(Elems[i] != matrix.Elems[i])
            return false;
    }
    return true;
}

template<typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matrix) const noexcept{
    return !(*this == matrix);
}

template<typename Data>
void MatrixVec<Data>::RowResize(const ulong newrows) {
    ulong newsize = colnum*newrows;
    Vector<Data>::Resize(newsize);
    rownum = newrows;
    size = newsize;
}

template<typename Data>
void MatrixVec<Data>::ColumnResize(const ulong newcols) {
    if(newcols == 0){
        Clear();
    }
    else if(colnum != newcols){

        ulong limit = (colnum < newcols) ? colnum : newcols;
        Data* tempElems = new Data[rownum*newcols] {};

        for(ulong i = 0; i < rownum; i++){
            for(ulong j = 0; j < limit; j++)
                std::swap(Elems[i*colnum+j], tempElems[i*newcols+j]);
        }

        std::swap(Elems, tempElems);
        size = rownum*newcols;
        colnum = newcols;
        delete[] tempElems;

    }
}

template<typename Data>
bool MatrixVec<Data>::ExistsCell(const ulong row, const ulong col) const noexcept{
    return (row < rownum && col < colnum);
}

template<typename Data>
Data& MatrixVec<Data>::operator()(const ulong row, const ulong col){
    return const_cast<Data&>(static_cast<const MatrixVec<Data> *>(this)->operator()(row, col));
}

template<typename Data>
const Data& MatrixVec<Data>::operator()(const ulong row, const ulong col) const{
    if(!ExistsCell(row, col))
        throw std::out_of_range("Out of range");
    return Elems[(colnum*row)+col];
}

template<typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    rownum = 0;
    colnum = 0;
}


/* ************************************************************************** */

}
