#include "AutoShutDown.h"

AutoShutDown::AutoShutDown()
{
    //ctor
}

AutoShutDown::~AutoShutDown()
{
    //dtor
}
void AutoShutDown::setup()
{
    time_t rawtime;
    struct tm * timeinfo;
    int year = ofGetYear();
    int month = ofGetMonth();
    int day = ofGetDay();
    char * weekday[] = { "Sunday", "Monday",
                         "Tuesday", "Wednesday",
                         "Thursday", "Friday", "Saturday"
                       };
    /* get current timeinfo and modify it to the user's choice */
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_mday = day;
    /* call mktime: timeinfo->tm_wday will be set */
    mktime ( timeinfo );
    printf ("That day is a %s.\n", weekday[timeinfo->tm_wday]);
    todayWeekDay = timeinfo->tm_wday;
    ofLog(OF_LOG_WARNING,"AutoShutDown: todayWeekDay = %i",todayWeekDay);
    startThread(true,false);

}
void AutoShutDown::threadedFunction()
{
    while ( isThreadRunning() != 0 )
    {
        if ( lock() )
        {
            unlock();

            for (vector<DateAndTimes*>::iterator it = dnt.begin(); it!=dnt.end(); ++it)
            {
                DateAndTimes *_dnt=*it;
                if (	ofGetHours()==_dnt->hour && ofGetMinutes()==_dnt->minutes)
                {
                    for (int i = 0 ; i < _dnt->weekday.size(); i++)
                    {
                        if (todayWeekDay== _dnt->weekday[i])
                        {
                            ofLog(OF_LOG_WARNING,"AutoShutDown: Time Match %i:%i exit Now ",ofGetHours(),ofGetMinutes());
                            //shut down system in 2 mintues
                            system("shutdown -s -t 120 -c \"You better finish, system will sthu down within 2 minutes!\"");
                            stopThread();
                            std::exit(0);
                        }
                    }
                }
            }
            ofSleepMillis(1 * 1000);

        }

    }
}
void AutoShutDown::pushData(DateAndTimes* _new_dnt)
{
    dnt.push_back(_new_dnt);
}
