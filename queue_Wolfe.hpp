/*
    Author: Dane Wolfe
    Date: 2/25/2025
    Description: A simple queue class implementation using a node class for data representation

*/

#pragma once

#ifndef QUEUE_WOLFE_HPP
#define QUEUE_WOLFE_HPP

#include <iostream>

/* Node class: For representing individual pieces of data for a linked structure */
template <typename T>
class Node{
    private:
        T data;
        Node<T>* next;
    public:
        Node();
        Node(T item);
        Node(T item, Node<T>* next);

        T getData();
        void setData(T data);

        Node<T>* getNext();
        void setNext(Node<T>* next);
};

/* Constructors for a Node */

template <typename T>
Node<T>::Node(){
    next = nullptr;
}

template <typename T>
Node<T>::Node(T data){
    this->data = data;
    next = nullptr;
}

template <typename T>
Node<T>::Node(T data, Node<T>* next){
    this->data = data;
    this->next = next;

}

/* Returns the data inside of the Node */
template <typename T>
T Node<T>::getData(){
    return data;
}

/* Sets the data inside of the Node */
template <typename T>
void Node<T>::setData(T data){
    this->data = data;
}

/* Returns the next Node in the linked structure */
template <typename T>
Node<T>* Node<T>::getNext(){
    return next;
}

/* Sets the next Node in the linked structure */
template <typename T>
void Node<T>::setNext(Node<T>* next){
    this->next = next;
}

/* Queue class: For representing a queue data structure */
template <typename T>
class Queue{
    private:
        Node<T>* front;
        Node<T>* tail;
        int size;
    public:
        Queue();
        ~Queue();

        void enqueue(T data);
        T dequeue();
        T getFront();
        int getSize();

        void empty();
        bool isEmpty();
};

/* Constructor for a Queue object */
template <typename T>
Queue<T>::Queue(){
    front = nullptr;
    tail = nullptr;
    size = 0;
} 

/* Deconstructor for a Queue object */
template <typename T>
Queue<T>::~Queue(){
    this->empty();
}

/* Enqueues an object into the queue (to the tail of the queue) */
template <typename T>
void Queue<T>::enqueue(T data){
    Node<T>* newNode = new Node<T>(data);

    if(size == 0){
        front = newNode;
        tail = front;
    }
    else{
        tail->setNext(newNode);
        tail = newNode;
    }
    
    size++;
}

/* Dequeues an object from the queue (from the head of the queue) */
template <typename T>
T Queue<T>::dequeue(){
    if(size == 0){
        throw std::out_of_range("Error: Cannot dequeue from an empty queue");
    }
    else{
        Node<T>* temp = front;
        front = front->getNext();
        T tempData = temp->getData();
        size--;
        delete temp;
        return tempData;
    }
}

/* Returns the data at the front of the queue */
template <typename T>
T Queue<T>::getFront(){
    return front->getData();
}

/* Returns the size of the queue */
template <typename T>
int Queue<T>::getSize(){
    return size;
}

/* Empties the queue */
template <typename T>
void Queue<T>::empty(){
    Node<T>* current = front;
    while(current != nullptr){
        current = current->getNext();
        delete front;
        front = current;
    }
}

/* Returns true or false depending on if the queue is empty */
template <typename T>
bool Queue<T>::isEmpty(){
    return size == 0;
}

#endif
