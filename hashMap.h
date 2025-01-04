#pragma once
#include <iostream>

template <class T>

class Map{
private:
    class Entry{
    public:
        std::string key;
        T* value; 
        bool isFull;

        Entry():key("") , value(nullptr) , isFull(false){}
    };
    
    Entry* array;

    int hash(std::string key){
        int index = 0;
        for(auto& a: key){
            index += a;
        }
        index = index % capacity;

        return index;
    }

public:

    int capacity;
    int fullIndex;

    Map(int c): capacity(c){
        array = new Entry[c];
        fullIndex = 0;
    }

    void replace(Map<T>* temp){
        for(int i=0 ; i<capacity ; i++){
            if(array[i].value){
                temp->insert(array[i].key , array[i].value);
            }
        }
    }

    void insert(std::string key , T* value){
        if(key == "") return;
        int i = hash(key);
        while(array[i].isFull){
            if(array[i].key == key){
                array[i].value = value;
                return;
            }
            i = (i+1) % capacity;
        }
        array[i].key = key;
        array[i].value = value;
        array[i].isFull = true;
        fullIndex++;
    }

    int exists(std::string key){
        for(int i=0 ; i<capacity ; i++){
            if(array[i].isFull && array[i].key == key){
                return i;
            }
        }
        return -1;
    }

    
    T* get(std::string key){
        if(exists(key) != -1){
            return array[exists(key)].value;
        }
        return nullptr;
    }
    
    void print(){
        for(int i=0 ; i<capacity ; i++){
            if(array[i].value){
                std::cout << "name: " << array[i].value->getName() << "\t code: " << array[i].key << std::endl;
            }
        }    
    }

    ~Map(){
        delete[] array;
        array = nullptr;
    }
};