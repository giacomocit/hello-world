#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ros/ros.h"

cv::VideoWriter video("outcpp.avi", CV_FOURCC('X','2','6','4'), 24000.0/1001.0, cv::Size(1280, 720));

void releaseResources() {
  video.release();
  cv::destroyAllWindows();
  ros::shutdown();
}

void videoFrameCallback(const sensor_msgs::ImageConstPtr& msg) {
  cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;
  video.write(img);
  cv::imshow("Frame", img);
  char c = (char) cv::waitKey(24000.0/1001.0);
  if (c == 27) releaseResources();
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "opencv_subscribe_video_node");
  ros::NodeHandle n;
  std::cerr << "subscribed to /videoFrame and saving video as outcpp.avi" << std::endl;
  ros::Subscriber sub = n.subscribe("/videoFrame", 1, videoFrameCallback);
  ros::spin();
  cv::destroyAllWindows();
  return 0;
}