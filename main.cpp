#include <iostream>
#include <chrono>
#include <thread>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "MatrixMaze.h"
#include "Solution.h"
#include "ISearcher.h"
#include "BestFirstSearch.h"
#include "SearchSolver.h"
#include "BFS.h"
#include "DFS.h"
#include <queue>
using namespace std;

int main() {
//    Solution<Cell> s = SearchSolver(new BestFirstSearch<Cell>()).solve(new MatrixMaze());
    Solution<Cell> s = SearchSolver(new DFS<Cell>()).solve(new MatrixMaze());
    for(const auto p : *s.getPath()){
        cout<<"("<<p.getI()<<","<<p.getJ()<<")";
    }




//    StringReverser sr{};
//    MySerialServer mss{};
//    MyTestClientHandler ch{&sr};
//    mss.open(5600, &ch);
//    std::this_thread::sleep_for(std::chrono::milliseconds(200000));

    return 0;
}







//
// Created by ben on 03/12/2019.
//

//#ifndef UNTITLED2_EX2_H
//#define UNTITLED2_EX2_H
//
//#include <map>
//#include <iostream>
//#include <fstream>
//using namespace std;
//
//
///*
// * Part of the code was taken from a website :
// *
// * Credit : Bhrigu Srivastava
// * http://bhrigu.me/blog/2017/01/22/lru-cache-c-plus-plus-implementation/
// *  - For the Node Class
// *    I added to the node the Template T class for the object that i passed in each nodes
// *    also the key is a string
// *  - For the Double linked list class i change I added somes methods and change types
// *    to accept Template types and strings
// *  - For the CacheManager  I added methods and add the files writing reading and also
// *    accepts now object of class template T can be in the nodes
// *
// */
//template <typename  T> class Node {
//public:
//    string key;
//    T value;
//    Node *prev, *next;
//    Node(string k, T v): key(k), value(v), prev(NULL), next(NULL) {}
//
//};
//
//
//
//template <typename  T> class DoublyLinkedList {
//    Node<T> *front, *rear;
//    int sizeList=0;
//    //chek if rear node is empty
//    bool isEmpty() {
//        return rear == NULL;
//    }
//
//public:
//    DoublyLinkedList(): front(NULL), rear(NULL) {}
//    //create a node with the current paramters and the node to the head of the linked list
//    Node<T>* add_page_to_head(string key, T value) {
//        Node<T> *page = new Node<T>(key, value);
//        if(!front && !rear) {
//            front = rear = page;
//        }
//        else {
//            page->next = front;
//            front->prev = page;
//            front = page;
//        }
//        sizeList++;
//        return page;
//
//    }
//    //move the node in  paramater to the begining (head)
//    void move_page_to_head(Node<T> *page) {
//        //if the node is already in the head
//        if(page==front) {
//            return;
//        }
//        //if the node is at the end (rear)
//        if(page == rear) {
//            rear = rear->prev;
//            rear->next = NULL;
//        }
//        else {
//            page->prev->next = page->next;
//            page->next->prev = page->prev;
//        }
//
//        page->next = front;
//        page->prev = NULL;
//        front->prev = page;
//        front = page;
//    }
//    //remove the node from the list
//    void remove_rear_page() {
//        if(isEmpty()) {
//            return;
//        }
//        if(front == rear) {
//            delete rear;
//            front = rear = NULL;
//        }
//        else {
//            Node<T> *temp = rear;
//            rear = rear->prev;
//            rear->next = NULL;
//            delete temp;
//        }
//        sizeList--;
//
//    }
//    //get the end
//    Node<T>* get_rear_page() {
//        return rear;
//    }
//    //get the head
//    Node<T>* get_front() {
//        return front;
//    }
//    //size of the linked list
//    int getSize() {
//        return sizeList;
//    }
//
//
//
//};
//
//template <typename  T> class CacheManager{
//    int capacity, size;
//    DoublyLinkedList<T> *pageList;
//    //map to store the current node with its key string and value object of type T (template)
//    map<string, Node<T>*> pageMap;
//
//public:
//    CacheManager(int capt) {
//        this->capacity = capt;
//        size = 0;
//        pageList = new DoublyLinkedList<T>();
//        pageMap = map<string, Node<T>*>();
//
//    }
//    //as specified in the exercie the method get will check if the current key string
//    // is present in the cache or in file
//    T get(string key) {
//        //the goal of the exercice is to check first the cache because fast access then the files
//        if(pageMap.find(key)==pageMap.end()) {
//            // Object to read in file
//            fstream file_obj;
//            // open file with ios::in the name should be on the form : ClassName-key
//            file_obj.open(T::class_name + "-" + key, ios::in);
//            if(!file_obj)
//            {
//                throw "an error";
//            } else {
//                T val;
//                file_obj.read((char*)&val, sizeof(val));
//                //insert the new value (get an insert : twice but more shorter code 2O(i) = O(i))
//                this->insert(key, val);
//                file_obj.close();
//                return val;
//            }
//        } else {
//            //create a variable of type teplate T to store the current obj
//            T val = pageMap[key]->value;
//            // move the page to front
//            pageList->move_page_to_head(pageMap[key]);
//            return val;
//        }
//
//
//    }
//
//    void insert(string key, T value) {
//        // Object to write in file
//        ofstream file_obj;
//
//        // Opening file in append mode
//        file_obj.open(T::class_name + "-" + key, ios::out);
//        if(!file_obj)
//        {
//            throw "Error in creating file!!!";
//        }
//        // Writing the object's data in file
//        file_obj.write((char*)& value, sizeof(value));
//
//        file_obj.close();
//
//        if(pageMap.find(key)!=pageMap.end()) {
//            // if key already present, update value and move page to head
//            pageMap[key]->value = value;
//            pageList->move_page_to_head(pageMap[key]);
//            return;
//        }
//
//        if(size == capacity) {
//            // remove rear page
//            string k = pageList->get_rear_page()->key;
//            pageMap.erase(k);
//            pageList->remove_rear_page();
//            size--;
//        }
//
//        // add new page to head to Queue
//        Node<T> *page = pageList->add_page_to_head(key, value);
//        size++;
//        pageMap[key] = page;
//    }
//
//    void foreach(void(*func)(T&)) {
//        Node<T> *temp = pageList->get_front();
//        int i = 0;
//        while(i < pageList->getSize()) {
//            func(temp->value);
//            temp = temp->next;
//            i++;
//        }
//
//
//    }
//
//
//    ~CacheManager() {
//        //create an iterator to iterate through the map and delete objs.
//        // typename for the Template T objects
//        typename map<string, Node<T>*> ::iterator i1;
//        for(i1=pageMap.begin();i1!=pageMap.end();i1++) {
//            delete i1->second;
//        }
//        delete pageList;
//
//    }
//};
//
//
//
//#endif //UNTITLED2_EX2_H