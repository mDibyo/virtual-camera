#include "opencv2/opencv.hpp"

using namespace cv;


int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage: VirtualCamera.inputVideo <Video_Path> VirtualCamera.outputVideo <Video_Path>\n");
    return -1;
  }

  VideoCapture capture(argv[1]);

  Size size = Size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH),
                   (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  printf("Output file: %s", argv[2]);
  VideoWriter writer(argv[2], CV_FOURCC('M','J','P','G'), capture.get(CV_CAP_PROP_FPS), size);
  if (!writer.isOpened()) {
    printf("Could not open writer. Aborting.");
    return -1;
  }

  namedWindow("Video display window", WINDOW_AUTOSIZE);

  for (;;) {
    Mat frame;
    capture >> frame;
    if (frame.empty()) {
      break;
    }

    // Show video and write to new video
    imshow("Video display window", frame);
    writer << frame;

    if (waitKey(30) >= 0) {
      break;
    }
  }
  writer.release();

  return 0;
}