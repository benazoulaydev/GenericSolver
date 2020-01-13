//
// Created by kfiry on 06/01/2020.
//

#include "StringReverser.h"
#include <bits/stdc++.h>

std::string StringReverser::solve(std::string* p) {
    reverse(p->begin(), p->end());
    return *p;
}
