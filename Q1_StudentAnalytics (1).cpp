#include<iostream>
using namespace std;

class Student {
private:
    char name[50];
    int marks;
public:
    Student() : marks(0) { name[0]='\0'; }
    void input() {
        cout<<"Name: "; cin>>name;
        cout<<"Marks (0-100): "; cin>>marks;
        while(marks<0||marks>100){ cout<<"Invalid. Enter 0-100: "; cin>>marks; }
    }
    const char* getName() const { return name; }
    int getMarks() const { return marks; }
};

class Department {
private:
    char deptName[50];
    Student* s;
    int n;
    static int totalDepts;
    static int totalStudents;
public:
    Department() : s(nullptr), n(0) { deptName[0]='\0'; }
    ~Department() { delete[] s; }
    void input() {
        totalDepts++;
        cout<<"Department name: "; cin>>deptName;
        cout<<"Number of students: "; cin>>n;
        while(n<0){ cout<<"Invalid. Enter >= 0: "; cin>>n; }
        if(n==0){ s=nullptr; return; }
        s=new Student[n];
        totalStudents+=n;
        for(int i=0;i<n;i++){
            cout<<"Student "<<i+1<<":"<<endl;
            s[i].input();
        }
    }
    int topperIndex() const {
        int max=0;
        for(int i=1;i<n;i++)
            if(s[i].getMarks()>s[max].getMarks()) max=i;
        return max;
    }
    int getTopperMarks() const {
        if(n==0) return -1;
        return s[topperIndex()].getMarks();
    }
    const char* getTopperName() const {
        if(n==0) return "None";
        return s[topperIndex()].getName();
    }
    void showTopper() const {
        if(n==0){ cout<<deptName<<": No students enrolled"<<endl; return; }
        cout<<deptName<<" Topper: "<<getTopperName()<<" ("<<getTopperMarks()<<")"<<endl;
    }
    void showPassFail() const {
        if(n==0){ cout<<deptName<<": No students"<<endl; return; }
        int pass=0,fail=0,highest=0,lowest=100,total=0;
        for(int i=0;i<n;i++){
            int m=s[i].getMarks();
            total+=m;
            if(m>=40) pass++; else fail++;
            if(m>highest) highest=m;
            if(m<lowest) lowest=m;
        }
        cout<<deptName<<" | Pass: "<<pass<<" | Fail: "<<fail
            <<" | Pass%: "<<(pass*100/n)
            <<" | Avg: "<<(total/n)
            <<" | High: "<<highest<<" | Low: "<<lowest<<endl;
    }
    const char* getDeptName() const { return deptName; }
    int getN() const { return n; }
    static int getTotalDepts() { return totalDepts; }
    static int getTotalStudents() { return totalStudents; }
};

int Department::totalDepts=0;
int Department::totalStudents=0;

int main() {
    int n;
    cout<<"=== Student Analytics System ==="<<endl;
    cout<<"Number of departments: "; cin>>n;
    while(n<=0){ cout<<"Must be > 0: "; cin>>n; }
    Department* d=new Department[n];
    for(int i=0;i<n;i++){
        cout<<"\n-- Department "<<i+1<<" --"<<endl;
        d[i].input();
    }
    cout<<"\n=== Department Results ==="<<endl;
    for(int i=0;i<n;i++){
        d[i].showTopper();
        d[i].showPassFail();
    }
    cout<<"\n=== University Topper ==="<<endl;
    int best=-1;
    for(int i=0;i<n;i++){
        if(d[i].getN()>0){
            if(best==-1||d[i].getTopperMarks()>d[best].getTopperMarks()) best=i;
        }
    }
    if(best==-1) cout<<"No students found in any department."<<endl;
    else cout<<"University Topper: "<<d[best].getTopperName()<<" from "<<d[best].getDeptName()<<" with "<<d[best].getTopperMarks()<<" marks"<<endl;
    cout<<"\n=== Summary ==="<<endl;
    cout<<"Total Departments: "<<Department::getTotalDepts()<<endl;
    cout<<"Total Students: "<<Department::getTotalStudents()<<endl;
    delete[] d;
    return 0;
}
