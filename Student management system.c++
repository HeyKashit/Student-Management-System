// STUDENT MANAGEMENT SYSTEM C++
// KASHIT DUHAN
#include <iostream>
#include <string.h>
#include <conio.h>

struct Student{
    char id[10];        //student's id #
    char lname[30];        //student's last name
    char fname[30];        //student's first name
    char mname[30];        //student's middle name
    char course[50];    //student's course
    int year;            //student's year level
    int age;            //student's age
};

struct Subject{
    Student students[40];    //the array where the students to be enrolled will be stored
    int size;                //the number of students currently enrolled in the subject
    char name[50];            //the name of the subject, e.g. CS210
};

bool enrol(Subject&,Student);            //enrolls a student in the subject
bool drop(Subject&,char[]) ;            //drops a student from the subject based on the ID
void display(Subject);                    //displays all students enrolled in the subject
void display(Student);                    //displays a particular student
void displayByYearLevel(Subject,int);    //displays all students with a particular year level
void displayByCourse(Subject,char[]);    //displays all students with a particular course
void displayByName(Subject,char[]);        //displays all students with a particular last name
void displayByID(Subject,char[]);        //displays student with corresponding id
void sortByName(Subject&);                //sorts the enrolled students in alphabetical order based on the last name
void sortByID(Subject&);                //sorts the enrolled students in ascending order based on the ID number
int searchByName(Subject,char[]);        //searches if a student with such a name is enrolled in the subject
int searchByID(Subject,char[]);            //searches if a student with such an ID is enrolled in the subject

int main(){
    Subject s;
    int choice;

    strcpy(s.name,"CS210");
    s.size = 0;


    do{
        cout<<"Menu: "<<endl;    //displays the menu
        cout<<"1. Enroll a Student\n 2. Drop a Student\n 3. Sort by ID\n 4. Sort by Name\n 5. Display by Year\n"
            <<"6. Display by Name\n 7. Display by ID\n 8. Display by Course\n 9. Display All\n 10. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;            //asks the user to enter choice

        switch(choice){
        case 1:                                        //for the case when the user chooses 1
            Student st;                                //this is where the inputs will be stored
            cout<<"Enter ID: ";                        //the following lines asks for information about a student
            cin>>st.id;
            cout<<"Enter first name: ";
            cin.ignore();
            cin.getline(st.fname,30);
            cout<<"Enter middle name: ";
            cin.getline(st.mname,30);
            cout<<"Enter last name: ";
            cin.getline(st.lname,30);
            cout<<"Enter course: ";
            cin.getline(st.course,50);
            cout<<"Enter year level: ";
            cin>>st.year;
            cout<<"Enter age: ";
            cin>>st.age;

            if(enrol(s,st)==true)        //checks if there was successful enrol
                cout<<"Student successfully enrolled..."<<endl;
            else
                cout<<"Either subject is full or student is already enrolled..."<<endl;

            break;
        case 2:
            char id[10];
            cout<<"Enter ID# of student to be dropped: ";    //asks the user to enter the ID of the student to be dropped
            cin>>id;

            if(drop(s,id)==true)                            //checks if there was successful drop
                cout<<"Student successfully dropped...\n";
            else
                cout<<"Student cannot be dropped due to non-enrolment\n";

            break;
        case 3:
            sortByID(s);                //calls sorByID
            cout<<"Done sorting...\n";

            break;
        case 4:
            sortByName(s);                //calls sortByName
            cout<<"Done sorting...\n";

            break;
        case 5:
            int y;
            cout<<"Enter year level: ";    //asks the year level for the display by year level
            cin>>y;

            displayByYearLevel(s,y);    //calls displaByYearLevel

            break;
        case 6:
            char name[30];
            cout<<"Enter last name: ";    //asks the last name for the display by last name
            cin>>name;

            displayByName(s,name);        //calls displayByName

            break;
        case 7:
            char idr[10];
            cout<<"Enter ID number: ";    //asks for the id for display by ID
            cin>>idr;

            displayByID(s,idr);            //calls displayByID

            break;
        case 8:
            char course[50];
            cout<<"Enter course: ";
            cin.ignore();
            cin.getline(course,50);        //asks for the course to be used in display by course

            displayByCourse(s,course);    //calls display by course

            break;
        case 9:
            display(s);                    //calls display for displaying all students...
            break;
        case 10:
            cout<<"Thank you and have a good day.\n";    //displays this line when user chooses to exit
            break;
        default:
            cout<<"No such choice exists...\n";        //in case the user types in a choice not listed in the menu.
        }
    }while(choice!=10);    //so long as the user does not choose 10, the loop will repeatingly prompt the menu.
   return 0;
}

bool enrol(Subject &s, Student st){
    if( (searchByID(s,st.id)==-1) && (s.size < 40) ){    //checks if the subject is not full and that the student is not enrolled in the subject
        s.students[s.size] = st;    //stores st in the next available space in the array
        s.size++;                    //increments the size of the subject
        return true;
    }
    else
        return false;
}

