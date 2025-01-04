#pragma once

#include <iostream>


template <class T>

class Stack{
private:
    T* array;
    int head;
    int capacity;

public:
    Stack(){
        head = -1;
        array = new T[10];
        capacity = 10;
    }

    bool isEmpty(){
        if(head == -1){
            return 1;
        }
        else return 0;
    }

    bool isFull(){
        if(head == capacity - 1){
            return 1;
        }
        else return 0;
    }
    
    void push(T a){
        if(isFull())
            std::cout <<"\nstack is full\n";
        else{
            array[++head] = a;
        }
    }

    T pop(){
        if(isEmpty()){
            return nullptr;
        }
        else{
            return array[head--];
        }
    }

   

    T top(){
        
        
        return array[head];
        
    }

    ~Stack(){
        delete [] array;
        array = nullptr;
    }
};
