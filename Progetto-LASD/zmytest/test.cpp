#include <iostream>
#include <string>
#include <random>
#include "test.hpp"
#include <iomanip>

using namespace lasd;

void myTest(){
    structureChoice();
    return;
}

void structureChoice(){

    std::cout << "Pick the data structure:\n 1-Vector\n 2-List \n 3-Stack \n 4-Queue \n 5-BinaryTree \n 6-Matrix" << std::endl;
    int choice = 1;
    
    while(choice){
        std::cin >> choice;
        switch(choice){
            case 1:
                dataChoiceVector();
                return;
                break;
            case 2:
                dataChoiceList(); 
                return;
                break;
            case 3:
                structureTypeChoiceStack();
                return;
                break;
            case 4:
                structureTypeChoiceQueue();
                return;
                break;
            case 5:
                structureTypeChoiceBT();
                return;
                break;
            case 6:
                structureTypeChoiceMatrix();
                return;
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
    

}

void dataChoiceVector(){

    ulong len;
    std::cout << "Choose the length of the data structure: "<< std::endl;
    std::cin >> len;

    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            Vector<int> vett = intVector(len);
            vectorTestChoice(vett);
            return;
            break;
        }
        case 2:{
            Vector<double> vett = doubleVector(len);
            vectorTestChoice(vett);
            return;
            break;
        }
        case 3:{
            Vector<std::string> vett = stringVector(len);
            vectorTestChoice(vett);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}
        
Vector<int> intVector(const ulong len){

    Vector<int> vector = Vector<int>(len); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 200);
    for(ulong i = 0; i < vector.Size(); i++){
        vector[i] = dist(gen);
    }
    return vector;

}
              
Vector<double> doubleVector(const ulong len){
    Vector<double> vector = Vector<double>(len); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<double> dist;
    for(ulong i = 0; i < vector.Size(); i++){
        vector[i] = dist(gen);
    }
    return vector;

}
       
Vector<std::string> stringVector(const ulong len){
    Vector<std::string> vector = Vector<std::string>(len);

    std::string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10);
    std::uniform_int_distribution<int> randPos(0, table.size()-1);

    std::string temp;
    for(ulong i = 0; i < len; i++){
        temp = "";
        uint newLen = dist(gen);
        for(ulong j = 0; j < newLen; j++){
            temp += table[randPos(gen)];
        }
        vector[i] = temp;
    }

    return vector;
}

template<typename Data>
void vectorTestChoice(Vector<Data> vector){
    int choice = 1;
    
    
    while(choice){
        std::cout << "Choose what to do: " << std::endl;
        std::cout << " 1-Visualizza il primo elemento \n 2-Visualizza l'ultimo elemento \n 3-Visualizza un elemento"
        "\n 4-Visualizza tutti gli elementi \n 5-Controlla esistenza \n 6-Ridimensiona"
        "\n 7-Specific test fold \n 8-Specific test map \n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                std::cout <<"First element is: "<< vector.Front() << std::endl;
                break;
            }
            case 2:{
                std::cout <<"Last element is: "<< vector.Back() << std::endl;
                break;
            }
            case 3:{
                ulong i;
                std::cout << "Pick the index: " << std::endl;
                std::cin >> i;
                std::cout <<"Element at index "<< i <<" is: " << vector[i] << std::endl;
                break;
            }
            case 4:{
                printPreOrder(vector);
                std::cout << std::endl;
                break;
            }
            case 5:{
                Data val;
                std::cout << "Scegliere il valore di cui verificare l'esistenza: " << std::endl;
                std::cin >> val;
                if(vector.Exists(val))
                    std::cout << "Il valore esiste\n" << std::endl;
                else
                    std::cout <<"Il valore non esiste\n" << std::endl;
                break;
            }
            case 6:{
                ulong newDim;
                std::cout << "Inserisci la nuova dimensione: " << std::endl;
                std::cin >> newDim;
                vector.Resize(newDim);
                break;
            }
            case 7:{
                specificTestFold(vector);
                break;
            }
            case 8:{
                specificTestMap(vector);
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }

    }
}

