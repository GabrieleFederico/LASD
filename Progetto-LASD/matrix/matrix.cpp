
namespace lasd {

/* ************************************************************************** */

template<typename Data>
ulong Matrix<Data>::RowNumber() const noexcept{
    return rownum;
}

template<typename Data>
ulong Matrix<Data>::ColumnNumber() const noexcept{
    return colnum;
}

/* ************************************************************************** */

}
