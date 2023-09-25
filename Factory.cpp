#include <iostream>
#include <string>
#include <memory>

using namespace std;


/*
简单工厂 Simple Factory
工厂方法 Factory Method
抽象工厂 Abstract Factory

创建型模式
工厂模式：主要是封装了对象的创建
*/

#if 0
//简单工厂
class Car
{//volatile关键字：告诉编译器不要对这个变量的读写操作进行优化，多线程环境中一个线程修改的变
public:
    Car(string name) : _name(name) {} 
    virtual void show() = 0;
private:
    string _name;
};

class Bmw : public Car
{
public:
    Bmw(string name) : Car(name) {}
    void show()
    {
        cout << "获取了一辆宝马汽车" << _name << endl;
    }
};

class Audi : public Car
{
public:
    Audi(string name) : Car(name) {}
    void show()
    {
        cout << "获取了一辆奥迪汽车" << _name << endl;
    }
};

enum CarType
{
    BMW,AUDI
};
class SimpleFactory
{
public:
    Car* createCar(CarType ct) //软件设计 “开闭原则“ 对修改关闭，对扩展开放
    {
        switch (ct)
        {
        case BMW:
            return new Bmw("X1");
        case AUDI:
            return new Audi("A6");
        default:
            cerr << "参数不正确" << ct << endl;
            break;
        }
        return nullptr
    }

};

int main()
{
    // Car *p1 = new BMW("X1");
    // Car *p2 = new Audi("A6");
    unique_ptr<SimpleFactory> factory(new SimpleFactory());
    unique_ptr<Car> p1(factory->createCar(BMW));
    p1->show();

    return 0;  
}
# endif

//工厂方法：继承结构，一个工厂生产一个产品
class Factory
{
public:
    virtual Car* createCar(string name) = 0;
};
//宝马工厂
class BMWFactory : public Factory
{
public:
    Car* createCar(string name)
    {
        return new Bmw(name);
    }
};
//奥迪工厂
class AudiFactory : public Factory
{
public:
    Car* createCar(string name)
    {
        return new Audi(name);
    }
};