bool drop(Subject &s, char id[]){
    int pos = searchByID(s,id);        //gets the position in the array where the student with the given input id is stored
    if(pos!=-1){                    //this means that the student is indeed enrolled and therefore can be dropped
        for(int i=pos; i<s.size-1; i++){
            s.students[i] = s.students[i+1];    //shifts the students to the left so the student to be dropped is overwritten
        }
        s.size--;                //the size of the subject must be decremented since it's one student less already
        return true;
    }
    else
        return false;            //this means that the ID was found to be not enrolled in the subject
}

void display(Student st){
    cout<<"ID #: "<<st.id<<endl;                                    //prints the id of the student
    cout<<"Name: "<<st.lname<<", "<<st.fname<<" "<<st.mname<<endl;    //prints the name of the student
    cout<<"Course: "<<st.course<<endl;                                //prints the course of the student
    cout<<"Year Level: "<<st.year<<endl;                            //prints the year level of the student
    cout<<"Age: "<<st.age<<endl;                                    //prints the age of the student
    cout<<"Press any key to continue..."<<endl;
    getch();
}

void display(Subject s){
    if(s.size==0){                                    //checks if there are no students enrolled in the subject
        cout<<"No students enrolled yet..."<<endl;    //if there are none, it prints this message.
    }
    else{
        for(int i=0; i<s.size; i++)        //loops through all the students currently enrolled in the subject
            display(s.students[i]);        //calls the display function that accepts a student as a parameter
    }

}

void displayByYearLevel(Subject s, int y){
    if(s.size==0){                                    //checks if there are no students enrolled in the subject
        cout<<"No students enrolled yet..."<<endl;    //if there are none, it prints this message.
    }
    else{
        for(int i=0; i<s.size; i++){        //loops through all the students currently enrolled in the subject
            if(s.students[i].year == y)        //checks if the student in the subject has year level y
                display(s.students[i]);        //calls the display function that accepts a student as a parameter
        }
    }
}

void displayByCourse(Subject s, char crse[]){
    if(s.size==0){                                    //checks if there are no students enrolled in the subject
        cout<<"No students enrolled yet..."<<endl;    //if there are none, it prints this message.
    }
    else{
        for(int i=0; i<s.size; i++){                    //loops through all the students currently enrolled in the subject
            if(strcmp(s.students[i].course,crse)==0)    //checks if the student in the subject has course crse
                display(s.students[i]);                    //calls the display function that accepts a student as a parameter
        }
    }
}

void displayByName(Subject s, char name[]){
    if(s.size==0){                                    //checks if there are no students enrolled in the subject
        cout<<"No students enrolled yet..."<<endl;    //if there are none, it prints this message.
    }
    else{
        for(int i=0; i<s.size; i++){                //loops through all the students currently enrolled in the subject
            if(strcmp(s.students[i].lname,name)==0)    //checks if the student in the subject has last name equal to name
                display(s.students[i]);                //calls the display function that accepts a student as a parameter
        }
    }
}

void displayByID(Subject s, char id[]){
    if(s.size==0){                                    //checks if there are no students enrolled in the subject
        cout<<"No students enrolled yet..."<<endl;    //if there are none, it prints this message.
    }
    else{
        for(int i=0; i<s.size; i++){                //loops through all the students currently enrolled in the subject
            if(strcmp(s.students[i].id,id)==0)        //checks if the student in the subject has id equal to id
                display(s.students[i]);                //calls the display function that accepts a student as a parameter
        }
    }
}

int searchByID(Subject s, char id[]){
    for(int i=0; i<s.size; i++){                    //loops through all the students currently enrolled in the subject
            if(strcmp(s.students[i].id,id)==0)        //if the id matches, the function will return i
                return i;                            //this i is the position of that student in the array with id equal to id
    }
    return -1;    //this means that no student in the class has such an id.
}

void sortByID(Subject &s){
    for(int i=0; i<s.size-1; i++){
        int min = i;    //assumes that the minimum is initially i
        for(int j=i+1; j<s.size; j++){

            if(strcmp(s.students[j].id,s.students[min].id)<0)        //searches for an id that is less than the current min
                min = j;                                        //if so, this becomes the new minimum
        }
        Student temp = s.students[i];        //this part swaps the student at position i and that at position min
        s.students[i] = s.students[min];
        s.students[min] = temp;
    }
}

void sortByName(Subject &s){
    for(int i=0; i<s.size; i++){
        int min = i;    //assumes that the minimum is initially i
        for(int j=i+1; j<s.size; j++){
            if(strcmp(s.students[j].lname,s.students[min].lname)<0)    //searches for an id that is less than the current min
                min = j;                                            //if so, this becomes the new minimum
            else
            if(strcmp(s.students[j].lname,s.students[min].lname)==0){        //if the last names happen to be the same
                if(strcmp(s.students[j].fname,s.students[min].fname)<0)    //the first name is then checked
                    min = j;
                else
                if(strcmp(s.students[j].fname,s.students[min].fname)==0){        //if the first names are also the same
                    if(strcmp(s.students[j].mname,s.students[min].mname)<0)    //the middle name is then checked
                        min = j;
                }
            }
        }
        Student temp = s.students[min];        //this part swaps the student at position i and that at position min
        s.students[min] = s.students[i];
        s.students[i] = temp;
    }
}
