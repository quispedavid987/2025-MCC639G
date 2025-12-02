#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include "types.h"
#include<utility>
#include<iostream> //**LIBRERIAS ADICIONALES


template <typename T>
class CLinkedList; //****CORRECCION
template <typename T>
class LLNode{
private:
    using    Type = T;
    friend   class CLinkedList<T>; //**Solo CLinkedLiist puede modificar el private
    Type     m_data; //**Dato en el nodo
    Ref      m_ref; //**Referencia del nodo
    LLNode<T>    *m_pNext = nullptr; //**Puntero al siguiente nodo

public:
    LLNode(Type &elem, Ref ref, LLNode<T> *pNext = nullptr) // constructor, el puntero al siguiente es nullptr
        : m_data(elem), m_ref(ref), m_pNext(pNext){ //PARAMETRO REF
    }
    Type   GetData()    { return m_data;     } //METODOS
    Ref    GetRef()     { return m_ref;     }
    Type  &GetDataRef() { return m_data;     }
    LLNode<T> * GetNext()    { return m_pNext;    } //DE NODE A LLNODE<T>
    LLNode<T> *&GetNextRef() { return m_pNext;    }
};

template <typename T>
class CLinkedList{
private:
    using Type = T; 
    using Node = LLNode<Type>  ; //typename NO NECESARIO
    Node *m_pHead = nullptr;
public:
    // Constructor
    CLinkedList();
    // TODO: Constructor Copia
    CLinkedList(CLinkedList &other);
    CLinkedList& operator = (CLinkedList &other);

    // TODO: Move contructor
    CLinkedList(CLinkedList &&other);
    CLinkedList& operator = (CLinkedList &&other);

    // Destructor seguro
    virtual ~CLinkedList();

    void Insert(Type &elem, Ref ref);

    template<typename P> //INSERCION
    friend std::ostream& operator<<(std::ostream& os, CLinkedList<P>& list);
private:
    // TODO: Implementar
    void InternalInsert(Node *&rParent, Type &elem, Ref ref);
    void Clear();
    void CopyFrom(CLinkedList &other);
};

template <typename T>
void CLinkedList<T>::Insert(Type &elem, Ref ref){
    InternalInsert(m_pHead, elem, ref);
}

template <typename T>
void CLinkedList<T>::InternalInsert(Node *&rParent, Type &elem, Ref ref){
    if( !rParent || elem < rParent->GetDataRef() ){
        rParent = new Node(elem, ref, rParent);
        return;
    }
    // Tail recursion
    InternalInsert(rParent->GetNextRef(), elem, ref);
}

template <typename T>
CLinkedList<T>::CLinkedList() : m_pHead(nullptr)
{
}

//IMPLEMENT CONST COPIA
template <typename T>
CLinkedList<T>::CLinkedList(CLinkedList &other) : m_pHead(nullptr)
{
    CopyFrom(other);
}

//IMPLEMENT MOVE CONST
template <typename T>
CLinkedList<T>::CLinkedList(CLinkedList &&other)
    : m_pHead(other.m_pHead)
{
    other.m_pHead = nullptr;
}

//ASIG POR COPIA
template <typename T>
CLinkedList<T>& CLinkedList<T>::operator=(CLinkedList &other){
    if (this != &other){
        Clear();
        CopyFrom(other);
    }
    return *this;
}

//OPERADOR ASIG POR MOV
template <typename T>
CLinkedList<T>& CLinkedList<T>::operator=(CLinkedList &&other) {
    if (this != &other){
        Clear();
        m_pHead = other.m_pHead;
        other.m_pHead = nullptr;
    }
    return *this;
}

//LIMPIAR LISTA
template <typename T> 
void CLinkedList<T>::Clear(){
    Node *current = m_pHead;
    while (current){
        Node *next = current->m_pNext;
        delete current;
        current = next;
    }
    m_pHead = nullptr;
}

//COPIAR DESDE OTRA LISTA
template <typename T>
void CLinkedList<T>::CopyFrom(CLinkedList &other) {
    if (!other.m_pHead){
        m_pHead = nullptr;
        return;
    }

    Node *otherCurent = other.m_pHead;
    Node **current = &m_pHead;

    while (otherCurent) {
        *current = new Node(otherCurent->m_data, otherCurent->m_ref);
        current = &((*current)->m_pNext);
        otherCurent = otherCurent->m_pNext;
    }
}


template <typename T>
CLinkedList<T>::~CLinkedList()
{
    Clear();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, CLinkedList<T>& list){
    typename CLinkedList<T>::Node *current = list.m_pHead;
    os <<"[";
    while (current) {
        os << "(" << current->GetData() << "," << current->GetRef() << ")";
        if (current->GetNext()){
            os << "->";
        }
        current = current->GetNext();
    }
    os << "]";
    return os;
}


void DemoLinkedList();

#endif // __LINKEDLIST_H__