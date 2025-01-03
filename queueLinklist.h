#pragma once

#include <iostream>

using namespace std;

template <class T>

class Node{
public:
    Node* next;
    T data;

    Node(T a){
        data = a;
        next = nullptr;
    }

};

class LinkList{
private:
    Node* head;
    Node* tail;

public:
    LinkList(){
        head = tail = nullptr;
    }
    
    void add(int a){
        Node* temp = new Node(a);
        if(!tail)
            tail = head = temp;
        else{
            head->next = temp;
            head = temp;
        }
    }

    int pop(){
        if(!tail)
            return -1;
        else{
            int x = tail->data;
            Node* temp = tail;
            tail = tail->next;
            delete temp;
            temp = nullptr;
            return x;
        }
    }

    int peak(){
        if(!tail)
            return -1;
        else{
            return tail->data;
        }
    }
};

int main(){
    
}