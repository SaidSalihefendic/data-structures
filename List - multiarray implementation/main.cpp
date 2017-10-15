#include <iostream>
#include "list.h"
#include<cmath>
#include<cstdlib>

using namespace std;

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
List<T> MergeSort(List<T> lista, int a, int b)
{
    cout << "Usli smo u funkciju!" << a << ", " << b << endl;
    if(a == b)
    {
        List<T> podlista(2);
        podlista.push_back_(lista[a]);
        return podlista;
    }

    int sredina =  (a + b) / 2;

    List<T> polovica1 = MergeSort(lista, a, sredina);
    List<T> polovica2 = MergeSort(lista, sredina + 1, b);

    return Merge(polovica1, polovica2);
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
List<T> Merge(List<T>& lista1, List<T>& lista2)
{
    List<T> nova_lista(lista1.get_capacity() + lista2.get_capacity()); //pravimo listu kapaciteta sadrzana od obe liste

    int for_list1 = 0;
    int for_list2 = 0;
    while(for_list1 != lista1.get_num_of_elements() && for_list2 != lista2.get_num_of_elements())
    {
        if(lista1[for_list1] <= lista2[for_list2])
            nova_lista.push_back_(lista1[for_list1++]);
        else
            nova_lista.push_back_(lista2[for_list2++]);
    }//end while
    for(int i = for_list1; i < lista1.get_num_of_elements(); i++)
        nova_lista.push_back_(lista1[i]);

    for(int i = for_list2; i < lista2.get_num_of_elements(); i++)
        nova_lista.push_back_(lista2[i]);

    return nova_lista;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    List<int> lista(5);

    while(true)
    {
        int choice;
        cout << "Vasa lista sada: " << endl;
        lista.print();

        cout << endl << endl;
        cout << "Poredak u vasoj listi trenutno sada: " << endl << endl;
        for(int i = 0; i < lista.get_num_of_elements(); i++)
        {
            cout << lista[i];
            if(i != lista.get_num_of_elements() - 1)
                cout << ", ";
        }
        cout << endl << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Akcije koje zelite uraditi: " << endl;
        cout << "1. push_front_()" << endl;
        cout << "2. push_back_()" << endl;
        cout << "3. pop_front_()" << endl;
        cout << "4. pop_back_()" << endl;
        cout << "5. remove_()" << endl;
        cout << "6. erase_()" << endl;
        cout << "7. InsertionSort()" << endl;
        cout << "8. dobiti odredjen broj iz liste" << endl;
        cout << "9. MergeSort()" << endl;
        cout << "10. insertKth()" << endl;
        cout << "11. swap()" << endl;
        cout << "12. reverse()" << endl;
        cout << "Odluka: ";
        cin >> choice;
        cout << "--------------------------------------------------------" << endl;
        int number;
        switch(choice)
        {

        case 1:
            cout << "Broj koji zelite unijeti za push_front_(): ";
            cin >> number;
            lista.push_front_(number);
            break;

        case 2:
            cout << "Broj koji zelite unijeti za push_back_(): ";
            cin >> number;
            lista.push_back_(number);
            break;

        case 3:
            try
            {
                lista.pop_front_();
                break;
            } catch(OutOfRangeException e)
            {
                cout << "U vasoj listi nema elemenata!" << endl;
                break;
            }//end try-catch

        case 4:
            try
            {
                lista.pop_back_();
                break;
            } catch(OutOfRangeException e)
            {
                cout << "U vasoj listi nema elemenata!" << endl;
                break;
            }//end try-catch

        case 5:
            cout << "Unesite koji broj zelite ukoliniti: ";
            cin >> number;
            try
            {
                lista.remove_(number);
                break;
            } catch(OutOfRangeException e)
            {
                cout << "Broj ne postoji u vasoj listi!" << endl;
                break;
            }//end try-catch

        case 6:
            cout << "Unesite koji clan liste zelite ukloniti: ";
            cin >> number;

            try
            {
                lista.erase_(number);
                break;
            }catch(OutOfRangeException e)
            {
                cout << "Takav clan u vasoj listi ne postoji!" << endl;
                break;
            }//end try-catch

        case 7:
            try
            {
                lista.InsertionSort();
                break;
            }catch(NonExistingElementException e)
            {
                cout << "Vasa lista nema elemanta za rad!" << endl;
                break;
            }//end try-catch

        case 8:
            cout << "Koji clan zelite pogledati: ";
            cin >> number;
            try
            {
                cout << lista[number] << endl;
                break;
            } catch(OutOfRangeException e)
            {
                cout << "Takav clan ne postoji u vasoj listi!" << endl;
                break;
            }//end try-catch

        case 9:
            try
            {
                lista = MergeSort(lista, 0, lista.get_num_of_elements() - 1);
                break;
            } catch(exception e)
            {
                cout << "Sortiranje nije uspjelo..." << endl;
                break;
            }//end try-catch bloka
        case 10:
            cout << "Koji broj zelite unijeti: ";
            cin >> number;
            cout << "Na kojem mjestu: ";
            int k;
            cin >> k;

            try
            {
                lista.insertKth(number, k);
                break;
            } catch(OutOfRangeException e)
            {
                cout << "Nije moguca ta pozicija u vasoj listi!" << endl;
                break;
            } //end try-catch
        case 11:
            cout << "Koja dva elementa zelite zamijeniti: " << endl;
            int a, b;
            cout << "Prvi broj: ";
            cin >> a;
            cout << "Drugi broj: ";
            cin >> b;

            try
            {
                lista.swap_(a, b);
                break;
            }catch(OutOfRangeException e)
            {
                cout << "Neka od vasa dva elementa ne postoji u vasoj listi. " << endl;
                break;
            }
        case 12:
            try
            {
                lista.reverse_();
            } catch(NonExistingElementException e)
            {
                cout << "Vasa lista nema brojeva." << endl;
            }
        default:
            cout << "Probajte ponovo!" << endl;
        }//end switch

        cout << endl << endl;
        system("cls");
    }//endwhile

    return 0;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------


//   List<int> lista(3);

//    lista.push_front_(11);
//    lista.push_front_(33);
//    lista.push_back_(22);
//    lista.push_back_(52);
//    lista.push_front_(41);
//
//    lista.print();
//
//    cout << endl;
//
//    lista.print_current_element();
//    lista.Next();
//    cout << endl;
//    lista.print_current_element();
//    cout << endl;
//    lista.Prev();
//    lista.print_current_element();
//
//    lista.Back();
//    cout << endl;
//    lista.print_current_element();
//    try
//    {
//        lista.Prev();
//    } catch(int e)
//    {
//        cout << e << endl;
//    }
//
//    List<int> lista(3);
//    lista.push_back_(32);
//    lista.push_back_(41);
//    lista.push_back_(28);
//    lista.push_back_(14);
//    lista.insertKth(50, 3);
//    lista.insertKth(10, 0);
//    lista.insertKth(20, 6);
//    lista.push_front_(11);
//
//    for(int i = 0; i < lista.get_num_of_elements(); i++)
//    {
//        cout << lista[i];
//        if(i != lista.get_num_of_elements() - 1)
//            cout << ", ";
//    }//end for
//    cout << endl;
//
//    lista.print();
//    cout << endl;
//
//    lista.pop_back_();
//    lista.pop_front_();
//    lista.remove_(50);
//    lista.remove_(32);
//    lista.remove_(41);
//    lista.remove_(28);
//    lista.remove_(14);
//
//    lista.push_back_(11);
//    lista.push_back_(22);
//    lista.push_back_(33);
//    lista.print();
//    cout << endl << endl;
//    lista.swap_(0, 2);
//    //lista.push_back_(18);
//
//    lista.print();
//
//    for(int i = 0; i < lista.get_num_of_elements(); i++)
//    {
//        cout << lista[i];
//        if(i != lista.get_num_of_elements() - 1)
//            cout << ", ";
//    }//end for
//    cout << endl;
//
//    lista.swap_(0, 3);
//
//    for(int i = 0; i < lista.get_num_of_elements(); i++)
//    {
//        cout << lista[i];
//        if(i != lista.get_num_of_elements() - 1)
//            cout << ", ";
//    }//end for
//    cout << endl;
//
//    lista.InsertionSort();
//
//    for(int i = 0; i < lista.get_num_of_elements(); i++)
//    {
//        cout << lista[i];
//        if(i != lista.get_num_of_elements() - 1)
//            cout << ", ";
//    }//end for
//    cout << endl;
//
//    cout << endl;
//
//    lista.print();
//    lista.erase_(0);
//    cout << endl;
//
//    lista.print();

        //ALLOCATION AND DESTRUCTOR TEST
//    while(true)
//    {
//        List<int> nova(1000);
//    }
//    List<int> lista1(4);
//    List<int> lista2(4);
//
//    lista1.push_back_(5);
//    lista1.push_back_(7);
//    lista1.push_back_(9);
//
//    lista2.push_back_(2);
//    lista2.push_back_(3);
//    lista2.push_back_(6);
//
//    lista1.print();
//    cout << endl << endl;
//    lista2.print();
//    cout << endl << endl;
//
//    List<int> lista3;
//    lista3 = Merge(lista1, lista2);
//
//    lista3.print();
//    List<int> lista(16);
//
//    lista.push_back_(3);
//    lista.push_back_(6);
//    lista.push_back_(1);
//    lista.push_back_(4);
//    lista.push_back_(2);
//    lista.push_back_(7);
//    lista.push_back_(9);
//    lista.push_back_(5);
//    lista.push_back_(11);
//    lista.push_back_(8);
//
//    lista = MergeSort(lista, 0, lista.get_num_of_elements() - 1);
//
//    lista.print();
//    //List<int> nova_lista = Merge(lista1, lista2);
//
//    //nova_lista.print();
