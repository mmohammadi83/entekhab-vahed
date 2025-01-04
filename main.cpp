#include <iostream>
#include "hashMap.h"
#include "queueLinklist.h"
#include "stackArray.h"
#include <vector>
#include <conio.h>

using namespace std;

#define khat cout << "=============================================\a";

void addCourse();
void addStudentToCourse(Student* );
class Course;
class Student;
Map<Course>* courses = new Map<Course>(capa);
Map<Student>* students = new Map<Student>(capa);

class Course{
private:
    string name;
    string code;
    int capacity;
public:
    Queue waitingQueue;
    vector <string> thisStudents;
    bool isFull;
    Course(string name , string code , int capacity): name(name), code(code) , capacity(capacity){ isFull = 0;}

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

    void updateIsFull(){
        isFull = thisStudents.size()/capacity;
    }

    int searchInThisStudents(string code){
        for(int i=0 ; i<thisStudents.size() ; i++){
            if(thisStudents[i] == code)
                return i;
        }
        return -1;
    }
    
};

class Member{
private:
    string name;
    string number;
    string pass;
    
public:

    Member(string name, string number , string pass):pass(pass), name(name) , number(number){}

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
    void setPass(string n){
        pass = n;
    }
    string getPass(){
        return pass;
    }

    bool passValid(string p){
        if(pass == p) return 1;
        else return 0;
    }

    virtual bool isAdmin() = 0;
    virtual void joinStudentToCourse() = 0;
};

class Student : public Member{
public:
    vector<string> courseList;
    Stack<string> log;

    Student(string name, string number , string pass):Member(name , number , pass){}

    bool isAdmin(){
        return 0;
    }

    void joinStudentToCourse(){
        system("cls");
        addStudentToCourse(this);
        log.push("addCourse");
    }
    void printCourses(){
        for(auto& i: courseList){
            cout << "name: " << courses->get(i) << "    code: " << i;
        }
    }
    int searchInCourseList(string code){
        for(int i=0 ; i<courseList.size() ; i++){
            if(courseList[i] == code)
                return i;
        }
        return -1;
    }
};

class Admin : public Member{
public:
    bool isAdmin(){
        return 1;
    }

    void addCourseByAdmin(){
        system("cls");
        addCourse();
    }
    void addStudentByAdmin(){
        system("cls");
        addStudent();
    }
    void coursesStatus(){
        system("cls");
        courses->print();
        getch();
    }
    void joinStudentToCourse(){
        system("cls");
        cout <<"enter student number: ";
        string num;
        cin>> num ;
        addStudentToCourse(students->get(num));
    }

    
};

int capa = 10;
template <typename T>

Map<T>* loadFactor(Map<T>* temp){
    if (static_cast<float>(temp->FullIndex)/temp->capacity > 0.66){
        capa += 10;
        Map<T>* map = new Map<T>[capa];
        
        temp->replace(map);
        delete temp;
        temp = nullptr;
        return map;
    }
    return temp;
}



void removeStudentFromCourse(Student* stu){
    while(true){
        system("cls");
        khat
        stu->printCourses();
        khat
        cout << "enter course code to remove(0 for exit): ";
        string code;
        cin>> code;
        if(code == "0"){
            break;
        }
        int i = stu->searchInCourseList(code);
        if(i == -1){
            cout << "code is not avable";
            getch();
        }
        else{
            stu->courseList.erase(stu->courseList.begin()+i);
            Course* temp = courses->get(code);
            int j = temp->searchInThisStudents(stu->getNumber());
            temp->thisStudents.erase(temp->thisStudents.begin()+j);
            if(!temp->isFull){
                string number = temp->waitingQueue.dequeue();
                temp->thisStudents.push_back(number);
                Student* stu2 = students->get(number);
                stu2->courseList.push_back(code);
                stu2 = nullptr;
            }
            temp = nullptr;
            cout << "done";
            getch();
            
        }
    }
}

void addWaitingQueue(Course* course , string number){
    cout << "this course is full. are you sure to add waiting queue?\n";
    cout << "1-yes\n2-no\n";
    int a;
    cin>>a;
    if(a == 1){
        course->waitingQueue.enqueue(number);
        cout << "you joined to waiting queue of this course!";
        getch();
    }
    else
        return;
}

void addStudentToCourse(Student* stu){
    khat // tarif dar bala
    courses->print();
    khat
    cout << "enter course code: ";
    string code;
    cin>> code;
    Course* temp = courses->get(code);
    if(temp->isFull){
        addWaitingQueue(temp , stu->getNumber());
        temp = nullptr;
        return;
    }
    stu->courseList.push_back(code);
    temp->thisStudents.push_back(stu->getNumber());
    temp->updateIsFull();
    temp = nullptr;
    cout << "you joined to this course!";
    getch();
}

void addCourse(){
    string name, code;
    int capa;
    cout<< "enter course name: ";
    cin >> name;
    
    cout<< "enter course code: ";
    cin >> code;
    cout<< "enter capacity of course: ";
    cin >> capa;

    Course* temp = new Course(name , code , capa);

    courses->insert(code , temp);

    courses = loadFactor<Course>(courses);
}

void addStudent(){
    string name, number, pass;
    cout<< "enter Student name: ";
    cin >> name;
    cout<< "enter Student number: ";
    cin >> number;
    cout<< "enter Student password: ";
    cin >> pass;

    Student* temp = new Student(name , number , pass);

    students->insert(number , temp);

    students = loadFactor<Student>(students);
}

int main(){

}