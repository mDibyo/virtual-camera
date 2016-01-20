#include "frame.hpp"

using namespace cv;


void PTZFrame::setPTZ(double new_point_angle, double new_tilt_angle, double new_zoom_setting) {
  zoom_setting = new_zoom_setting;
  if (zoom_setting < 1) {
    zoom_setting = 1;
  }
  output_size = Size_<double>(input_size) / zoom_setting;
  Size pan_tilt_range_size = (input_size - output_size) / 2;
  double max_abs_point_angle = atan((double) pan_tilt_range_size.width / (2 * distance));
  double max_abs_tilt_angle = atan((double) pan_tilt_range_size.height / (2 * distance));

  point_angle = new_point_angle;
  if (point_angle < -max_abs_point_angle) {
    point_angle = -max_abs_point_angle;
  } else if (point_angle > max_abs_point_angle) {
    point_angle = max_abs_point_angle;
  }

  tilt_angle = new_tilt_angle;
  if (tilt_angle < -max_abs_tilt_angle) {
    tilt_angle = -max_abs_tilt_angle;
  } else if (tilt_angle > max_abs_tilt_angle) {
    tilt_angle = max_abs_tilt_angle;
  }
}


void PTZFrame::getRect(Rect& rect) {
  Point rect_center((int) (distance * tan(point_angle)), (int) (distance * tan(tilt_angle)));
  if (rect_center.x < output_size.width/2) {
    rect_center.x = output_size.width/2;
  } else if (rect_center.x + output_size.width/2 > input_size.width) {
    rect_center.x = input_size.width - output_size.width/2;
  }
  if (rect_center.y < output_size.height/2) {
    rect_center.y = output_size.height/2;
  } else if (rect_center.y + output_size.height/2 > input_size.height) {
    rect_center.y = input_size.height - output_size.height/2;
  }

  rect = Rect(rect_center - output_size/2, output_size);
}