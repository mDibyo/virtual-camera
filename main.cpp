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
  PTZFrame ptz_frame(input_size, 30);

//  VideoWriter writer(argv[2], CV_FOURCC('M','J','P','G'), 30, input_size);
//  if (!writer.isOpened()) {
//    printf("Could not open writer. Aborting.");
//    return -1;
//  }

  bool done = false;
  int key_pressed;
  Rect extracted_rect;

  namedWindow(VIDEO_DISPLAY_WINDOW_NAME, WINDOW_KEEPRATIO);
//  namedWindow("second window", WINDOW_AUTOSIZE);

  while (!done) {
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
//    writer << written;

    key_pressed = waitKey(30);
    if (key_pressed >= 0) {
      key_pressed = key_pressed & 255; // extract last 8 bits of key pressed
      switch (key_pressed) {
        case 83: // right
          ptz_frame.offsetPTZ(0.1, 0, 0);
          break;
        case 81: // left
          ptz_frame.offsetPTZ(-0.1, 0, 0);
          break;
        case 82: // up
          ptz_frame.offsetPTZ(0, 0.1, 0);
          break;
        case 84: // down
          ptz_frame.offsetPTZ(0, -0.1, 0);
          break;
        case 'a':
          ptz_frame.offsetPTZ(0, 0, 0.1);
          break;
        case 'z':
          ptz_frame.offsetPTZ(0, 0, -0.1);
          break;
        case 32: // space
          done = true;
          break;
        default:
          printf("%d\n", key_pressed);
          break;
      }
    }
  }
//  writer.release();

  return 0;
}