void dataChoiceList(){
    ulong len;
    std::cout<< "Choose the length of the data structure: "<< std::endl;
    std::cin >> len;

    std::cout << "Pick the data type: \n1-Int \n2-Double \n3-String" << std::endl;
    uint choice = 0;
    std::cin >> choice;
    switch(choice){
        case 1:{
            List<int> list(intVector(len));
            listTestChoice(list);
            break;
        }
        case 2:{
            List<double> list(doubleVector(len));
            listTestChoice(list);
            break;
        }
        case 3:{
            List<std::string> list(stringVector(len));
            listTestChoice(list);
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

template<typename Data>
void listTestChoice(List<Data> list){
    int choice = 1;
    
    
    while(choice){
        std::cout << "Choose what to do: " << std::endl;
        std::cout << " 1-Visualizza il primo elemento \n 2-Visualizza l'ultimo elemento \n 3-Visualizza un elemento"
        "\n 4-Visualizza tutti gli elementi \n 5-Controlla esistenza \n 6-Specific test Fold"
        "\n 7-Specific test Map \n 8-Inserimento in testa \n 9-Inserimento in coda"
        "\n 10-Rimozione in testa \n 11-Rimozione e lettura in testa \n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                std::cout <<"First element is: "<< list.Front() << std::endl;
                break;
            }
            case 2:{
                std::cout <<"Last element is: "<< list.Back() << std::endl;
                break;
            }
            case 3:{
                ulong i;
                std::cout << "Pick the index: " << std::endl;
                std::cin >> i;
                std::cout <<"Element at index "<< i <<" is: " << list[i] << std::endl;
                break;
            }
            case 4:{
                printPreOrder(list);
                std::cout << std::endl;
                break;
            }
            case 5:{
                Data val;
                std::cout << "Scegliere il valore di cui verificare l'esistenza: " << std::endl;
                std::cin >> val;
                if(list.Exists(val))
                    std::cout << "Il valore esiste\n" << std::endl;
                else
                    std::cout <<"Il valore non esiste\n" << std::endl;
                break;
            }
            case 6:{
                specificTestFold(list);
                break;
            }
            case 7:{
                specificTestMap(list);
                break;
            }
            case 8:{
                std::cout << "Inserire l'elemento da inserire in testa: " << std::endl;
                Data newData;
                std::cin >> newData;
                list.InsertAtFront(newData);
                break;
            }
            case 9:{
                std::cout << "Inserire l'elemento da inserire in coda: " << std::endl;
                Data newData;
                std::cin >> newData;
                list.InsertAtBack(newData);
                break;
            }
            case 10:{
                list.RemoveFromFront();
                break;
            }
            case 11:{
                Data res = list.FrontNRemove();
                std::cout << "L'elemento rimosso è: " << res << std::endl;
                break;   
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }

    }
}

template<typename Data>
void printPreOrder(MappableContainer<Data>& container){
    int par = 0;
    container.MapPreOrder(&mapPrint<Data>, &par);

}

template<typename Data>
void printPostOrder(MappableContainer<Data>& container){
    int par = 0;
    container.MapPostOrder(&mapPrint<Data>, &par);

}

template<typename Data>
void mapPrint(Data& data, void* par){
    //setprecision serve poiché in caso di stampa di double potrebbe risultare fuorviante leggere il numero stampato
    //senza la precisione adatta, in particolare testando l'esistenza di un dato all'interno della struttura
    //stampando però prima la struttura per assicurarmi che il dato fosse presente, volendo poi verificare l'esistenza
    //di quel dato il testo non aveva risvolto positivo a causa della precisione di stampa
    std::cout << std::setprecision(46) << data << "    ";
}

void specificTestFold(FoldableContainer<int>& container){
    int n;
    std::cout << "Inserire il valore n: " << std::endl;
    std::cin >> n;
    const int par = n;
    int acc = 0;
    container.FoldPreOrder(&sumInt, &par, &acc);
    std::cout << "Il risultato è: " << acc << std::endl;
}

void specificTestFold(FoldableContainer<double>& container){
    int n;
    std::cout << "Inserire il valore n: ";
    std::cin >> n;
    const int par = n;
    double acc = 1;
    container.FoldPreOrder(&productDouble, &par, &acc);
    std::cout << "Il risultato è: " << acc << std::endl;
}

void specificTestFold(FoldableContainer<std::string>& container){
    int n;
    std::cout << "Inserire il valore n: ";
    std::cin >> n;
    const int par = n;
    std::string acc = "";
    container.FoldPreOrder(&concatString, &par, &acc);
    std::cout << "Il risultato è: " << acc << std::endl;
}

//Somma di numeri < n
void sumInt(const int& data, const void* n, void* res){
    if(data < *((int*)n))
        *((int*)res) += data;

}

//Prodotto di numeri > n
void productDouble(const double& data, const void* n, void* res){
    if(data > *((double*)n))
        *((double*)res) *= data;

}

//Concatenazione stringhe con lunghezza <= n
void concatString(const std::string& data, const void* n, void* res){
    if(data.size() <= (*(int*)n))
        (*(std::string*)res) += data;
}

void specificTestMap(MappableContainer<int>& container){
    int par = 2; 
    container.MapPreOrder(&intTimesPar, &par);
}

void specificTestMap(MappableContainer<double>& container){
    int par = 2;
    container.MapPreOrder(&doublePowerOfPar, &par);
}

void specificTestMap(MappableContainer<std::string>& container){
    int* par;
    container.MapPreOrder(&stringUppercase, par);
}

void intTimesPar(int& data, void* par){
    data = data**((int*)par);
}

void doublePowerOfPar(double& data, void* par){
    if(*((int*)par) == 0)
        data = 1;

    double temp = data;
    for(ulong i = 1; i < *((int*)par); i++)
        data *= temp;
}

void addInverseDoublePowerOfPar(double& data, void* par){
    if(*((int*)par) == 0)
        data = 1;

    data = -data;
    double temp = data;
    for(ulong i = 1; i < *((int*)par); i++)
        data *= temp;
}

void stringUppercase(std::string& data, void* par){
    for(ulong i = 0; i < data.size(); i++)
        data[i] = toupper(data[i]);
    
}

void structureTypeChoiceStack(){
    ulong len;
    std::cout<< "Choose the length of the data structure: "<< std::endl;
    std::cin >> len;

    std::cout << "Pick the stack implementation: \n 1-Vector \n 2-List" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            dataChoiceStackVec(len);
            return;
            break;
        }
        case 2:{
            dataChoiceStackLst(len);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void structureTypeChoiceQueue(){
    ulong len;
    std::cout<< "Choose the length of the data structure: "<< std::endl;
    std::cin >> len;

    std::cout << "Pick the queue implementation: \n 1-Vector \n 2-List" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            dataChoiceQueueVec(len);
            return;
            break;
        }
        case 2:{
            dataChoiceQueueLst(len);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void dataChoiceStackVec(const ulong len){
    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            StackVec<int> stack(intVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        case 2:{
            StackVec<double> stack(doubleVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        case 3:{
            StackVec<std::string> stack(stringVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void dataChoiceStackLst(const ulong len){
    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            StackLst<int> stack(intVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        case 2:{
            StackLst<double> stack(doubleVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        case 3:{
            StackLst<std::string> stack(stringVector(len));
            stackTestChoice(stack);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

void dataChoiceQueueVec(const ulong len){
    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            QueueVec<int> queue(intVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        case 2:{
            QueueVec<double> queue(doubleVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        case 3:{
            QueueVec<std::string> queue(stringVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

void dataChoiceQueueLst(const ulong len){

    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            QueueLst<int> queue(intVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        case 2:{
            QueueLst<double> queue(doubleVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        case 3:{
            QueueLst<std::string> queue(stringVector(len));
            queueTestChoice(queue);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

template<typename Data>
void stackTestChoice(Stack<Data>& stack){
    int choice = 1;
    
    
    while(choice){
        std::cout << "Choose what to do: " << std::endl;
        std::cout << " 1-Inserimento \n 2-Rimozione \n 3-Rimozione con lettura"
        "\n 4-Lettura non distruttiva \n 5-Vuotezza \n 6-Lettura dimensione"
        "\n 7-Svuotamento \n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                Data val;
                std::cout << "Scegliere elemento da inserire: "<< std::endl;
                std::cin >> val;
                stack.Push(val);
                break;
            }
            case 2:{
                try{
                    stack.Pop();
                }
                catch(std::length_error e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    std::cout << "Rimozione con lettura: " << stack.TopNPop() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 4:{
                try{
                    std::cout << "Lettura non distruttiva:" << stack.Top() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 5:{
                if(stack.Empty())
                    std::cout << "La lista è vuota" << std::endl;
                else
                    std::cout << "La lista non è vuota" << std::endl;
                break;
            }
            case 6:{
                std::cout << stack.Size() << std::endl;
                break;
            }
            case 7:{
                stack.Clear();
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }

    }
}

template<typename Data>
void queueTestChoice(Queue<Data>& queue){
    int choice = 1;
    
    
      while(choice){
        std::cout << "Choose what to do: " << std::endl;
        std::cout << " 1-Inserimento \n 2-Rimozione \n 3-Rimozione con lettura"
        "\n 4-Lettura non distruttiva \n 5-Vuotezza \n 6-Lettura dimensione"
        "\n 7-Svuotamento \n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                Data val;
                std::cout << "Inserire il valore: " << std::endl;
                std::cin >> val;
                queue.Enqueue(val);
                break;
            }
            case 2:{
                try{
                    queue.Dequeue();
                }
                catch(std::length_error e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    std::cout << "Rimozione con lettura: " << queue.HeadNDequeue() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 4:{
                try{
                    std::cout << "Lettura non distruttiva:" << queue.Head() << std::endl;
                }
                catch(const std::exception& e){
                    std::cout << "Eccezione: " << e.what() << std::endl;
                }
                break;
            }
            case 5:{
                if(queue.Empty())
                    std::cout << "La lista è vuota" << std::endl;
                else
                    std::cout << "La lista non è vuota" << std::endl;
                break;
            }
            case 6:{
                std::cout << queue.Size() << std::endl;
                break;
            }
            case 7:{
                queue.Clear();
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }

    }
}

void structureTypeChoiceBT(){
    ulong len;
    std::cout<< "Choose the length of the data structure: "<< std::endl;
    std::cin >> len;

    std::cout << "Pick the binarytree implementation: \n 1-Vector \n 2-List \n 3-BST" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            dataChoiceBTVec(len);
            return;
            break;
        }
        case 2:{
            dataChoiceBTLnk(len);
            return;
            break;
        }
        case 3:{
            dataChoiceBST(len);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void dataChoiceBTVec(const ulong len){
    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            BinaryTreeVec<int> tree(intVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        case 2:{
            BinaryTreeVec<double> tree(doubleVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        case 3:{
            BinaryTreeVec<std::string> tree(stringVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void dataChoiceBTLnk(const ulong len){
    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            BinaryTreeLnk<int> tree(intVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        case 2:{
            BinaryTreeLnk<double> tree(doubleVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        case 3:{
            BinaryTreeLnk<std::string> tree(stringVector(len));
            btTestChoice(tree);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

template<typename Data>
void btTestChoice(BinaryTree<Data>& tree){
    int choice = 1;
    if(tree.Empty()){
        std::cout << "L'albero è vuoto, non è possibile effettuare alcuna operazione, qualsiasi operazione "
        "solleverebbe un'eccezione" << std::endl;
        return;
    }
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-Stampa \n 2-Esistenza \n 3-Specific Test Fold \n 4-Specific Test Map"
        "\n 5-Navigazione con iteratori \n 6-Navigazione con puntatori \n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                printBT(tree);
                break;
            }
            case 2:{
                Data val;
                std::cout << "Dammi il valore: ";
                std::cin >> val;
                if(tree.Exists(val))
                    std::cout << "Il valore esiste" << std::endl;
                else
                    std::cout << "Il valore non esiste" << std::endl;
                break;
            }
            case 3:{
                specificTestFold(tree);
                break;
            }
            case 4:{
                specificTestMap(tree);
                break;
            }
            case 5:{
                iteratorChoice(tree);
                break;
            }
            case 6:{
                nodeNavigation(tree);
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

}

template<typename Data>
void nodeNavigation(BinaryTree<Data>& tree){
    int choice = 1;
    typename BinaryTree<Data>::Node* temp = &tree.Root();
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << "\n 1-Accesso all'elemento corrente"
        "\n 2-Figlio sinistro \n 3-Figlio destro\n 4-Esistenza figlio sinistro \n 5-Esistenza figlio destro"
        "\n 6-Modifica elemento corrente \n 0-Indietro" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                std::cout << temp->Element() << std::endl;
                break;
            }
            case 2:{
                try{
                    temp = &temp->LeftChild();
                }
                catch(std::out_of_range e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    temp = &temp->RightChild();
                }
                catch(std::out_of_range e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 4:{
                if(temp->HasLeftChild())
                    std::cout << "Il nodo ha figlio sinistro" << std::endl;
                else
                    std::cout << "Il nodo non ha figlio sinistro" << std::endl;
                break;
            }
            case 5:{
                if(temp->HasRightChild())
                    std::cout << "Il nodo ha figlio destro" << std::endl;
                else
                    std::cout << "Il nodo non ha figlio destro" << std::endl;
                break;
            }
            case 6:{
                Data val;
                std::cout << "Dammi il valore con cui modificare il nodo" << std::endl;
                std::cin >> val;
                temp->Element() = val;
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }
}

template <typename Data>
void printBT(BinaryTree<Data>& tree){
    int choice = 1;
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-PreOrder \n 2-PostOrder \n 3-InOrder \n 4-Breadth \n 0-Indietro" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                int par = 0;
                tree.MapPreOrder(&mapPrint<Data>, &par);
                break;
                return;
            }
            case 2:{
                int par = 0;
                tree.MapPostOrder(&mapPrint<Data>, &par);
                break;
                return;
            }
            case 3:{
                int par = 0;
                tree.MapInOrder(&mapPrint<Data>, &par);
                break;
                return;
            }
            case 4:{
                int par = 0;
                tree.MapBreadth(&mapPrint<Data>, &par);
                break;
                return;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

}

void specificTestFold(BinaryTree<int>& tree){
    int n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const int par = n;
    int acc = 1;
    tree.FoldPreOrder(&productInt, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

void specificTestFold(BinaryTree<double>& tree){
    double n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const double par = n;
    double acc = 0;
    tree.FoldPreOrder(&sumDouble, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

void specificTestFold(BinaryTree<std::string>& tree){
    int n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const int par = n;
    std::string acc = 0;
    tree.FoldPreOrder(&concatString, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

//Prodotto di numeri < n
void productInt(const int& data, const void* n, void* res){
    if(data < *((int*)n))
        *((int*)res) *= data;

}

//Somma di numeri > n
void sumDouble(const double& data, const void* n, void* res){
    if(data > *((double*)n))
        *((double*)res) += data;

}

void specificTestMap(BinaryTree<int>& tree){
    int par = 3;
    tree.MapPreOrder(&intTimesPar, &par);
}

void specificTestMap(BinaryTree<double>& tree){
    int par = 3;
    tree.MapPreOrder(&doublePowerOfPar, &par);
}

void specificTestMap(BinaryTree<std::string>& tree){
    std::cout << "Dammi la stringa: " << std::endl;
    std::string par;
    std::cin >> par;
    tree.MapPreOrder(&stringHeadConcat, &par);
}

void stringHeadConcat(std::string& data, void* par){
    data = *((std::string*)par) + data;
    
}

template<typename Data>
void iteratorChoice(BinaryTree<Data>& tree){
    int choice = 1;

    std::cout << "Choose the iterator: \n" << std::endl;
    std::cout << " 1-PreOrder \n 2-PostOrder \n 3-InOrder \n 4-Breadth" << std::endl;
    std::cin >> choice;
    switch(choice){
        case 1:{
            BTPreOrderIterator<Data>iterator(tree);
            iteratorVisit(iterator);
            break;
        }
        case 2:{
            BTPostOrderIterator<Data>iterator(tree);
            iteratorVisit(iterator);
            break;
        }
        case 3:{
            BTInOrderIterator<Data>iterator(tree);
            iteratorVisit(iterator);
            break;
        }
        case 4:{
            BTBreadthIterator<Data>iterator(tree);
            iteratorVisit(iterator);
            break;
        }
        case 0:{
                return;
            break;
        }
        default:
            std::cout << "Invalid input" << std::endl;
    }
    

}

template<typename Data>
void iteratorVisit(ForwardIterator<Data>& iterator){
    int choice = 1;
    
    while(choice){
        std::cout << "Choose what to do: \n" << std::endl;
        std::cout << " 1-Accesso all'elemento \n 2-Prossimo elemento "<< std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                try{
                    std::cout << *iterator << std::endl;
                }
                catch(const std::out_of_range e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 2:{
                try{
                    ++iterator;
                }
                catch(const std::out_of_range e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }

    }
}

void dataChoiceBST(const ulong len){
    std::cout << "Pick the data type: \n1-Int \n2-Double \n3-String" << std::endl;
    uint choice = 0;
    std::cin >> choice;
    switch(choice){
        case 1:{
            BST<int> bst(intVector(len));
            bstTestChoice(bst);
            break;
        }
        case 2:{
            BST<double> bst(doubleVector(len));
            bstTestChoice(bst);
            break;
        }
        case 3:{
            BST<std::string> bst(stringVector(len));
            bstTestChoice(bst);
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

template<typename Data>
void bstTestChoice(BST<Data>& bst){
    int choice = 1;
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-Stampa \n 2-Esistenza \n 3-Specific Test Fold \n 4-Specific Test Map"
        "\n 5-Inserimento \n 6-Eliminazione \n 7-Operazioni con max e min \n 8-Operazioni con succ e pred"
        "\n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                printBT(bst);
                break;
            }
            case 2:{
                Data val;
                std::cout << "Dammi il valore: ";
                std::cin >> val;
                if(bst.Exists(val))
                    std::cout << "Il valore esiste" << std::endl;
                else
                    std::cout << "Il valore non esiste" << std::endl;
                break;
            }
            case 3:{
                specificTestFold(bst);
                break;
            }
            case 4:{
                specificTestMap(bst);
                break;
            }
            case 5:{
                Data val {};
                std::cout << "Dammi il valore da inserire: ";
                std::cin >> val;
                bst.Insert(val);
                break;
            }
            case 6:{
                Data val {};
                std::cout << "Dammi il valore da rimuovere: ";
                std::cin >> val;
                bst.Remove(val);
                break;
            }
            case 7:{
                bstMaxMin(bst);
                break;
            }
            case 8:{
                bstPredSucc(bst);
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

}

template<typename Data>
void bstMaxMin(BST<Data>& bst){
    int choice = 1;
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-Lettura Min \n 2-Rimozione Min \n 3-Rimozione e Lettura Min \n "
        "4-Lettura Max \n 5-Rimozione Max \n 6-Rimozione e Lettura Max \n 0-Indietro" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                try{
                    std::cout << bst.Min() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 2:{
                try{
                    bst.RemoveMin();
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    std::cout << bst.MinNRemove() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 4:{
                try{
                    std::cout << bst.Max() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 5:{
                try{
                    bst.RemoveMax();
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 6:{
                try{
                    std::cout << bst.MaxNRemove() << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

}

template<typename Data>
void bstPredSucc(BST<Data>& bst){
    int choice = 1;
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-Lettura Predecessore \n 2-Rimozione Predecessore \n 3-Rimozione e Lettura Predecessore \n "
        "4-Lettura Successore \n 5-Rimozione Successore \n 6-Rimozione e Lettura Successore \n 0-Indietro" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui leggere il predecessore: ";
                    std::cin >> val;
                    std::cout << bst.Predecessor(val) << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 2:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui rimuovere il predecessore: ";
                    std::cin >> val;
                    bst.RemovePredecessor(val);
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 3:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui leggere e rimuovere il predecessore: ";
                    std::cin >> val;
                    std::cout << bst.PredecessorNRemove(val) << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 4:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui leggere il successore: ";
                    std::cin >> val;
                    std::cout << bst.Successor(val) << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 5:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui rimuovere il successore: ";
                    std::cin >> val;
                    bst.RemoveSuccessor(val);
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 6:{
                try{
                    Data val {};
                    std::cout << "Dammi il valore di cui leggere e rimuovere il successore: ";
                    std::cin >> val;
                    std::cout << bst.SuccessorNRemove(val) << std::endl;
                }
                catch(std::length_error e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

}

void structureTypeChoiceMatrix(){
    ulong rows, cols;
    std::cout<< "Choose the number of rows: "<< std::endl;
    std::cin >> rows;

    std::cout<< "Choose the number of cols: "<< std::endl;
    std::cin >> cols;

    std::cout << "Pick the matrix implementation: \n 1-MatrixVec \n 2-MatrixCSR" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            dataChoiceMatrixVec(rows, cols);
            return;
            break;
        }
        case 2:{
            dataChoiceMatrixCSR(rows, cols);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    
}

void dataChoiceMatrixVec(const ulong rows, const ulong cols){
    ulong size;
    std::cout << "Quanti elementi vuoi siano presenti?" << std::endl;
    std::cin >> size;

    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            MatrixVec<int> matrix(intMatrixVec(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        case 2:{
            MatrixVec<double> matrix(doubleMatrixVec(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        case 3:{
            MatrixVec<std::string> matrix(stringMatrixVec(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

void dataChoiceMatrixCSR(const ulong rows, const ulong cols){
    ulong size;
    std::cout << "Quanti elementi vuoi siano presenti?" << std::endl;
    std::cin >> size;

    std::cout << "Pick the data type: \n 1-Int \n 2-Double \n 3-String" << std::endl;
    int choice = 1;
    
    std::cin >> choice;
    switch(choice){
        case 1:{
            MatrixCSR<int> matrix(intMatrixCSR(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        case 2:{
            MatrixCSR<double> matrix(doubleMatrixCSR(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        case 3:{
            MatrixCSR<std::string> matrix(stringMatrixCSR(rows, cols, size));
            matrixTestChoice(matrix);
            return;
            break;
        }
        default:
            std::cout << "Invalid choice" << std::endl;
    }
}

template<typename Data>
void matrixTestChoice(Matrix<Data>& matrix){
    int choice = 1;
    
    while(choice){
        std::cout << "\nChoose what to do: \n" << std::endl;
        std::cout << " 1-Stampa preorder \n 2-Stampa post order \n 3-Esistenza valore \n 4-Specific Test Fold"
        "\n 5-Specific Test Map \n 6-Esistenza cella \n 7-Lettura \n 8-Scrittura \n 9-Ridimensioamento righe"
        "\n 10-Ridimensionamento colonne\n 0-Esci" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1:{
                printPreOrder(matrix);
                break;
            }
            case 2:{
                printPostOrder(matrix);
                break;
            }
            case 3:{
                Data val;
                std::cout << "Inserire il valore di cui si desidera verificare l'esistenza" << std::endl;
                std::cin >> val;
                matrix.Exists(val);
                break;
            }
            case 4:{
                specificTestFold(matrix);
                break;
            }
            case 5:{
                specificTestMap(matrix);
                break;
            }
            case 6:{
                ulong row, col;
                std::cout << "Dammi la riga: " << std::endl;
                std::cin >> row;
                std::cout << "Dammi la colonna: " << std::endl;
                std::cin >> col;
                if(matrix.ExistsCell(row, col))
                    std::cout << "La cella esiste" << std::endl;
                else
                    std::cout << "La cella non esiste" << std::endl;
                break;
            }
            case 7:{
                ulong row, col;
                std::cout << "Dammi la riga: " << std::endl;
                std::cin >> row;
                std::cout << "Dammi la colonna: " << std::endl;
                std::cin >> col;
                try{
                    std::cout << const_cast<const Matrix<Data>*>(&matrix)->operator()(row, col) << std::endl;
                }
                catch(std::exception e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 8:{
                ulong row, col;
                std::cout << "Dammi la riga: " << std::endl;
                std::cin >> row;
                std::cout << "Dammi la colonna: " << std::endl;
                std::cin >> col;
                Data val;
                std::cout << "Dammi il valore da inserire" << std::endl;
                std::cin >> val;
                try{
                    matrix(row, col) = val;
                }
                catch(std::exception e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 9:{
                ulong newrows;
                std::cout << "Dammi il nuovo numero di righe" << std::endl;
                std::cin >> newrows;
                matrix.RowResize(newrows);
                break;
            }
            case 10:{
                ulong newcols;
                std::cout << "Dammi il nuovo numero di colonne" << std::endl;
                std::cin >> newcols;
                matrix.ColumnResize(newcols);
                break;
            }
            case 0:{
                return;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }
}

MatrixVec<int> intMatrixVec(const ulong rows, const ulong cols, const ulong size){
    MatrixVec<int> matrix = MatrixVec<int>(rows, cols); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 200);
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    for(ulong i = 0; i < size; i++){
        ulong x = r(gen), y = c(gen);
        if(matrix(x, y) == 0)
            matrix(x, y) = dist(gen);
        else
            i--;
    }
    return matrix;
}

MatrixVec<double> doubleMatrixVec(const ulong rows, const ulong cols, const ulong size){
    MatrixVec<double> matrix = MatrixVec<double>(rows, cols); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    std::uniform_real_distribution<double> dist(0, 200);
    for(ulong i = 0; i < size; i++){
        ulong x = r(gen), y = c(gen);
        if(matrix(x, y) == 0)
            matrix(x, y) = dist(gen);
        else
            i--;
    }
    return matrix;
}

MatrixVec<std::string> stringMatrixVec(const ulong rows, const ulong cols, const ulong size){
    MatrixVec<std::string> matrix = MatrixVec<std::string>(rows, cols);

    std::string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10);
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    std::uniform_int_distribution<int> randPos(0, table.size()-1);

    std::string temp;
    for(ulong i = 0; i < size; i++){
        temp = "";
        uint newLen = dist(gen);
        for(ulong j = 0; j < newLen; j++){
            temp += table[randPos(gen)];
        }
        ulong x = r(gen), y = c(gen);
        if(matrix(x, y) == "")
            matrix(x, y) = temp;
        else
            i--;
        
    }

    return matrix;
}

MatrixCSR<int> intMatrixCSR(const ulong rows, const ulong cols, const ulong size){
    MatrixCSR<int> matrix = MatrixCSR<int>(rows, cols); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    std::uniform_int_distribution<int> dist(0, 200);
    for(ulong i = 0; i < size; i++){
        ulong x = r(gen), y = c(gen);
        if(!matrix.ExistsCell(x, y))
            matrix(x, y) = dist(gen);
        else
            i--;
    }
    return matrix;
}

MatrixCSR<double> doubleMatrixCSR(const ulong rows, const ulong cols, const ulong size){
    MatrixCSR<double> matrix = MatrixCSR<double>(rows, cols); 
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    std::uniform_real_distribution<double> dist(0, 200);
    for(ulong i = 0; i < size; i++){
        ulong x = r(gen), y = c(gen);
        if(!matrix.ExistsCell(x, y))
            matrix(x, y) = dist(gen);
        else
            i--;
    }
    return matrix;
}

MatrixCSR<std::string> stringMatrixCSR(const ulong rows, const ulong cols, const ulong size){
    MatrixCSR<std::string> matrix = MatrixCSR<std::string>(rows, cols); 

    std::string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> r(0, rows-1);
    std::uniform_int_distribution<int> c(0, cols-1);
    std::uniform_int_distribution<int> dist(1, 10);
    std::uniform_int_distribution<int> randPos(0, table.size()-1);
    
    std::string temp;
    for(ulong i = 0; i < size; i++){
        temp = "";
        uint newLen = dist(gen);
        for(ulong j = 0; j < newLen; j++){
            temp += table[randPos(gen)];
        }
        ulong x = r(gen), y = c(gen);
        if(!matrix.ExistsCell(x, y))
            matrix(x, y) = temp;
        else
            i--;
    }
    return matrix;
}

void specificTestFold(Matrix<int>& matrix){
    int n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const int par = n;
    int acc = 1;
    matrix.FoldPreOrder(&productInt, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

void specificTestFold(Matrix<double>& matrix){
    double n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const double par = n;
    double acc = 0;
    matrix.FoldPreOrder(&sumDouble, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

void specificTestFold(Matrix<std::string>& matrix){
    int n;
    std::cout << "Dammi il valore n: " << std::endl;
    std::cin >> n;
    const int par = n;
    std::string acc = 0;
    matrix.FoldPreOrder(&concatString, &par, &acc);
    std::cout << "Risultato: " << acc << std::endl;
}

void specificTestMap(Matrix<int>& matrix){
    int par = 2;
    matrix.MapPreOrder(&intTimesPar, &par);
}

void specificTestMap(Matrix<double>& matrix){
    int par = 3;
    matrix.MapPreOrder(&addInverseDoublePowerOfPar, &par);
}

void specificTestMap(Matrix<std::string>& matrix){
    std::cout << "Dammi la stringa: " << std::endl;
    std::string par;
    std::cin >> par;
    matrix.MapPreOrder(&stringHeadConcat, &par);
}
