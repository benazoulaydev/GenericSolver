//
// Created by ben on 12/01/2020.
//

#ifndef GENERICSOLVER_STRINCLASS_H
#define GENERICSOLVER_STRINCLASS_H

#include "CacheManager.h"
#include <iostream>
#include <string>
#include <dirent.h>
#include <stdio.h>
using namespace std;

class strinClass
{
    const char* name;
public:
    static const string class_name; //every class will have a class static name called: class_name
    strinClass(const char* _name): name(_name) {};
    strinClass(){}; //every class will have a default constructor
    void print() {
        cout<<"strinClass Object: "<<name<<endl;
    };
    ~strinClass(){};

};
const string strinClass::class_name = "stringClass";


#endif //GENERICSOLVER_STRINCLASS_H
