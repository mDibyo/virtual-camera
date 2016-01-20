#include "opencv2/opencv.hpp"

#include "frame.hpp"

using namespace cv;


const String VIDEO_DISPLAY_WINDOW_NAME = "Video display window";

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage: VirtualCamera.inputVideo <Video_Path> VirtualCamera.outputVideo <Video_Path>\n");
    return -1;
  }

  VideoCapture capture(argv[1]);

  Size input_size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH), (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  PTZFrame ptz_frame(input_size, 10);
//  Size output_size(input_size.width/2, input_size.height/2);

//  VideoWriter writer(argv[2], CV_FOURCC('M','J','P','G'), 30, input_size);
//  if (!writer.isOpened()) {
//    printf("Could not open writer. Aborting.");
//    return -1;
//  }

  Rect extracted_rect;

  namedWindow(VIDEO_DISPLAY_WINDOW_NAME, WINDOW_KEEPRATIO);
//  namedWindow("second window", WINDOW_AUTOSIZE);

  for (;;) {
    Mat frame;
    capture >> frame;
    if (frame.empty()) {
      break;
    }

    ptz_frame.getRect(extracted_rect);
    Mat extracted(frame, extracted_rect);

    // Show video and write to new video
//    imshow("second window", frame);
    imshow(VIDEO_DISPLAY_WINDOW_NAME, extracted);
//    Mat written = extracted.clone();
//    writer.write(written);
//    writer << written;

    if (waitKey(30) >= 0) {
      break;
    }
  }
//  writer.release();

  return 0;
}