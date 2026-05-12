#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr)
        {
        }
    };

    Node* top;
    int count;

public:
    Stack();
    ~Stack();

    void push(const T& value);

    T pop();

    T peek() const;

    bool isEmpty() const;

    int size() const;
    void clear();
};

template <typename T>
Stack<T>::Stack() : top(nullptr), count(0)
{
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
void Stack<T>::push(const T& value)
{
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    count++;
}

template <typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    Node* temp = top;
    T poppedValue = temp->data;
    top = top->next;
    delete temp;
    count--;
    return poppedValue;
}

template <typename T>
T Stack<T>::peek() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
int Stack<T>::size() const
{
    return count;
}

template <typename T>
void Stack<T>::clear()
{
    while (!isEmpty())
    {
        pop();
    }
}

#endif
