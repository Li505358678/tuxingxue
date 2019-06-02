//
// Created by lh on 19-5-31.
//

#ifndef CG_TEST_MYPOINT_H
#define CG_TEST_MYPOINT_H

class MyPoint
{
public:
    int x;
    int y;
    int z;
    MyPoint(void);
    MyPoint(int m, int n, int o);
    void setPoint(int m, int n, int o);
    ~MyPoint(void);
};

MyPoint::MyPoint(void)
{
    x = y = z = 0;
}
MyPoint::MyPoint(int m, int n, int o)
{
    x = m;
    y = n;
    z = o;
}
void MyPoint::setPoint(int m, int n, int o)
{
    x = m;
    y = n;
    z = o;
}
MyPoint::~MyPoint(void){}

#endif //CG_TEST_MYPOINT_H
