#include <iostream>
#include <mutex>

using namespace std;

std::mutex mtx;

/*
单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
A *p1 = new A();
A *p2 = new A();
A *p3 = new A();
常用场景：日志模块，数据库模块(跟数据库服务器进行通信)

单例模式：
饿汉单例模式：还没有获取实例对象，实例对象就已经产生了
懒汉单例模式：唯一的实例对象，直到第一次获取它的时候，才产生
*/

# if 0
//饿汉式单例 一定是线程安全的，因为satic成员变量在main函数之前就已经创建好的
//缺点：没有使用对象就构造，初始化这个对象浪费资源
class Singleton
{
public:
    static Singleton* getInstance()  // #3 获取类的唯一实例对象的接口方法，声明为static就不需要依赖具体的对象来获取
    {
        return &instance;
    }
private:
    static Singleton instance; // #2 定义一个唯一的类的实例对象
    Singleton() {}  // #1 构造函数私有化，限制类对象的构造
    Singleton(const Singleton&) = delete;  // #4 限制拷贝构造
    Singleton& operator=(const Singleton&) = delete;
};

Singleton Singleton::instance;



// int main()
// {
//     Singleton *p1 = Singleton::getInstance();
//     Singleton *p2 = Singleton::getInstance();
//     Singleton *p3 = Singleton::getInstance();

//     Singleton t = *p1; //还是可以通过默认拷贝构造和赋值去创建对象，所以要限制拷贝构造和赋值
//     return 0;
// }




//懒汉单例模式=>不是线程安全的 =>线程安全的懒汉单例模式
class Singleton
{
public:
    //不是可重入函数(多线程中，一个函数没有执行完，能不能被另一个线程再调用一次，能则叫可重入)
    static Singleton* getInstance()  // #3 获取类的唯一实例对象的接口方法，声明为static就不需要依赖具体的对象来获取
    {
        //lock_guard<std::mutex> guard(mtx); 锁的粒度太大，单线程环境没必要一直加锁解锁
        if(instance == nullptr)
        {
            lock_guard<std::mutex> guard(mtx);
            if (instance == nullptr) 
            {
                /*
                开辟内存
                构造对象
                给instance赋值
                */
                instance = new Singleton();
            }
           
        }
        return instance;
    }
private:
    static Singleton *volatile instance; // #2 定义一个唯一的类的实例对象
    //volatile关键字：告诉编译器不要对这个变量的读写操作进行优化，多线程环境中一个线程修改的变量可能被其他线程读取，不对改变两缓存，所有线程看到的都是cpu里的值
    Singleton() {}  // #1 构造函数私有化，限制类对象的构造
    Singleton(const Singleton&) = delete;  // #4 限制拷贝构造
    Singleton& operator=(const Singleton&) = delete;
};

Singleton*volatile Singleton::instance = nullptr;

#endif


//精简的线程安全的懒汉单例模式
class Singleton
{
public:
    //不是可重入函数(多线程中，一个函数没有执行完，能不能被另一个线程再调用一次，能则叫可重入)
    static Singleton* getInstance()  // #3 获取类的唯一实例对象的接口方法，声明为static就不需要依赖具体的对象来获取
    {
        //函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
        static Singleton instance; // #2 定义一个唯一的类的实例对象，静态对象第一次运行到这才进行初始化
        return &instance;
    }
private:
    Singleton() {}  // #1 构造函数私有化，限制类对象的构造
    Singleton(const Singleton&) = delete;  // #4 限制拷贝构造
    Singleton& operator=(const Singleton&) = delete;
};
