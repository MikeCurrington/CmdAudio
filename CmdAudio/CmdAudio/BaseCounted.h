//
//  BaseCounted.hpp
//  CmdAudio
//
#pragma once
#include <cassert>
#include <type_traits>

///
/// Base class for classes that want refcounted allocation / destruction
/// NOT THREAD SAFE !
///
template <class T>
class BaseCounted
{
private:
    BaseCounted & operator=(const BaseCounted &rhs);	// deliberately not implemented so we dont accidentally assign
    BaseCounted(const BaseCounted&);					// deliberately not implemented copy constructor
    
public:
    BaseCounted();
    
    T * Aquire();                   // increase the refcount of this instance (call Release when done)
    void Release();                 // Release a use of this instance (will delete when refcount is zero)
    
    static void CheckMemFree();     // debug function to see if all generators have been freed
protected:
    virtual ~BaseCounted() = 0;     // protected so we use refcounting Aquire/Release to delete when unused
    
private:
    int refCount;
    
    static int numAllocated;        //debug
};


///
/// BaseCountedPtr
/// Automatic refcounting (smart) pointer template class
///
template <typename T>
class BaseCountedPtr
{
    //    static_assert(std::is_base_of<BaseCounted<T>, T>::value, "T must derive from BaseCounted");
public:
    BaseCountedPtr()
    {
        obj = nullptr;
    }
    ~BaseCountedPtr()
    {
        auto o = obj;
        obj = nullptr;
        if (o != nullptr)
            o->Release();
    }
    BaseCountedPtr(T* o)
    {
        if (o != nullptr)
            obj = static_cast<T*>( o->Aquire() );
        else
            obj = nullptr;
    }
    BaseCountedPtr( const BaseCountedPtr & src )
    {
        if (src.obj)
            obj = static_cast<T*>( src.obj->Aquire() );
        else
            obj = nullptr;
    }
    
    BaseCountedPtr& operator=( const BaseCountedPtr other )
    {
        std::swap(this->obj, other.obj);
        return *this;
    }
    /*
     const GeneratorBasePtr& operator=( GeneratorBasePtr other ) const
     {
     std::swap(this->obj, other.obj);
     //swap(other);
     return *this;
     }
    */
    
    T* operator->()
    {
        return obj;
    }
    
    const T* operator->() const
    {
        return obj;
    }
    
    operator bool() const
    {
        return obj!=nullptr;
    }
    
    T* Obj()
    {
        return obj;
    }
    const T* ConstObj() const
    {
        return obj;
    }
    template <class U>
    BaseCountedPtr<U> StaticCast()
    {
        BaseCountedPtr<U> casted( static_cast<U*>(this->Obj()) );
        return casted;
    }
    
private:
    mutable T* obj;
    
};


///
/// BaseCounted implementation
///
template <class T>
BaseCounted<T>::BaseCounted() : refCount(0)
{
    numAllocated++;
}

template <class T>
BaseCounted<T>::~BaseCounted()
{
    numAllocated--;
}

template <class T>
T * BaseCounted<T>::Aquire()
{
    assert (refCount >= 0);
    refCount++;
    return static_cast<T*>(this);
}

template <class T>
void BaseCounted<T>::Release()
{
    assert(refCount>0);
    if (--refCount == 0)
        delete this;
    else
    {
        assert(refCount > 0);
    }
}

template <class T>
int BaseCounted<T>::numAllocated = 0;	//debug

//DEBUG
template <class T>
void BaseCounted<T>::CheckMemFree()
{
    assert(numAllocated == 0);
}

