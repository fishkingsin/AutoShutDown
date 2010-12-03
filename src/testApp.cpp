#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofxXmlSettings xml;
    ofLogLevel(OF_LOG_VERBOSE);
    if ( xml.loadFile("config.xml"))
    {
       printf("config.xml loaded\n");
    }
    else
    {
       printf("Could not Found arconfig.xml\n");
    }



    if (xml.pushTag("SHUTDOWN_SETTING"))
    {
        int numTag = xml.getNumTags("SHUTDOWN");
        char * weekday[] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"
                           };
        int raw_data = 0;
        for (int i = 0 ; i < numTag; i++)
        {
            DateAndTimes *_new_data = new DateAndTimes();

            raw_data = xml.getAttribute("SHUTDOWN","time",0,i);
            string week_string = xml.getAttribute("SHUTDOWN","weekday"," ",i);

            _new_data->hour  = raw_data/100;
            _new_data->minutes = raw_data%100;

            ofLog(OF_LOG_WARNING,"AutoShutDown: _new_data->hour %i",_new_data->hour);
            ofLog(OF_LOG_WARNING,"AutoShutDown: _new_data->minutes %i",_new_data->minutes);



            for (int j = 0 ;j < week_string.length() ; j++)
            {
                int weekdayi = (int)week_string[j] - 48;
                //vector<int>weekday;
                ofLog(OF_LOG_VERBOSE,"AutoShutDown :input weekday %s",weekday[weekdayi]);
                _new_data->weekday.push_back(weekdayi);
            }
            if (_new_data->hour <=24 && _new_data->minutes <=60 && week_string!=" ")
            {
                autoShutDown.pushData(_new_data);
            }

        }
        autoShutDown.setup();
        xml.popTag();
    }
}

//--------------------------------------------------------------
void testApp::update(){
}


//--------------------------------------------------------------
void testApp::draw(){
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

