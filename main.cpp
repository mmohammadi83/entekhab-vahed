#include <iostream>
#include "hashMap.h"
#include "queueLinklist.h"
#include "stackArray.h"
#include <vector>

using namespace std;

Map<Course> courses;
Map<Student> students;


class Student;
class Course{
private:
    string name;
    string code;
    int capacity;
public:
    Queue waitingQueue;
    vector <string> students;

    Course(string name , string code , int capacity): name(name), code(code) , capacity(capacity){}

    void setName(string n){
        name = n;
    }
    string getName(){
        return name;
    }
    void setCode(string n){
        code = n;
    }
    string getCode(){
        return code;
    }
    void setCapa(int n){
        capacity = n;
    }
    int getCapa(){
        return capacity;
    }

    
};

class Student{
private:
    string name;
    string number;
    

public:
    vector<string> courseList;
    Stack<string> log(9);

    Student(string name, string number): name(name) , number(number){}

    void setName(string n){
        name = n;
    }
    string getName(){
        return name;
    }
    void setNumber(string n){
        number = n;
    }
    string getNumber(){
        return number;
    }


};

int main(){

}