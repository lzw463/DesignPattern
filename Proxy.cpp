#include <iostream>
#include <memory>

using namespace std;


/*
代理Proxy模式（结构型模式）：通过代理类来控制实际对象的访问权限
客户     助理proxy     老板 委托类
*/

class VideoSite
{
public:
    virtual void freeMovie() = 0;
    virtual void vipMovie() = 0;
    virtual void ticketMovie() = 0;
};

class FixBugVideoSite : public VideoSite//委托类
{
public:
    virtual void freeMovie()
    {
        cout << "观看免费电影" << endl;
    }
    virtual void vipMovie()
    {
        cout << "观看vip电影" << endl;
    }
    virtual void ticketMovie()
    {
        cout << "观看用卷电影" << endl;
    }
};

//代理类
class FreeVideoSiteProxy : public VideoSite
{
public:
    FreeVideoSiteProxy() {pVideo = new FixBugVideoSite();}
    ~FreeVideoSiteProxy() {delete pVideo;}
    virtual void freeMovie()
    {
        pVideo->freeMovie(); //通过代理对象的freemovie访问委托对象的free
    }
    virtual void vipMovie()
    {
        cout << "不能观看vip电影" << endl;
    }
    virtual void ticketMovie()
    {
        cout << "需要使用券观看电影" << endl;
    }
private:
    VideoSite *pVideo;
};

int main()
{
    unique_ptr<VideoSite> p1(new FreeVideoSiteProxy());
    p1->freeMovie(); //没有权限控制
    p1->vipMovie();
    p1->ticketMovie(); 
    return 0;
}