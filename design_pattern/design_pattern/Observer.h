//
//  Observer.h
//  design_pattern
//
//  Created by dao on 12/26/17.
//  Copyright © 2017 dao. All rights reserved.
//

#ifndef Observer_h
#define Observer_h

#include <iostream>
#include <vector>
namespace observer{
using namespace std;

class AlarmListener
{
public:
    virtual void alarm() = 0;
};

class SensorSystem
{
    vector < AlarmListener * > listeners;
public:
    void attach(AlarmListener *al)
    {
        listeners.push_back(al);
    }
    void soundTheAlarm()
    {
        for (int i = 0; i < listeners.size(); i++)
            listeners[i]->alarm();
    }
};

class Lighting: public AlarmListener
{
public:
    /*virtual*/void alarm()
    {
        cout << "lights up" << '\n';
    }
};

class Gates: public AlarmListener
{
public:
    /*virtual*/void alarm()
    {
        cout << "gates close" << '\n';
    }
};

class CheckList
{
    virtual void localize()
    {
        cout << "   establish a perimeter" << '\n';
    }
    virtual void isolate()
    {
        cout << "   isolate the grid" << '\n';
    }
    virtual void identify()
    {
        cout << "   identify the source" << '\n';
    }
public:
    void byTheNumbers()
    {
        // Template Method design pattern
        localize();
        isolate();
        identify();
    }
};
// class inheri.  // type inheritance
class Surveillance: public CheckList, public AlarmListener
{
    /*virtual*/void isolate()
    {
        cout << "   train the cameras" << '\n';
    }
public:
    /*virtual*/void alarm()
    {
        cout << "Surveillance - by the numbers:" << '\n';
        byTheNumbers();
    }
};

int runDP()
{
    SensorSystem ss;
    Gates gate;
    Lighting light;
    Surveillance sur;
    ss.attach(&gate);
    ss.attach(&light);
    ss.attach(&sur);
    ss.soundTheAlarm();
    return 1;
}
}
#endif /* Observer_h */
