/*************************
* Name    : Tousif Osman *
* ID      : 1220490042   *
* Sub     : CSE 225      *
* Section : 1            *
*                        *
*   Library Management   *
*                        *
*************************/

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "bookInfo.h"
#include "MemberInfo.h"

using namespace std;


/**Global Variable*/
list<BookInfo> BookData; ///for book data handeling
list<MemberInfo> MemberData; ///for member handeling

int memberIdCount = 0; ///for genarating member id
int bookIdCount = 0; ///for genareting book id
Field srtBField = ID; ///for sorting book

/**Member Manager*/
void AddMember();
void DeletMember(int id);
MemberInfo SearchMember(string name, bool &found);


/**Book Manager*/
BookInfo SearchBook(string field, bool &found);
void BorrowBook(int bookID, int userID);
void ReturnBook(int bookID, int userID);
void AddBook();
void DeletBook(int id);
void EditBook(int id);
void SwortBook();
void SetSwortField(Field inField);


/**Library Manager*/
void Settings();
void AddLogInID();
void DeletLogInID(string id);
void ResetProgram();

/**Loader and saver*/
void LoadData();
void SaveData();
void LoadBookData();
void SaveBookData();
void LoadMemberData();
void SaveMemberData();

/**Welcome and others*/
void Welcome();
void Timer(string text);
bool Authinticate();
void PrintBookObj(BookInfo obj);
void PrintAllBooks();
void PrintMemberObj(MemberInfo temp);
void PrintAllMembers();
void menu();
void management();

int main()
{
    if(Authinticate()){
        Welcome();
        LoadData();
        menu();
        SaveData();
        cout << "\n\n\t-Thank You !!" << endl;
        Timer("Saveing");
    }
    return 0;
}

/***************
* Book Manager *
***************/

BookInfo SearchBook(string field, bool &found){
    found = false;
    list<BookInfo>::iterator p = BookData.begin();
    for(;p != BookData.end(); p++){
        if((*p).BookName == field){
            found = true;
            return (*p);
        }
    }
    return (*BookData.begin());
}

void BorrowBook(int bookID, int userID){
        bool mFound = false;

        string date;

        list<MemberInfo>::iterator q = MemberData.begin(); ///finding member
        for(;q != MemberData.end(); q++)
            if((*q).id == userID){
                mFound = true;
                break;
            }

        if(mFound){ ///finding book
        list<BookInfo>::iterator p = BookData.begin();
        for(;p != BookData.end(); p++){
            if((*p).id == bookID){
                cout << "\tDate of Issue : ";
                cin >> date;
                if((*p).BorrowBooks(userID, (*q).Name, date)){ ///p = book , q = member
                    (*q).BorrowBooks(bookID);

                    SaveData();
                    cout << "\tBook Borrowed !!" << endl;
                    return;
                }
                else{
                    cout << "\tBook Can not be borrwod !!" << endl;
                    return;
                }
            }
        }
        cout << "\tBook can not be found !!" << endl;
    }
    else
        cout << "\tMember can not be found !!" << endl;
}

void ReturnBook(int bookID, int userID){
    bool mFound = false, bFound = false;

    list<MemberInfo>::iterator q = MemberData.begin(); ///finding member
    for(;q != MemberData.end(); q++)
        if((*q).id == userID){
            mFound = true;
            break;
        }
    if(!mFound){
        cout << "\tMember Not found !!" << endl;
        return;
    }

    list<BookInfo>::iterator p = BookData.begin(); ///finding book
    for(;p != BookData.end(); p++)
        if((*p).id == bookID){
            bFound = true;
            break;
        }
    if(!bFound){
        cout << "\tMember Not found !!" << endl;
        return;
    }

    if((*p).ReturnBooks(userID) && (*q).ReturnBooks(bookID)){
        cout << "\tBook has been returned !!" << endl;
        SaveData();
    }
    else
        cout << "\tBook has was not returned !!" << endl;
}

void AddBook(){
    BookInfo temp(++bookIdCount, &srtBField);
    cout << "\tName Of the book : ";
    cin >> temp.BookName;
    cout << "\tName Of the Authour : ";
    cin >> temp.AuthourName;
    cout << "\tName Of the Publisher : ";
    cin >> temp.Publishar;
    cout << "\tNumber of Copy : ";
    cin >> temp.AvalableCopy;

    BookData.push_back(temp);
    SaveBookData();
}

void DeletBook(int id){
    list<BookInfo>::iterator p = BookData.begin();
    for(;p != BookData.end(); p++)
        if((*p).id == id){
            BookData.erase(p);
            cout << "\tBook Deleted !!" << endl;
            SaveData();
            return;
        }
    cout << "\tBook not found" << endl;
}

