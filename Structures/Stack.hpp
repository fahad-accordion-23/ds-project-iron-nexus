#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

/**
 * @brief Simple linked-list based Stack for history tracking or undo operations.
 * @tparam T The type of data stored.
 */
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

    /**
     * @brief Pushes an item onto the top of the stack.
     */
    void push(const T& value);

    /**
     * @brief Removes and returns the top item.
     */
    T pop();

    /**
     * @brief Returns the top item without removing it.
     */
    T peek() const;

    /**
     * @brief Checks if the stack is empty.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the number of items in the stack.
     */
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

#endif  // STACK_HPP
