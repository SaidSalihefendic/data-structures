#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include<iomanip>
using namespace std;

class OutOfRangeException : public exception
{

};

class NonExistingElementException : public exception
{

};

template<class T>
class List
{
public:
        //CONSTRUCTORS
    List();
    List(int capacity);
    List(const List& lista);

        //DESTRUCTOR
    ~List();

        //MODIFIERS
    void push_back_(T key);
    void push_front_(T key);
    void pop_back_();
    void pop_front_();
    void insertKth(T key, int position);
    void swap_(int position1, int position2);
    void InsertionSort();
    void erase_(int index);
    void reverse_();

        //ELEMENT ACCESS
    void Front(); //Must be capital because of namespace
    void Back();
    void Next();
    void Prev();

        //GETTERS
    int get_current_position() const;
    int get_num_of_elements() const;
    int get_capacity() const;

        //OPERATIONS
    void remove_(T key);

        //OTHER OPERATIONS
    void print() const;
    void print_current_element() const;

        //OPERATORS
    T& operator[](int index);
    List& operator =(const List& lista);

private:
        //Multiarray representation
    int* next;
    T* key;
    int* prev;

        //Helpful variables
    int free;
    int front_;
    int back_;
    int current_position;
    int capacity;
    int num_of_elements;

        //Private functions
    void __find_new_free();
    void __raise_capacity();
};

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
List<T>::List() : capacity(10), free(0), front_(-1), back_(-1), num_of_elements(0), current_position(-1)
{
    next = new int[capacity];
    key = new T[capacity];
    prev = new int[capacity];

        //-1 for NULL dummy
    for(int i = 0; i < capacity; i++)
    {
        next[i] = -1;
        prev[i] = -1;
    }//end for
}//end constructor

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
List<T>::List(const List& lista)
{
    this->capacity = lista.capacity;
    this->free = lista.free;
    this->front_ = lista.front_;
    this->back_ = lista.back_;
    this->num_of_elements = lista.num_of_elements;
    this->current_position = lista.current_position;

    this->next = new int[capacity];
    this->key = new T[capacity];
    this->prev = new int[capacity];

    for(int i = 0; i < this->capacity; i++)
    {
        this->next[i] = lista.next[i];
        this->key[i] = lista.key[i];
        this->prev[i] = lista.prev[i];
    }//end for
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
List<T>::~List()
{
    delete[] next;
    delete[] key;
    delete[] prev;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
List<T>::List(int capacity) : capacity(capacity), free(0), front_(-1), back_(-1), num_of_elements(0)
{
    next = new int[capacity];
    key = new T[capacity];
    prev = new int[capacity];

        // -1 for NULL dummy
    for(int i = 0; i < capacity; i++)
    {
        next[i] = -1;
        prev[i] = -1;
    }//end for
}//end constructor

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>
void List<T>::print() const
{
    ///A way of representing our list operator

    cout << setw(6) << "NEXT: ";
    for(int i = 0; i < this->capacity; i++)
    {
        if(prev[i] != -1 && next[i] != -1 || i == front_ || i == back_)
            cout << setw(3) << this->next[i] << " | ";
        else
            cout << " " << " | ";
    }//end for
    cout << endl;

    cout << setw(6) << "KEY: ";
    for(int i = 0; i < this->capacity; i++)
    {
        if(prev[i] != -1 && next[i] != -1 || i == front_ || i == back_)
            cout << setw(3) << this->key[i] << " | ";
        else
            cout << " " << " | ";
    }

    cout << endl;

    cout << setw(6) << "PREV: ";
    for(int i = 0; i < this->capacity; i++)
    {
        if(prev[i] != -1 && next[i] != -1 || i == front_ || i == back_)
            cout << setw(3) << this->prev[i] << " | ";
        else
            cout << " " << " | ";
    }

    cout << endl;
} //end print()


///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
int List<T>::get_current_position() const
{
    return current_position;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
int List<T>::get_num_of_elements() const
{
    return num_of_elements;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
int List<T>::get_capacity() const
{
    return capacity;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::push_back_(T key)
{
        ///Puts a key as the tail of list
        //Certain possibility that free will be some number other than zero, despite the empty list
    if(back_ == -1)
    {
        front_ = free;
        back_ = free;
        this->next[free] = -1;
        this->key[free] = key;
        this->prev[free] = -1;
        num_of_elements++;
        current_position = front_;
    }//end if

    else
    {
            //Inserting at the end of list, only adding key and prev to the previous tail
        this->next[free] = -1;
        this->key[free] = key;
        this->prev[free] = this->back_;

        num_of_elements++;
            //Now the previous tail has a next
        this->next[back_] = free;
        this->back_ = free;
    }//end else

    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::push_front_(T key)
{
        ///Puts a key as the head of list
        //Certain possibility that free will be some number other than zero, despite the empty list
    if(front_ == -1)
    {
        front_ = free;
        back_ = free;
        this->next[free] = -1;
        this->key[free] = key;
        this->prev[free] = -1;
        num_of_elements++;
        current_position = front_;
    }//end if

    else
    {
            //Inserting at the beginning of list, only adding key and next to the previous head
        this->next[free] = this->front_;
        this->key[free] = key;
        this->prev[free] = -1;

        num_of_elements++;

            //Now the previous head has a prev and we update current position pointer
        this->prev[front_] = free;
        this->front_ = free;
        current_position = front_;
    }//end else

    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::__find_new_free()
{
        //special case
    if(num_of_elements == 0)
    {
        free = 0;
        return;
    }
        //Searchin for new free, if there isn't any, we will raise capacity
    bool found_new_free = false;
    for(int i = 0; i < capacity; i++)
    {
        if(i != free && i != front_ && i != back_ && next[i] == -1 && prev[i] == -1)
        {
            found_new_free = true;
            free = i;
            break;
        }//end if
    }//end for

        //If we haven't found any new free spot, we will raise the capacity and find new free
    if(!found_new_free)
    {
        this->__raise_capacity();
        __find_new_free();
    }//end if
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::__raise_capacity()
{
        ///Function that doubles the original capacity
    int* temp_next = new int[capacity * 2];
    T* temp_key = new T[capacity * 2];
    int* temp_prev = new int[capacity * 2];

    for(int i = 0; i < capacity * 2; i++)
    {
        temp_next[i] = -1;
        temp_prev[i] = -1;
    }//end for

        //parsing data into new arrays of double the initial capacity
    for(int i = 0; i < capacity; i++)
    {
        temp_next[i] = next[i];
        temp_key[i] = key[i];
        temp_prev[i] = prev[i];
    }//end for

        //save the number of capacity
    capacity = capacity * 2;
        //releasing memory
    delete[] next;
    delete[] key;
    delete[] prev;

        //Now assign the new arrays to our pointers
    next = temp_next;
    key = temp_key;
    prev = temp_prev;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::Next()
{
        ///Sets current position to its next element
    if(next[current_position] == -1) throw OutOfRangeException();
    else current_position = next[current_position];
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::Front()
{
        ///Sets current position to its head element
    if(front_ == -1) throw OutOfRangeException();
    else
        current_position = front_;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::Back()
{
        ///Sets current position to its tail element
    if(back_ == -1) throw OutOfRangeException();
    else
        current_position = back_;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::Prev()
{
        ///Sets current position to its previous element
    if(prev[current_position] == - 1) throw OutOfRangeException(); //Implementirati svoje izuzetke
    else
        current_position = prev[current_position];
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::print_current_element() const
{
        ///Prints data about the current element
    cout << " | " << setw(3) << next[current_position] << " | " << endl;
    cout << " | " << setw(3) << key[current_position] << " | " << endl;
    cout << " | " << setw(3) << prev[current_position] << " | " << endl;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::insertKth(T key, int position)
{
            ///Inserting an element in the k-th position
            //test if position is valid for the list
        if(position > num_of_elements || position < 0)
        {
            throw OutOfRangeException();
        }//end if

            //restarting the current position to list head
        Front();

            //special cases, at the head and tail of list
        if(position == 0)
        {
            push_front_(key);
            return;
        }//end if

        else if(position == num_of_elements)
        {
            push_back_(key);
            return;
        }//end else if

            //we need to get to the (k - 1)th element
        for(int i = 0; i < position - 1; i++)
        {
            Next();
        }//end for

            //now declaring the new next and prev values with the next free spot
        int temp_next = next[current_position]; //help variable to keep the index to the next element

        next[current_position] = free;
        prev[temp_next] = free;

        this->next[free] = temp_next;
        this->key[free] = key;
        this->prev[free] = current_position;
        num_of_elements++;

        __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::remove_(T key)
{
    if(num_of_elements <= 0)
        throw NonExistingElementException();

        //Trazimo sada taj key
    Front();
    int position = -1;
    for(int i = 0; i < num_of_elements; i++)
    {
        if(this->key[current_position] == key)
        {
            position = current_position;
            break;
        }//end if
        Next();
    }//end for

        //If we haven't found an element, throw a nonexisting value exception
    if(position == -1)
    {
        throw NonExistingElementException();
    }

    //Special cases, if it's about list's head or tail
    if(prev[position] == -1)
    {
        pop_front_();
        return;
    }
    else if(next[position] == -1)
    {
        pop_back_();
        return;
    }//end if-else

        //helping variables
    int temp_next = next[position];
    int temp_prev = prev[position];

        //reallocation
    next[temp_prev] = temp_next;
    prev[temp_next] = temp_prev;

        //"deallocation"
    next[position] = -1;
    prev[position] = -1;
    Front();

    num_of_elements--;
    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::pop_back_()
{
    if(back_ == -1)
    {
        throw OutOfRangeException();
    }
    int temp_back = prev[back_];

    next[prev[back_]] = -1;

    this->next[back_] = -1;
    this->prev[back_] = -1;

    back_ = temp_back;
    num_of_elements--;

        //if we have deleted all members, then we don't have front nor back anymore
    if(num_of_elements == 0)
    {
        front_ = -1;
        back_ = -1;
    }

    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::pop_front_()
{
    if(front_ == -1)
    {
        throw OutOfRangeException();
    }
    int temp_front = next[front_];

    prev[next[front_]] = -1;

    this->next[front_] = -1;
    this->prev[front_] = -1;

    front_ = temp_front;
    num_of_elements--;
    if(num_of_elements == 0)
    {
        front_ = -1;
        back_ = -1;
    }
    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::swap_(int position1, int position2)
{
    if(position1 < 0 || position2 < 0 || position1 >= num_of_elements || position2 >= num_of_elements)
    {
        throw OutOfRangeException();
    }//end if

    int relative_position1;
    int relative_position2;

    Front(); //from the beginning of the list
    for(int i = 0; i < position1; i++)
        Next(); ////updating current position
    relative_position1 = current_position;

    Front(); //from the beginning of the list
    for(int i = 0; i < position2; i++)
        Next(); //updating current position
    relative_position2 = current_position;

    int temp_key = key[relative_position1];
    key[relative_position1] = key[relative_position2];
    key[relative_position2] = temp_key;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
T& List<T>::operator[](int index)
{
    if(index < 0 || index >= num_of_elements)
    {
        throw OutOfRangeException();
    }//end if

        //we need to come to that element, so we use already builtin functions
    Front(); //resetting current position
    for(int i = 0; i < index; i++)
    {
        Next();
    }

    int temp_position = current_position;
    Front();

    return key[temp_position];
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::InsertionSort()
{
    if(num_of_elements <= 0)
        throw NonExistingElementException();

    ///Sorting the list, Insertion Sort algorithm
    for(int i = 1; i < num_of_elements; i++)
    {
        int j = i - 1;
        int key = (*this)[i];

        while(j >= 0 && (*this)[j] > key)
        {
            (*this)[j + 1] = (*this)[j];
            j = j - 1;
        }//end while

        (*this)[j + 1] = key;
    }//end for
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
List<T>& List<T>::operator =(const List<T>& lista)
{
    if(this == &lista) return *this;

    this->~List(); //ponistavamo nizove do sada sto smo imali

    this->capacity = lista.capacity;
    this->free = lista.free;
    this->front_ = lista.front_;
    this->back_ = lista.back_;
    this->num_of_elements = lista.num_of_elements;
    this->current_position = lista.current_position;

    this->next = new int[capacity];
    this->key = new T[capacity];
    this->prev = new int[capacity];

    for(int i = 0; i < this->capacity; i++)
    {
        this->next[i] = lista.next[i];
        this->key[i] = lista.key[i];
        this->prev[i] = lista.prev[i];
    }//end for

    return *this;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::erase_(int index)
{
    if(index < 0 || index >= num_of_elements)
    {
        //throw -1;
        return;
    }//end if

    Front(); //reset the current position
    for(int i = 0; i < index; i++)
        Next();

    remove_(key[current_position]);
    Front();
    __find_new_free();
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
void List<T>::reverse_()
{
    if(num_of_elements <= 0)
        throw NonExistingElementException();

    Front();
    for(int i = 0; i < num_of_elements / 2; i++)
    {
        swap_(i, num_of_elements - 1 - i);
    }//end for
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------


#endif // LISTA_H


/*
//            Back();
//            next[current_position] = free;
//
//            this->next[free] = -1;
//            this->key[free] = key;
//            this->prev[free] = back_;
//            back_ = free;
//
//            __find_new_free();
//            num_of_elements++;

//            prev[current_position] = free;
//
//            this->next[free] = front_;
//            this->key[free] = key;
//            this->prev[free] = -1;
//            front_ = free;
//
//            __find_new_free();
//            num_of_elements++;

*/
