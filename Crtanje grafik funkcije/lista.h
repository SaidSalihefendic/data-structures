#ifndef LISTA_H
#define LISTA_H


template<class Type>
class List
{
public:
    struct node
    {
        Type data;
        node* next;
        node* prev;

        node(node* prev, Type data, node* next) : prev{prev}, data{data}, next{next} {}
    };
private:
    node* head;
    node* tail;
    int length;
public:
            //Constructors and destructor
        List();
        List(List<Type>& copyList);
        ~List();

            //Adding functions
        void pushFront(Type data);
        void pushBack(Type data);
        node* Insert(Type data, node* current);

            //Accessors
        node* Begin() { return head->next; };
        node* End(){ return tail; };

            //Delete Functions
        node* popFront(){ return Erase(head->next); }
        node* popBack() { return Erase(tail->prev); }
        node* Erase(node* pointer);
        void Clear();

            //Access functions
        void processList(void(*func)(Type));

};

#endif // LISTA_H

///>>>>>>>>>>>>>>>>>>>>>>>>>>CONSTRUCTORS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
List<Type>::List() : length(0)
{
    head = new node(nullptr, Type{}, nullptr);
    tail = new node(head, Type{}, nullptr);
    head->next = tail;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
List<Type>::List(List<Type>& copyList) : List()
{
    node* current = copyList.Begin();

    while(current != copyList.End())
    {
        this->pushBack(current->data);
        current = current->next;
    }//end while
}
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
List<Type>::~List()
{
    this->Clear();
    delete head;
    delete tail;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
void List<Type>::pushFront(Type data)
{
    head->next = head->next->prev = new node(head, data, head->next);
    length++;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
void List<Type>::pushBack(Type data)
{
    tail->prev = tail->prev->next = new node(tail->prev, data, tail);
    length++;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
void List<Type>::processList(void(*func)(Type))
{
    node* current = head->next;

    while(current != tail)
    {
        func(current->data);
        current = current->next;
    }//end while
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
typename List<Type>::node* List<Type>::Erase(List<Type>::node* pointer)
{
    if(pointer == nullptr || pointer == head || pointer == tail) throw "Can't erase null pointers";

        //we need to return a pointer to the next node
    node* temp_pointer = pointer->next;

        //Relinking
    pointer->prev->next = pointer->next;
    pointer->next->prev = pointer->prev;

    delete pointer;
    length--;

    return temp_pointer;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
void List<Type>::Clear()
{
    node* current = this->Begin();

    while(current != this->tail)
    {
        current = Erase(current);
    }//end while
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class Type>
typename List<Type>::node* List<Type>::Insert(Type data, typename List<Type>::node* current)
{
    if(current == nullptr || current == head) throw "Can't add to the list!";

    current->prev = current->prev->next = new node(current->prev, data, current);

    length++;
    return current->prev;
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
