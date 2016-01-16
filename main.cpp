#include "opencv2/opencv.hpp"

using namespace cv;


int main(int argc, char** argv) {
  if ( argc != 2 ) {
    printf("usage: VirtualCamera.video <Video_Path>\n");
    return -1;
  }

  VideoCapture capture(argv[1]);
  namedWindow("Video display window", WINDOW_AUTOSIZE);

  for (;;) {
    Mat frame;
    capture >> frame;
    if (frame.empty()) break;
    imshow("Video display window", frame);
    if (waitKey(30) >= 0) break;
  }
  return 0;
}