#ifndef VIRTUAL_CAMERA_FRAME_H
#define VIRTUAL_CAMERA_FRAME_H

#include <math.h> /* tan, atan */
#include "opencv2/opencv.hpp"

using namespace cv;

class PTZFrame {
  Size input_size;
  Size output_size;
  double distance;

  double point_angle;
  double tilt_angle;
  double zoom_setting;

public:
  PTZFrame(Size input_size, double distance) :
      input_size(input_size),
      output_size(input_size),
      distance(distance),
      point_angle(0.0),
      tilt_angle(0.0),
      zoom_setting(1.0) {};

  void setPTZ(double new_point_angle, double new_tilt_angle, double new_zoom_setting);

  void getRect(Rect& rect);

};


#endif //VIRTUAL_CAMERA_FRAME_H