void EditBook(int id){
    list<BookInfo>::iterator p = BookData.begin();
    for(;p != BookData.end(); p++)
        if((*p).id == id){
            int option;
                cout << "\n\t[1]Edit Name [2]Edit Authour [3]Edit Publisher [4]Number Of copy __";
                cin >> option;
            if(option == 1){
                cout << "\tName Of the book : ";
                cin >> (*p).BookName;
            }
            else if(option == 2){
                cout << "\tName Of the Authour : ";
                cin >> (*p).AuthourName;
            }
            else if(option == 3){
                cout << "\tName Of the Publisher : ";
                cin >> (*p).Publishar;
            }
            else if(option == 4){
                cout << "\tNumber Of copy : ";
                cin >> (*p).AvalableCopy;
            }
            else
                cout << "\tInvalde Option";

            cout << endl;
            SaveBookData();
            return;
        }
    cout << "\nBook Not Found !!" << endl;
}

void SetSwortField(Field inField){
    srtBField = inField;
}

void SwortBook(){
    cout << "\tSwort By ? [1]Name [2]Aouther [3]ID __";
    int inp;
    cin >> inp;
    if(inp == 1)
        SetSwortField(Name);
    else if(inp == 2)
        SetSwortField(Aouther);
    else if(inp == 3)
        SetSwortField(ID);

    BookData.sort();
    SaveBookData();
}

/****************
* Save and Load *
****************/

void SaveData(){
    SaveBookData();
    SaveMemberData();
}

void SaveBookData(){
    ofstream output("BookData.txt", ios::trunc);
    if(!output)
        cout << "\tCan not open file !!" << endl;
    else{
        list<borrowStruct>::iterator bp;

        output << bookIdCount;

        for(list<BookInfo>::iterator p = BookData.begin(); p != BookData.end(); p++){
            output << endl << (*p).BookName << " " << (*p).AuthourName << " "<< (*p).Publishar << " " << (*p).id<< " " << (*p).AvalableCopy << endl;
            for(bp = (*p).borrowInfo.begin(); bp != (*p).borrowInfo.end(); bp++)
                output << (*bp).name << " " << (*bp).ID << " " << (*bp).dateOfIssue << endl;
            output << "END";
        }
        output.close();
    }
}

void SaveMemberData(){
    ofstream output("MemberData.txt", ios::trunc);
    if(!output){
        cout << "\tCan not open file !!" << endl;
        return;
    }
    output << memberIdCount;
    list<MemberInfo>::iterator p = MemberData.begin();
    for(; p != MemberData.end(); p++){
        output << endl <<(*p).Name << " " << (*p).Email << " " << (*p).PhoneNumber << " " << (*p).id << endl;
        for(list<int>::iterator q = (*p).borrowInfo.begin(); q != (*p).borrowInfo.end(); q++)
            output << *q << " ";
        output << "0";
    }

    output.close();
}

void LoadData(){
    LoadBookData();
    LoadMemberData();
}

void LoadBookData(){
    ifstream input("BookData.txt");
    if(!input)
        cout << "\tCan not open file !!" << endl;
    else{
        list<BookInfo> bDtatTemp;
        BookInfo temp(0, &srtBField);
        borrowStruct bsTem;

        input >> bookIdCount;

        while(!input.eof()){
            input >> temp.BookName >> temp.AuthourName >> temp.Publishar >> temp.id >> temp.AvalableCopy;
            while(1){
                input >> bsTem.name;
                if(bsTem.name != "END" && !input.eof()){
                    input >> bsTem.ID >> bsTem.dateOfIssue;
                    temp.borrowInfo.push_back(bsTem);
                }
                else break;
            }
            bDtatTemp.push_back(temp);
            temp.borrowInfo.clear();
        }
        input.close();
        BookData = bDtatTemp;
    }
}

void LoadMemberData(){
    ifstream input("MemberData.txt");

    if(!input){
        cout << "\tCan not open file !!" << endl;
        return;
    }

    input >> memberIdCount;

    list<MemberInfo> mDataTemp;
    MemberInfo temp(0);
    int idTmp;

    while(!input.eof()){
        input >> temp.Name >> temp.Email >> temp.PhoneNumber >> temp.id;
        input >> idTmp;
        while(idTmp != 0 && !input.eof()){
            temp.borrowInfo.push_back(idTmp);
            input >> idTmp;
        }
        mDataTemp.push_back(temp);

        temp.borrowInfo.clear();
    }
    input.close();
    MemberData = mDataTemp;
}

/**************************************
* Welcome and authenticate and others *
**************************************/

void Welcome(){
    Timer("Loading");
    cout << "\n\n\n\tWelcome !!\n\n" << endl;

}

