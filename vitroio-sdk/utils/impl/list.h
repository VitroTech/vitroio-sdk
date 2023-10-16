#ifndef VITROIO_SDK_LIST_H
#define VITROIO_SDK_LIST_H

#include <cstddef>

namespace vitroio
{

namespace sdk
{

namespace impl 
{

template <typename T>
struct ListNode
{
    T value;
    ListNode* next;
};

template <typename T>
class List
{
public:
    List()
    {
        first_ = NULL;
        last_ = NULL;
    }

    ~List()
    {
        ListNode<T>* node = first_;
        ListNode<T>* nextNode;
        while(node != NULL){
            nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }

    bool isEmpty() const
    {
        return (first_ == NULL);
    }

    ListNode<T>* first()
    {
        return first_;
    }

    ListNode<T>* last()
    {
        return last_;
    }
    
    void pushBack(T value)
    {
        ListNode<T>* tmpNode = new ListNode<T>;
        tmpNode->value = value;
        tmpNode->next = NULL;
        if(isEmpty()){
            first_ = tmpNode;
            last_ = tmpNode;
        }
        else{
            last_->next = tmpNode;
            last_ = tmpNode;
        }
    }

private:
    ListNode<T>* first_;
    ListNode<T>* last_;
};

} // namespace impl 

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_LIST_H