#pragma once

#include <iostream>


template <class T>

class Stack{
private:
    T* array;
    int head;
    int capacity;

public:
    Stack(int a){
        head = -1;
        array = new T[a];
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
            throw overflow_error("stack is full");
        else{
            array[++head] = a;
        }
    }

    T pop(){
        if(isEmpty()){
            throw underflow_error("stack is empty");
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
