/*
    Author: Dane Wolfe
    Date: 2/25/2025
    Description: A class implementation of a linked list. 
        -Note: Importing queue_Wolfe.hpp for the Node class
        -Double note: Accidentally created in FileSystem.cpp, was copied and pasted over to correct file
*/
#pragma once

#ifndef LL_HPP
#define LL_HPP

#include <iostream>
#include "queue_Wolfe.hpp"

/* LinkedList class: For representing a linked list data structure, some methods removed due to usefulness */
template <typename T>
class LinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        LinkedList();
        ~LinkedList();

        Node<T>* getFront();
        Node<T>* getTail();
        int getSize();

        void addFront(T item);
        void addTail(T item);
        void arbitraryInsert(Node<T>* previous, Node<T>* newNode);

        void removeFront();
        void removeTail();
        void remove(T item);
        void arbitraryRemove(Node<T>* previous, Node<T>* target);

        Node<T>* find(T item);
        void empty();

};

/* Constructor for a linkedlist object */
template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/* Deconstructor for a linkedlist object */
template <typename T>
LinkedList<T>::~LinkedList(){
    this->empty();
}

/* Getters: return by specified method */

template <typename T>
Node<T>* LinkedList<T>::getFront(){
    return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail(){
    return tail;
}

template <typename T>
int LinkedList<T>::getSize(){
    return size;
}

/* Insertions */
/* Add to the head */
template <typename T>
void LinkedList<T>::addFront(T item){
    Node<T>* newNode = new Node<T>(item, head);
    if(head == nullptr){
        tail = newNode;
    }
    head = newNode;
    size++;
}

/* Add to the tail */
template <typename T>
void LinkedList<T>::addTail(T item){
    if(head == nullptr){
        addFront(item);
        return;
    }
    Node<T>* newNode = new Node<T>(item);
    tail->setNext(newNode);
    tail = newNode;
    size++;
}

/* Inserts a new node into the structure based on a previous node */
template <typename T>
void LinkedList<T>::arbitraryInsert(Node<T>* previous, Node<T>* newNode){
    newNode->setNext(previous->getNext());
    previous->setNext(newNode);
    size++;
}

/* Removals */
/* Removes the head */
template <typename T>
void LinkedList<T>::removeFront(){
    if(head == nullptr){
        throw std::out_of_range("Error: Cannot remove the head of an empty list");
    }
    else if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    else{
        Node<T>* remove = head;
        head = head->getNext();
        remove->setNext(nullptr);
        delete remove;
        size--;
    }
}

/* Removes the tail */
template <typename T>
void LinkedList<T>::removeTail(){
    if(head == nullptr){
        throw std::out_of_range("Error: Cannot remove the tail of an empty list");
    }
    else if(head == tail){
        delete head;
        head == nullptr;
        tail = nullptr;
        size = 0;
    }
    else{
        Node<T>* current = head;
        while(current->getNext()->getNext() != nullptr){
            current = current->getNext();
        }

        Node<T>* temp = current->getNext();
        tail = current;
        delete temp;
        size--;
    }
}

/* Removes the first occurence of an item in the linked linkedlist
    -Note: Since each value of the linked list will theoretically be unique, we have no need for removeAll */
template <typename T>
void LinkedList<T>::remove(T item){
    if(head == nullptr){
        throw std::out_of_range("Error: Cannot delete an item from an empty list");
    }
    else if(head->getData() == item){
        removeFront();
    }
    else{
        Node<T>* current = head->getNext();
        Node<T>* previous = head;

        while(current != nullptr && current->getData() != item){
            previous = current;
            current = current->getNext();
        }

        if(current != nullptr){
            if(current == tail){
                tail = previous;
                tail->setNext(nullptr);
                delete current;
                size--;
            }
            else{
                arbitraryRemove(previous, current);
            }
        }
    }
}

/* Removes an item in the list based on the node passed in and it's previous node */
template <typename T>
void LinkedList<T>::arbitraryRemove(Node<T>* previous, Node<T>* target){
    previous->setNext(target->getNext());
    target->getNext();
    delete target;
    size--;
}

/* Finds the first occurence of a node containing a specified item, if any (also doubles as a "exists" method) */
template <typename T>
Node<T>* LinkedList<T>::find(T item){
    Node<T>* current = head;

    while(current != nullptr){
        if(current->getData() == item) return current;
        current = current->getNext();
    }

    return nullptr;
}

/* Empties the list */
template <typename T>
void LinkedList<T>::empty(){
    Node<T>* current = head;
    while(current != nullptr){
        current = current->getNext();
        delete head;
        head = current;
    }
}

#endif
