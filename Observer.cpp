#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

/*
行为型模式：主要关注的是对象之间的通信
观察者-监听者模式（发布-订阅模式）
主要关注的是对象的一对多关系
多个对象都依赖一个对象，当该对象的状态发生改变时，其他所有对象都能接收到相应的通知

一组数据（对象） => 通过这一组数据=>曲线图（对象1）/柱状图（对象2）/圆饼图（对象3）
当数据对象改变时，对象123应该及时收到相应的通知

Observer1  Observer1  Observer1

           subject(主题)主题有更改及时通知相应的观察者
*/



class Observer //观察者抽象类
{
public:
    //处理消息的接口
    virtual void handle(int msgid) = 0;
};

class Observer1 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 1:
            cout << "observer1 recv 1 msg" << endl;
            break;
        case 2:
            cout << "observer1 recv 2 msg" << endl;
            break;
        default:
            cout << "observer1 recv unknown msg" << endl;
        }
    
    }
};

class Observer2 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 2:
            cout << "observer2 recv 2 msg" << endl;
            break;
        default:
            cout << "observer1 recv unknown msg" << endl;
        }
    
    }
};



class Observer3 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 1:
            cout << "observer3 recv 1 msg" << endl;
            break;
        case 3:
            cout << "observer3 recv 3 msg" << endl;
            break;
        default:
            cout << "observer3 recv unknown msg" << endl;
        }
    
    }
};

class Subject
{
public:
    //给主题增加观察者对象
    void addObserver(Observer* obser, int msgid)
    {
        _subMap[msgid].push_back(obser);
    }

    //主题监测发生改变，通知相应的观察者对象处理事件
    void dispatch(int msgid)
    {
        auto it = _subMap.find(msgid);
        if (it != _subMap.end())
        {
            for (Observer *pObser : it->second)
            {
                pObser->handle(msgid);
            }
        }
    }
private:
    unordered_map<int, list<Observer*>> _subMap;
};

int main()
{
    Subject subject;
    Observer *p1 = new Observer1();
    Observer *p2 = new Observer2();
    Observer *p3 = new Observer3();

    subject.addObserver(p1, 1);
    subject.addObserver(p1, 2);
    subject.addObserver(p2, 2);
    subject.addObserver(p3, 1);
    subject.addObserver(p3, 3);

    int msgid = 0;
    for(;;)
    {
        cout << "输入消息id";
        cin >> msgid;
        if (msgid == -1)
            break;
        subject.dispatch(msgid);
    }
    return 0;
}