void Timer(string text){
    cout << "\n\n\t" <<text << " .....\n\t";
    for(int i = 0; i < 200000000; i++)
        if(!(i%10000000)) cout << "\x00db";
}

bool Authinticate(){
    ifstream input("adminID.txt", ios::in);
    if(!input){
        cout << "\tNo ID Avalable!! Please insert an new ID\n" << endl;
        AddLogInID();
        return Authinticate();
    }
    else if(input){
        string userID, userPassword, id, password;

        for(int i = 0; i < 3; i++){
            cout << "\tLogIn   ID     : ";
            cin >> userID;
            cout << "\tLogIn Password : ";
            cin >> userPassword;
            while(!input.eof()){
                input >> id >> password;
                if(userID == id && userPassword ==  password){
                    input.close();
                    return true;
                }
            }
            input.close();
            input.open("adminID.txt");
            cout << "\tInvalide Input !!\n\tTry " << i + 2 << endl;
        }
    }
    input.close();
    return false;
}

void AddLogInID(){
    ofstream output("adminID.txt", ios::out | ios::app);
    if(!output)
        cout<< "\toutput file can't be opened !!" << endl;
    else{
        string id, password;
        cout << "\tID : ";
        cin >> id;
        cout << "\tPassword : ";
        cin >> password;
        output << endl << id << " " << password;
        output.close();
    }

}


struct storageType{
        string id;
        string password;
};
void DeletLogInID(string id){

    storageType strTemp;

    list<storageType> temp;

    ifstream input("adminID.txt");

    if(!input){
        cout << "\tError in openig file" << endl;
        return;
    }

    while(!input.eof()){
        input >> strTemp.id >> strTemp.password;
        if(strTemp.id != id){
            temp.push_back(strTemp);
            //cout << strTemp.id << endl;
        }
    }
    input.close();

    ofstream output("adminID.txt", ios::trunc);

    if(!output){
        cout << "\tError in openig file" << endl;
        return;
    }

    for(list<storageType>::iterator p = temp.begin(); p != temp.end();p++)
        output << endl << (*p).id << " " << (*p).password;

    output.close();
}

void ResetProgram(){
    ofstream ostm;
    ostm.open("adminID.txt", ios::trunc);
    ostm << "admin 0" <<endl;
    ostm.close();

    ostm.open("BookData.txt", ios::trunc);
    ostm << "0";
    ostm.close();

    ostm.open("MemberData.txt", ios::trunc);
    ostm << "0";
    ostm.close();

    LoadData();
}

void PrintBookObj(BookInfo obj){
        cout << "\t\x0000f "<<obj.BookName <<endl;
        cout << "\t______________________________________" <<endl;
        cout <<"\tID        : " << obj.id << endl;
        cout <<"\tName      : " << obj.BookName <<endl;
        cout <<"\tAurher    : " << obj.AuthourName << endl;
        cout <<"\tPublisher : " << obj.Publishar << endl;
        cout <<"\tCopies    : " << obj.AvalableCopy << endl;
        cout << "\tBorroed By \x001f\n" <<endl;
        for(list<borrowStruct>::iterator p = obj.borrowInfo.begin(); p != obj.borrowInfo.end(); p++)
            cout << "\t\t" << (*p).ID << " " <<(*p).name << " " <<(*p).dateOfIssue << endl;

}

void PrintAllBooks(){
    for(list<BookInfo>::iterator p = BookData.begin(); p != BookData.end(); p++){
        cout << "\n\t______________________________________" << endl;
        PrintBookObj((*p));
    }
}

void menu(){
    while(1){
        LoadData();
        cout<< "\t                 Menu" <<endl;
        cout<< "\t--------------------------------------" <<endl;
        cout<< "\t\x0010 Search   Book[1]    \x0010 All   Books[A]\n" <<endl;
        cout<< "\t\x0010 Search Member[2]    \x0010 All Members[S]\n" <<endl;
        cout<< "\t\x0010 Borrow   Book[3]    \x0010   Manageent[M]\n" <<endl;
        cout<< "\t\x0010 Return   Book[4]    \x0010        Exit[0]\n" <<endl;

        char option;
        cout << "\t__";
        cin >>option;
        if(option == '1'){
            if(BookData.empty()){ ///If the list is empty or initial stage
                cout << "\tEmpty book data!!" << endl;
                continue;
            }

            string name;
            bool found;
            BookInfo out(0, &srtBField);
            cout << "\tName Of the Book : ";
            cin >> name;
            out = SearchBook(name, found);
            if(found)
                PrintBookObj(out);
            else
                cout << "\tBook not Found !!" << endl;

        }
        else if(option == '2'){
            if(MemberData.empty()){  ///If the list is empty or initial stage
                cout << "\tEmpty Member data !!" << endl;
                continue;
            }
            string name;
            bool found;
            cout << "\tName of the Member : ";
            cin >> name;
            MemberInfo temp(0);
            temp = SearchMember(name, found);
            if(found) PrintMemberObj(temp);
        }
        else if(option == '3'){
            int name;
            int bID;
            cout << "\tBook   ID : ";
            cin >> bID;
            cout << "\tMember ID : ";
            cin >> name;
            BorrowBook(bID, name);
        }
        else if(option == '4'){
            int name;
            int bID;
            cout << "\tBook   ID : ";
            cin >> bID;
            cout << "\tMember ID : ";
            cin >> name;
            ReturnBook(bID, name);
        }
        else if(option == 'A' || option == 'a')
            PrintAllBooks();
        else if(option == 'S' || option == 's')
            PrintAllMembers();
        else if(option == 'M' || option == 'm')
            management();
        else if(option == '0')
            break;
        else
            cout << "\tInvalade Option !!" << endl;

        cout << endl;
        SaveData();
    }
}

