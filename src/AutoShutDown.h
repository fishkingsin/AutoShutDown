#ifndef AUTOSHUTDOWN_H
#define AUTOSHUTDOWN_H

#include "ofxThread.h"
#include "ofMain.h"

struct DateAndTimes
{
    public:
    int hour;
    int minutes;
    vector<int>weekday;
};
class AutoShutDown : public ofxThread
{
    public:
        AutoShutDown();
        virtual ~AutoShutDown();
        void setup();
		void threadedFunction();
		void pushData(DateAndTimes* _new_dnt);
    private:
    vector<DateAndTimes*>dnt;
  	int todayWeekDay;
};

#endif // AUTOSHUTDOWN_H
