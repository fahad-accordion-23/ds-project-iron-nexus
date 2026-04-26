#ifndef STACK_HPP
#define STACK_HPP

/**
 * @brief Simple linked-list based Stack for history tracking or undo operations.
 * @tparam T The type of data stored.
 */
template<typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
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
};

#endif // STACK_HPP
