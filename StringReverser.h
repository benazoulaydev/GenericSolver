//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H


#include <string>
#include "Solver.h"
#include <bits/stdc++.h>

class StringReverser : public Solver<std::string, std::string>{
public:
    std::string solve(std::string *p) override{
        reverse(p->begin(), p->end());
        return *p;
    }
};


#endif //EX4_STRINGREVERSER_H
