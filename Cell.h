//
// Created by kfiry on 12/01/2020.
//

#ifndef GENERICSOLVER_CELL_H
#define GENERICSOLVER_CELL_H

#include <utility>
#include <functional>
using namespace std;

// represent matrix cell
class Cell {
private:
public:
    int i, j;
    Cell(){
        i=99999;
        j=99999;
    }
    Cell(int i1,int j1){
        i = i1;
        j = j1;
    }
    void printS(){
        cout<<"("<<i<<","<<j<<")";
    }
    bool operator==(const Cell &other) const {
//        cout<<this->i<<","<<this->j<<" "<<other.i<<other.j<<endl;
        return ((this->i == other.i) && (this->j == other.j));
    }
    bool operator!=(const Cell &other) const{
        return !(*this == other);
    }
//    bool operator==(const Cell *other)const {
//        return (this->i == other->i) && (this->j == other->j);
//    }
//    bool operator!=(const Cell *other) const{
//        return !(*this == *other);
//    }
    int getI() const {
        return i;
    }

    int getJ() const {
        return j;
    }
};
namespace std
{
    template <>
    struct hash<Cell>
    {
        size_t operator()(const Cell& k) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return ((hash<int>()(k.getI()) ^ (hash<int>()(k.getJ()) << 1)) >> 1);
        }
    };
}
#endif //GENERICSOLVER_CELL_H
