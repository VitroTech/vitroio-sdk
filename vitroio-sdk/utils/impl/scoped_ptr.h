#ifndef VITROIO_SDK_SCOPED_PTR_H
#define VITROIO_SDK_SCOPED_PTR_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

namespace impl 
{

template <typename T>
class ScopedPtr : private NonCopyable< ScopedPtr<T> >
{
public:
    typedef Callback<void(void*)> Deleter;

    explicit ScopedPtr(T* ptr, Deleter deleter = Deleter(NULL)) : 
        ptr_(ptr),
        deleter_(deleter)
    {}

    ~ScopedPtr()
    { 
        if(!ptr_){ 
            return;
        }

        if(deleter_){
            deleter_(ptr_);
        }
        else{
            delete ptr_;
        }
    }

    T* get()
    {
        return ptr_;
    }

    const T* get() const
    {
        return ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    T& operator*() {
        return *ptr_;
    }

    operator bool() const
    {
        return ptr_;
    }

private:
    T* ptr_;
    Deleter deleter_;
};

} // namespace impl 

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_SCOPED_PTR_H