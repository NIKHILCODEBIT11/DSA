#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;
    node* child;

    node(int data,node* child,node* next){
        this->data = data;
        this->next = next;
        this->child = child;
    }
    node(int data){
        this->data = data;
        this->next = nullptr;
        this->child = nullptr;
    }
    node(int data,node* child){
        this->data = data;
        this->next = nullptr;
        this->child = child;
    }
};