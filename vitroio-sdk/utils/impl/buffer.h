#ifndef VITROIO_SDK_BUFFER_H
#define VITROIO_SDK_BUFFER_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

namespace impl
{

class Buffer
{
public:
    Buffer() :
        buff_(NULL),
        availableSize_(0),
        workingSize_(0),
        usedSize_(0),
        freeOffset_(0)
    {}

    ~Buffer()
    {
        free();
    }

    bool alloc(uint32_t size, uint8_t defaultValue = 0)
    {
        if( (buff_ = new (nothrow) uint8_t[size]) ){
            availableSize_ = size;
            workingSize_ = size;
            usedSize_ = 0;
            memset(buff_, defaultValue, size);
            return true;
        }
        return false;
    }

    void free()
    {
        if(buff_){ 
            delete buff_;
            buff_ = NULL;
        }
        availableSize_ = 0;
        workingSize_ = 0;
        usedSize_ = 0;
        freeOffset_ = 0;
    }

    uint32_t availableSize() const
    {
        return availableSize_;
    }

    uint32_t size() const
    {
        return workingSize_;
    }

    uint32_t freeSize() const
    {
        return workingSize_ - usedSize_;
    }

    bool resize(uint32_t size)
    {
        if(size > availableSize_){
            return false;
        }
        workingSize_ = size;

        usedSize_ = (usedSize_ > workingSize_) ? workingSize_ : usedSize_;

        return true;
    }

    uint8_t* get()
    {
        return buff_;
    }

    const uint8_t* get() const
    {
        return buff_;
    }

    uint32_t set(uint8_t* data, uint32_t size)
    {
        uint32_t bytesToSet = (size > freeSize()) ? freeSize() : size;

        memcpy(buff_ + freeOffset_, data, bytesToSet);
        usedSize_ += bytesToSet;
        freeOffset_ += bytesToSet;

        return bytesToSet;
    }

    void clear(uint32_t newSize = 0, uint8_t defaultValue = 0)
    {
        usedSize_ = 0;
        freeOffset_ = 0;
        memset(buff_, defaultValue, availableSize_);
    }

    bool isEmpty() const
    {
        return !usedSize_;
    }

    bool isFull() const
    {
        return (usedSize_ == workingSize_) ? true : false; 
    }

    operator bool() const
    {
        return buff_;
    }

private:
    uint8_t* buff_;
    uint32_t availableSize_;
    uint32_t workingSize_;
    uint32_t usedSize_;
    uint32_t freeOffset_;
};

} // namespace impl 

} // namepsace sdk

} // namespace vitroio

#endif // VITROIO_SDK_BUFFER_H