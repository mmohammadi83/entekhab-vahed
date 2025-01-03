#pragma once

#include <iostream>

class Node{
public:
    Node* next;
    std::string data;

    Node(std::string a){
        data = a;
        next = nullptr;
    }
    ~Node(){

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
    
    bool isEmpty(){
        if(!tail){
            return 1;
        }
        else return 0;
    }

    void enqueue(std::string a){
        Node* temp = new Node(a);
        if(!tail)
            tail = head = temp;
        else{
            head->next = temp;
            head = temp;
        }
    }

    std::string dequeue(){
        if(isEmpty())
            return nullptr;
        else{
            std::string x = tail->data;
            Node* temp = tail;
            tail = tail->next;
            delete temp;
            temp = nullptr;
            return x;
        }
    }

    std::string first(){
        if(isEmpty())
            return nullptr;
        else{
            return tail->data;
        }
    }
};
