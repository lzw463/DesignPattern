#include <iostream>

using namespace std;

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