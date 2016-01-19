#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


const String VIDEO_DISPLAY_WINDOW_NAME = "Video display window";

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage: VirtualCamera.inputVideo <Video_Path> VirtualCamera.outputVideo <Video_Path>\n");
    return -1;
  }

  VideoCapture capture(argv[1]);

  Size input_size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH), (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  Size output_size(400, input_size.height/2);

  VideoWriter writer(argv[2], CV_FOURCC('M','J','P','G'), 30, output_size);
  if (!writer.isOpened()) {
    printf("Could not open writer. Aborting.");
    return -1;
  }

  Rect extracted_rect(0, 10, output_size.width, output_size.height);

  namedWindow(VIDEO_DISPLAY_WINDOW_NAME, WINDOW_AUTOSIZE);

  for (;;) {
    Mat frame;
    capture >> frame;
    if (frame.empty()) {
      break;
    }

    Mat extracted(frame, extracted_rect);

    // Show video and write to new video
    imshow(VIDEO_DISPLAY_WINDOW_NAME, extracted);
    Mat written = extracted.clone();
//    writer.write(written);
    writer << written;

    if (waitKey(30) >= 0) {
      break;
    }
  }
  writer.release();

  return 0;
}