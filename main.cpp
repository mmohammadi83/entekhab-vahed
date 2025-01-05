#include <iostream>
#include "hashMap.h"
#include "queueLinklist.h"
#include "stackArray.h"
#include <vector>
#include <conio.h>

using namespace std;

#define khat cout << "=============================================" << endl;

class Course;
class Student;

void addCourse();
void addStudentToCourse(Student* );
void addStudent();
void removeStudentFromCourse(Student* stu);

int capa = 10;
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
            cout << "name: " << courses->get(i)->getName() << "    code: " << i << endl;
        }
    }
    int searchInCourseList(string code){
        for(int i=0 ; i<courseList.size() ; i++){
            if(courseList[i] == code)
                return i;
        }
        return -1;
    }

    void removeCourse(){
        log.push("removeCourse");
        removeStudentFromCourse(this);
    }
};

class Admin : public Member{
public:
    Admin(string name, string number , string pass):Member(name , number , pass){}
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
        cout <<"enter student number(0 for back): ";
        string num;
        cin>> num ;
        if(num != "0")
            addStudentToCourse(students->get(num));
    }

    
};


template <typename T>

Map<T>* loadFactor(Map<T>* temp){
    if (static_cast<float>(temp->fullIndex)/temp->capacity > 0.66){
        capa += 10;
        Map<T>* map = new Map<T>(capa);
        
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
    cout << "enter course code(0 for back): ";
    string code;
    cin>> code;
    if(code == "0")
        return;
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
void adminMenu(Admin* admin);
void signUpAdmin(Admin* admin){
    system("cls");
    string name , number , pass;
    cout<< "enter Admin name: ";
    cin >> name;
    cout<< "enter Admin number: ";
    cin >> number;
    cout<< "enter Admin password: ";
    cin >> pass;

    admin = new Admin(name , number , pass);
    adminMenu(admin);
}

void chekExistAdmin(Admin* admin){
    if(!admin){
        cout <<"admin not exists. please first sign up";
        getch();
        signUpAdmin(admin);
    }
}

void getWaitingQueue(){
    system("cls");
    string code;
    cout<< "enter course code(0 for back): ";
    cin >> code;
    if(code == "0")
        return;
    cout <<"\nname: "<< courses->get(code)->getName() << endl;
    courses->get(code)->waitingQueue.print();
    getch();
}

void adminMenu(Admin* admin){
    
    while(true){
        system("cls");
        cout<< "1-add a course\n2-sign up student\n3-add student to course\n4-show courses status\n5-show courses waiting queue\n6-back\nenter: ";
        int ch;
        cin>> ch;
        switch (ch)
        {
        case 1:
            admin->addCourseByAdmin();
            break;
        case 2:
            admin->addStudentByAdmin();
            break;
        case 3:
            admin->joinStudentToCourse();
            break;
        case 4:
            admin->coursesStatus();
            break;
        case 5:
            getWaitingQueue();
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}
void validateAdmin(Admin* admin){
    if(!admin)
        chekExistAdmin(admin);
    else{
        while(true){
            string number , pass;
            system("cls");
            cout<< "enter Admin number: ";
            cin >> number;
            cout<< "enter Admin password: ";
            cin >> pass;

            if(admin->getNumber() == number && admin->getPass()== pass){
                adminMenu(admin);
            }
            else{
                cout << "password or username incorrect(enter 0 for exit)";
                int a = getch();
                if(a == 0) break;
            }
        }
    }
}

void studentMenu(Student* stu){
    while(true){
        system("cls");
        cout<< "1-add a course\n2-remove a course\n3-show courses\n4-show given courses\n5-show courses waiting queue\n6-back\nenter: ";
        int ch;
        cin>> ch;
        switch (ch)
        {
        case 1:
            stu->joinStudentToCourse();
            break;
        case 2:
            stu->removeCourse();
            break;
        case 3:
            courses->print();
            getch();
            break;
        case 4:
            system("cls");
            khat
            stu->printCourses();
            khat
            getch();
            break;
        case 5:
            getWaitingQueue();
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}

void studentValidate(){
    while(true)
    {    
        system("cls");
        string number , pass;
        cout<< "enter Student number: ";
        cin >> number;
        cout<< "enter Student password: ";
        cin >> pass;

        if(students->get(number)->getPass() == pass){
            studentMenu(students->get(number));
        }
        else{
            cout << "password or username incorrect(enter 0 for exit)";
            int a = getch();
            if(a == 0) break;
        }
    }    

}

void menu(Admin* admin){
    while(true){
        system("cls");
        cout << "1-sign in Admin\n2-sign in student\n3-exit\nenter: ";
        int ch;
        cin>> ch;
        switch (ch)
        {
        case 1:
            validateAdmin(admin);
            break;
        case 2:
            studentValidate();
            break;
        default:
            break;
        }
    }
}

int main(){
    Admin* admin = nullptr;
    menu(admin);
}