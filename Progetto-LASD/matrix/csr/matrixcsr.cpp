
namespace lasd {

template<typename Data>
MatrixCSR<Data>::MatrixCSR(){
    Rows[0] = &head;
}

template<typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong rows, const ulong cols){
    rownum = rows;
    colnum = cols;
    size = rownum * colnum;
    Rows.Resize(rows+1);
    for(ulong i = 0; i <= rownum; i++)
        Rows[i] = &head;

}

template<typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& matrix) {
    size = matrix.size;
    rownum = matrix.rownum;
    colnum = matrix.colnum;
    Rows.Resize(matrix.Rows.Size());
    for(ulong i = 0; i <= rownum; i++)
        Rows[i] = &head;

    for(ulong i = 0; i < rownum; i++){
        for(Node** ptr = matrix.Rows[i]; *ptr != nullptr && ptr != matrix.Rows[i+1]; ptr = &((*ptr)->next)){
            (*this)(i, (*ptr)->data.second) = (*ptr)->data.first;
        }
        
    }

}

template<typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& matrix) noexcept{
    std::swap(size, matrix.size);
    std::swap(rownum, matrix.rownum);
    std::swap(colnum, matrix.colnum);
    std::swap(Rows, matrix.Rows);
    std::swap(head, matrix.head);
    for(ulong i = 0; i <= rownum && Rows[i] == &matrix.head; i++)
        Rows[i] = &head;

    for(ulong i = 0; i <= matrix.rownum && matrix.Rows[i] == &head; i++)
        matrix.Rows[i] = &matrix.head;
    
}

template<typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& matrix){
    MatrixCSR<Data>* temp = new MatrixCSR<Data>(matrix);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& matrix) noexcept{
    std::swap(size, matrix.size);
    std::swap(rownum, matrix.rownum);
    std::swap(colnum, matrix.colnum);
    std::swap(Rows, matrix.Rows);
    std::swap(head, matrix.head);
    for(ulong i = 0; i <= rownum && Rows[i] == &matrix.head; i++){
        Rows[i] = &head;
    }

    for(ulong i = 0; i <= matrix.rownum && matrix.Rows[i] == &head; i++)
        matrix.Rows[i] = &matrix.head;

    return *this;
}

template<typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& matrix) const noexcept{

    return (rownum == matrix.rownum && colnum == matrix.colnum && List<std::pair<Data, ulong>>::operator==(matrix));
}

template<typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& matrix) const noexcept{
    return !(*this == matrix);
}

template<typename Data>
void MatrixCSR<Data>::RowResize(ulong newrows) {
    if(newrows == 0)
        List<std::pair<Data, ulong>>::Clear();
    else{
        ulong oldrows = rownum;
        Rows.Resize(newrows+1);

        Node** curr;

        if(oldrows > newrows){
            curr = Rows[newrows];
            if(*curr != nullptr){
                Node* temp = *curr;
                *curr = nullptr;
                delete temp;
            }   
        }
        else if(oldrows < newrows){

            curr = Rows[oldrows];

            for(ulong i = oldrows + 1; i <= newrows; i++)
                Rows[i] = curr;
        }
    }
    rownum = newrows;
    size = rownum * colnum;
}

template<typename Data>
void MatrixCSR<Data>::ColumnResize(ulong newcols) {
    if(newcols == 0){
        List<std::pair<Data, ulong>>::Clear();
    }
    else if(colnum > newcols){
        ulong i = 1;
        Node** curr = &head;
        while(i <= rownum){
            Node* node;
            Node** pointer = Rows[i];
            while(curr != pointer && (*curr)->data.second < newcols){
                node = *curr;
                curr = &node->next;
            }
            if(curr != pointer){
                Node* temp = *curr;
                *curr = *pointer;
                *pointer = nullptr;
                delete temp;
            }
            while(i <= rownum && Rows[i] == pointer){
                Rows[i] = curr;
                i++;
            }
        }
    }
    colnum = newcols;
    size = rownum * colnum;
    
}

template<typename Data>
bool MatrixCSR<Data>::ExistsCell(const ulong row, const ulong col) const noexcept {
    if((rownum <= row) || (colnum <= col))
        return false;

    Node** curr = Rows[row];
    while(curr != Rows[row+1]){
        if((*curr)->data.second == col)
            return true;

        curr = &((*curr)->next);
    }
    return false;
}

template<typename Data>
Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col) {
    if((rownum <= row) || (colnum <= col))
        throw std::out_of_range("Out of range");

    Node** curr = Rows[row];
    Node** pointer = Rows[row+1];

    while(*curr != nullptr && curr != pointer && (*curr)->data.second <= col){
        if((*curr)->data.second == col)
            return (*curr)->data.first;
        curr = &((*curr)->next);
    }

    Node* temp = new Node(std::make_pair(Data{}, col));
    
    if((*curr) != nullptr){
        temp->next = *curr;
        *curr = temp;
    }
    else
        *curr = temp;

    ulong i = 1;

    while(row + i <= rownum && curr == pointer && curr == Rows[row+i]){
        Rows[row+i] = &(temp)->next;
        i++;
    }

    return temp->data.first;
}

template<typename Data>
const Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col) const {
    if((rownum <= row) || (colnum <= col))
        throw std::out_of_range("Out of range");


    Node** curr = Rows[row];
    while(*curr != nullptr && curr != Rows[row+1] && (*curr)->data.second <= col){
        if((**curr).data.second == col)
            return (*curr)->data.first;
        curr = &((*curr)->next);
    }
    throw std::length_error("Length error");
}

template<typename Data>
void MatrixCSR<Data>::Clear() {
    Rows.Clear();
    List<std::pair<Data, ulong>>::Clear();
    Rows = Vector<Node**>(1);
    Rows[0] = &head;
    rownum = 0;
    colnum = 0;
    
}

template<typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    List<std::pair<Data, ulong>>::MapPreOrder(
    [&fun](std::pair<Data, ulong>& datx, void* parx){
        fun(datx.first, parx);
    },
    par);
}

template<typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par){
    List<std::pair<Data, ulong>>::MapPostOrder(
    [&fun](std::pair<Data, ulong>& datx, void* parx){
        fun(datx.first, parx);
    },
    par);
}

template<typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
    List<std::pair<Data, ulong>>::FoldPreOrder(
    [&fun](const std::pair<Data, ulong>& datx, const void* parx, void* accx){
        fun(datx.first, parx, accx);
    },
    par, acc);
}

template<typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
    List<std::pair<Data, ulong>>::FoldPostOrder(
    [&fun](const std::pair<Data, ulong>& datx, const void* parx, void* accx){
        fun(datx.first, parx, accx);
    },
    par, acc);
}


}


