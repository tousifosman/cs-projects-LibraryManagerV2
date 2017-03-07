#include "MemberInfo.h"

MemberInfo::MemberInfo(int inID){
    id = inID;
    //bObjField = inField;
}

bool MemberInfo::BorrowBooks(int bookID){
        borrowInfo.push_back(bookID);
        return true;
}

bool MemberInfo::ReturnBooks(int bookID){
    for(list<int>::iterator p = borrowInfo.begin(); p != borrowInfo.end(); p++)
        if((*p) == bookID){
            borrowInfo.erase(p);
            return true;
        }
    return false;
}
