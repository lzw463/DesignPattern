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
//问题：不符合软件设计开闭原则
class Car
{
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

//工厂方法：继承结构，一个工厂生产一个产品
//问题：现在考虑一类产品（有关联关系的系列产品），工厂类太多太多
class Factory
{
public:
    virtual Car* createCar(string name) = 0; //工厂方法，负责车
    virtual Light* createCarLight() = 0; //工厂方法，负责灯
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
#endif


//系列产品2
class Light
{
public:
    virtual void show() = 0;
};
class BmwLight : public Light
{
public:
    void show() {cout << "BMW light" << endl;}
};
class AudiLight : public Light
{
public:
    void show() {cout << "Audi light" << endl;}
};



//抽象工厂（对有关联关系的产品组提供产品对象的统一创建）
//问题：基类工厂添加一个方法：所有子类必须重写



//简单工厂
//把对象的创建封装在一个接口函数中通过传入不同的标示，返回创建的对象
//客户不用自己负责new对象，不用了解对象创建的详细过程
//提供创建对象方法的接口函数不闭合，不能对修改关闭

//工厂方法
//提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的产品
//可以做到不同的产品在不同的工厂中创建，能够对现有工厂以及产品的修改关闭
//实际上很多产品是有关联关系的，属于一个产品组，不应该放在不用的工厂中去创建，导致工厂类太多了，不好维护

//抽象工厂
//把有关联关系的属于一个产品组的所有产品创建的接口函数放在一个抽象工厂里面