void management(){
        while(1){
            LoadData();
            cout<< "\n\t               Management" <<endl;
            cout<< "\t--------------------------------------" <<endl;
            cout<< "\t\x0010 Add      Book[1]  \x0010  Add    LogID[A]\n" <<endl;
            cout<< "\t\x0010 Add    Member[2]  \x0010  Delete LogID[D]\n" <<endl;
            cout<< "\t\x0010 Delete   Book[3]  \x0010  Sort   books[S]\n" <<endl;
            cout<< "\t\x0010 Delete Member[4]  \x0010 *ResetProgram[R]\n" <<endl;
            cout<< "\t\x0010 Edit     Book[5]  \x0010          Back[0]\n" <<endl;


            char option;
            cout << "\t__";
            cin >>option;

            if(option == '1')
                AddBook();
            else if(option == '2')
                AddMember();
            else if(option == '3'){
                int id;
                cout << "\tBook ID : ";
                cin >> id;
                DeletBook(id);
            }
            else if(option == '4'){
                int temp;
                cout << "\tMember ID : ";
                cin  >> temp;
                DeletMember(temp);
            }
            else if(option == '5'){
                int id;
                cout << "\tBook ID : ";
                cin >> id;
                EditBook(id);

            }
            else if(option == 'A' || option == 'a')
                AddLogInID();
            else if(option == 'D' || option == 'd'){
                if(Authinticate()){
                    string id;
                    cout << "\tID for Delete : ";
                    cin >> id;
                    DeletLogInID(id);
                }
            }
            else if(option == 'S' || option == 's')
                SwortBook();
            else if(option == 'R' || option == 'r'){
                if(Authinticate())
                    ResetProgram();
            }
            else if(option == '0')
                break;
            else
                cout << "\tInvalade Option !!" << endl;

            cout << endl;
            SaveData();
        }

}

/************************
* MemberData Functions *
************************/

void AddMember()
{
    MemberInfo temp(++memberIdCount);
    cout << "\tMember  Name : ";
    cin >> temp.Name;
    cout << "\tMember Email : ";
    cin >> temp.Email;
    cout << "\tPhone Number : ";
    cin >> temp.PhoneNumber;

    MemberData.push_back(temp);
    cout << "\tMember Added !!" << endl;
    SaveMemberData();
}

void DeletMember(int id)
{
    list<MemberInfo>::iterator p = MemberData.begin();
    for(;p != MemberData.end(); p++)
        if((*p).id == id){
            MemberData.erase(p);
            cout << "\tMember Deleted !!" << endl;
            SaveData();
            return;
        }
    cout << "\tMember not found" << endl;
}


MemberInfo SearchMember(string field, bool &found)
{
    found = false;

    list<MemberInfo>::iterator p = MemberData.begin();
    for(;p != MemberData.end(); p++)
        if((*p).Name == field){
            found = true;
            return (*p);
        }

    return (*MemberData.begin());
}

void PrintAllMembers(){
    cout << endl;
    list<MemberInfo>::iterator p = MemberData.begin();
    for(;p != MemberData.end(); p++){
        PrintMemberObj((*p));
        cout<<endl;
    }
}


void PrintMemberObj(MemberInfo temp)
{
        cout << "\t\x0000f "<<temp.Name <<endl;
        cout << "\t______________________________________" <<endl;
        cout << "\tID               : " <<temp.id << endl;
        cout << "\tName             : " <<temp.Name << endl;
        cout << "\tE - mail         : " <<temp.Email << endl;
        cout << "\tPhone   No       : " <<temp.PhoneNumber <<endl;
        cout << "\tBorrowedBook IDs : ";
        list<int>::iterator p = temp.borrowInfo.begin();
        for(;p != temp.borrowInfo.end() ;p++)
            cout << (*p) << ", ";
        cout << endl;
}

