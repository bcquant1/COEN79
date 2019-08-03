//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.

#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function
namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }
    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    
    sequence::~sequence(){
        list_clear(head_ptr);
        cursor = NULL;
        precursor = NULL;
        tail_ptr = NULL;
        head_ptr = NULL;
        many_nodes = 0;
    }
    
    void sequence::start( ){
        cursor = head_ptr;
        precursor = NULL;
    }
    
    void sequence::end(){
        if (head_ptr == NULL && tail_ptr == NULL){
            return;
        }
        cursor = tail_ptr;
        if (head_ptr == tail_ptr){
            precursor = NULL;
        }
        else{
            precursor = list_locate(head_ptr, many_nodes-1);
        }
    }
    void sequence::advance( ){
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }
    
    void sequence::insert(const value_type& entry){
        if (precursor == NULL || !is_item()){
            list_head_insert(head_ptr, entry);
            many_nodes++;
            cursor = head_ptr;
            precursor = NULL;
            if (tail_ptr == NULL){
                tail_ptr = head_ptr;
            }
            return;
        }
        list_insert(precursor, entry);
        cursor = precursor -> link();
        many_nodes++;
    }
    
    void sequence::attach(const value_type& entry){
        if (!is_item()){
            if (head_ptr == NULL && tail_ptr == NULL){
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
                tail_ptr = head_ptr;
                many_nodes++;
                return;
            }
            else{
                list_insert(precursor,entry);
                cursor = precursor-> link();
                tail_ptr = tail_ptr-> link();
                many_nodes++;
                return;
            }
        }
        bool update(cursor == tail_ptr);
        precursor = cursor;
        list_insert(precursor,entry);
        cursor = cursor->link();
        if(update){
            tail_ptr = tail_ptr-> link();
        }
        many_nodes++;
    }
    
    void sequence::operator =(const sequence& source){
        if (this == &source){
            return;
        }
        list_clear(head_ptr);
        cursor = NULL;
        precursor = NULL;
        head_ptr = NULL;
        tail_ptr = NULL;
        many_nodes = 0;
        if (source.cursor == NULL){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
        }
        else if(source.cursor == source.head_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            start();
        }
        else if(source.cursor == source.tail_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            end();
        }
        else{
            list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
            list_piece(source.cursor, NULL, cursor, tail_ptr);
            precursor->set_link(cursor);
        }
        many_nodes = source.many_nodes;
    }
    
    void sequence::remove_current( ){
        assert(is_item());
        if (cursor == head_ptr){
            if (head_ptr == tail_ptr){
                list_head_remove(head_ptr);
                cursor = NULL;
                precursor = NULL;
                tail_ptr = NULL;
                head_ptr = NULL;
            }
            else{
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        }
        else if(cursor == tail_ptr){
            list_remove(precursor);
            tail_ptr = precursor;
            precursor = NULL;
            cursor = NULL;
        }
        else{
            list_remove(precursor);
            cursor = cursor->link();
        }
        many_nodes--;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    
    size_t sequence::size( ) const{
        return many_nodes;
    }
    
    bool sequence::is_item( ) const{
        return (cursor != NULL);
    }
    
    sequence::value_type sequence::current( ) const{
        assert(is_item());
        return cursor->data();
    }
}
