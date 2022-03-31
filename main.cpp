#include "opencv2/opencv.hpp"
#include <iostream>
#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <vitis/ai/demo.hpp>
#include <vitis/ai/tfssd.hpp>

using namespace cv;
using namespace std;
bool detected = 0;
bool tracker_init = 0;
Mat Detected_frame;
Mat frame;
int main(int argc, char** argv)
{
    VideoCapture cap(0);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
       auto network = vitis::ai::TFSSD::create("ssd_resnet_50_fpn_coco_tf");
     // List of tracker types in OpenCV 3.4.1
    string trackerTypes[8] = {"BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};
    // vector <string> trackerTypes(types, std::end(types));

    // Create a tracker
    string trackerType = trackerTypes[2];

    
    Ptr<Tracker> tracker;
        if (trackerType == "BOOSTING")
            tracker = TrackerBoosting::create();
        if (trackerType == "MIL")
            tracker = TrackerMIL::create();
        if (trackerType == "KCF")
            tracker = TrackerKCF::create();
        if (trackerType == "TLD")
            tracker = TrackerTLD::create();
        if (trackerType == "MEDIANFLOW")
            tracker = TrackerMedianFlow::create();
        if (trackerType == "GOTURN")
            tracker = TrackerGOTURN::create();
        if (trackerType == "CSRT")   
    while(true)
    {
          cap >> frame;
          //Resizing for densebox 320 by 360
          resize(frame, frame, Size(640,640));
          if (!detected){

          
          
          //Resizing for densebox 320 by 360
          
          //The VITIS-AI MAGIC
	      auto results = network->run(frame);
          //Drawing boxes around results
	    for(const auto &r : results.bboxes){
            auto label = r.label;
            auto x1 = r.x * frame.cols;
            auto y1 = r.y * frame.rows;
            auto width = r.width * frame.cols;
            auto height = r.height * frame.rows;
            auto x2 = x1 + width;
            auto y2 = y1 + height;
            auto score = r.score;

          Point pt1(x1, y1);
          // and its bottom right corner.
          Point pt2(x2, y2);
          
          if(label == 21 ){
            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0));
            std::cout << "RESULT: " << label << "\t" << x1 << "\t" << y1 << "\t" << width << "\t" << height << "\t" << score << std::endl;
            detected = 1;
            cow.ID = 1;
            cow.height = height;
            cow.width =  width;
            cow.x =  x1;
            cow.y =  y1;
          }
        }
    } else{
        if (!tracker_init){
            Rect2d bbox(cow.height,cow.width.cow.x,cow.y)
            tracker->init(frame, bbox);
            tracker_init = 1;
        }
        bool ok = tracker->update(frame, bbox);
        if (ok)
        {
            
            // Tracking success : Draw the tracked object
            rectangle(frame, bbox, Scalar( 0, 0, 255 ), 2, 1 );
            putText(frame, "Tracking Cow", Point(bbox.x,bbox.y), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255), 2);

        }
      std::cout << "RESULT: " << cow.ID << "\t" << cow.x << "\t" << cow.y << "\t" << cow.width << "\t" << cow.height << "\t" << std::endl;
      
    }
          resize(frame, frame, Size(640,480));
          imshow("Cattle Tracking", frame);
          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
         
    // the camera will be closed automatically upon exit
    // cap.close();
}
}