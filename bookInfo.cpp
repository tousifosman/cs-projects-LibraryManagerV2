#include "bookInfo.h"

BookInfo::BookInfo(int inID, Field *inField){
    id = inID;
    bObjField = inField;
}

bool BookInfo::BorrowBooks(int memberID, string name, string date){
    if(AvalableCopy>=1){
        borrowStruct bs;
        bs.ID = memberID;
        bs.name = name;
        bs.dateOfIssue = date;
        borrowInfo.push_back(bs);
        AvalableCopy --;
        return true;
    }
    else
        return false;
}

bool BookInfo::ReturnBooks(int memberID){
    for(list<borrowStruct>::iterator p = borrowInfo.begin(); p != borrowInfo.end(); p++){
        if((*p).ID == memberID){
            borrowInfo.erase(p);
            AvalableCopy++;
            return true;
        }
    }
    return false;
}

void BookInfo::setSortField(Field *inField){
    bObjField = inField;
}

bool BookInfo::operator==(BookInfo right){
    if(*bObjField == Name)
        return BookName == right.BookName;
    else if(*bObjField == Aouther)
        return AuthourName == right.AuthourName;

    return id == right.id;
}

bool BookInfo::operator>(BookInfo right){
    if(*bObjField == Name)
        return BookName > right.BookName;
    else if(*bObjField == Aouther)
        return AuthourName > right.AuthourName;

    return id > right.id;
}

bool BookInfo::operator>=(BookInfo right){
    if(*bObjField == Name)
        return BookName >= right.BookName;
    else if(*bObjField == Aouther)
        return AuthourName >= right.AuthourName;

    return id >= right.id;
}

bool BookInfo::operator<(BookInfo right){
    if(*bObjField == Name)
        return BookName < right.BookName;
    else if(*bObjField == Aouther)
        return AuthourName < right.AuthourName;

    return id < right.id;
}

bool BookInfo::operator<=(BookInfo right){
    if(*bObjField == Name)
        return BookName <= right.BookName;
    else if(*bObjField == Aouther)
        return AuthourName <= right.AuthourName;

    return id <= right.id;
}
