#pragma once
#include <iostream>

class Map{
private:
    class Entry{
    public:
        std::string key;
        std::string value; 
        bool isFull;

        Entry():key("") , value("") , isFull(false){}
    };
    int capacity;
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
    Map(int c): capacity(c){
        array = new Entry[c];
    }

    void insert(std::string key , std::string value){
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

    }

    int exists(std::string key){
        for(int i=0 ; i<capacity ; i++){
            if(array[i].isFull && array[i].key == key){
                return i;
            }
        }
        return -1;
    }

    std::string get(std::string key){
        if(exists(key) != -1){
            return array[exists(key)].value;
        }
        return "Empty";
    }
    ~Map(){
        delete[] array;
        array = nullptr;
    }
};