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
        capacity = a
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
            cout <<"stack is full";
        else{
            array[++head] = a;
        }
    }

    T pop(){
        if(isEmpty()){
            cout << "stack is empty";
        }
        else{
            return array[head--];
        }
    }

   

    T top(){
        
        else{
            return array[head];
        }
    }

    ~Stack(){
        delete [] array;
        array = nullptr;
    }
};
