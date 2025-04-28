#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <iostream>

template <typename T>
class my_shared_ptr
{
private:
    T* ptr;  //指向对象的指针
    int* ptr_count; //引用计数指针
public:
    //默认构造函数
    explicit my_shared_ptr(T*p=nullptr)
    :ptr(p)
    ,ptr_count(new int(1)) //引用计数初始化为1
    {
        //如果指针为空，引用计数初始化为0
        if(ptr == nullptr)
        {
            ptr_count = new int(0);
        }
        std::cout<<"my_shared_ptr默认构造\n";
    }
    //拷贝构造函数
    my_shared_ptr(const my_shared_ptr<T>& sp)
    {
       ptr=sp.ptr;
       ptr_count=sp.ptr_count;
       //引用计数加1
       (*ptr_count)++;
       std::cout<<"my_shared_ptr拷贝构造\n";
    }
    //拷贝赋值运算符重载
    my_shared_ptr<T>& operator=(const my_shared_ptr<T>& sp)
    {
        if(this != &sp) //自赋值检查
        {
            //引用计数减1
            (*ptr_count)--;
            if(*ptr_count == 0) //引用计数为0，释放内存
            {
                delete ptr;
                delete ptr_count;
            }
            ptr=sp.ptr;
            ptr_count=sp.ptr_count;
            //引用计数加1
            (*ptr_count)++;
        }
        std::cout<<"my_shared_ptr拷贝赋值\n";
        return *this;
    }
    //移动构造函数
    my_shared_ptr(my_shared_ptr<T>&& sp) noexcept
    {
        ptr=sp.ptr;
        ptr_count=sp.ptr_count;
        sp.ptr=nullptr;
        sp.ptr_count=nullptr;
        std::cout<<"my_shared_ptr移动构造\n";
    }
    //移动赋值运算符重载
    my_shared_ptr<T>& operator=(my_shared_ptr<T>&& sp) noexcept
    {
        if(this != &sp) //自赋值检查
        {
            //引用计数减1
            (*ptr_count)--;
            if(*ptr_count == 0) //引用计数为0，释放内存
            {
                delete ptr;
                delete ptr_count;
            }
            ptr=sp.ptr;
            ptr_count=sp.ptr_count;
            sp.ptr=nullptr;
            sp.ptr_count=nullptr;
        }
        std::cout<<"my_shared_ptr移动赋值\n";
        return *this;
    }
    //析构函数
    ~my_shared_ptr()
    {
        //引用计数减1
        (*ptr_count)--;
        if(*ptr_count == 0) //引用计数为0，释放内存
        {
            delete ptr;
            delete ptr_count;
        }
        std::cout<<"my_shared_ptr析构\n";
    }
    //重载*运算符
    T& operator*() const
    {
        return *ptr;
    }
    //重载->运算符
    T* operator->() const
    {
        return ptr;
    }
    //获取引用计数
    int use_count() const
    {
        return *ptr_count;
    }
    //获取原始指针
    T* get() const
    {
        return ptr;
    }
    //重载bool运算符
    operator bool() const
    {
        return ptr != nullptr;
    }
    //重载==运算符
    bool operator==(const my_shared_ptr<T>& sp) const
    {
        return ptr == sp.ptr;
    }
    //重载!=运算符
    bool operator!=(const my_shared_ptr<T>& sp) const
    {
        return ptr != sp.ptr;
    }
    //重载<运算符
    bool operator<(const my_shared_ptr<T>& sp) const
    {
        return ptr < sp.ptr;
    }
    //重载<=运算符
    bool operator<=(const my_shared_ptr<T>& sp) const
    {
        return ptr <= sp.ptr;
    }
    //重载>运算符
    bool operator>(const my_shared_ptr<T>& sp) const
    {
        return ptr > sp.ptr;
    }
    //重载>=运算符
    bool operator>=(const my_shared_ptr<T>& sp) const
    {
        return ptr >= sp.ptr;
    }

};

#endif // !MY_SHARED_PTR_H_
