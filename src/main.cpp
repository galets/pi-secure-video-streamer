#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat frame;

    // Open the default camera
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "Failed to open camera" << endl;
        return -1;
    }

    cap >> frame;
    if (frame.empty())
    {
        cerr << "ERROR! blank frame grabbed\n";
        return -1;
    }

    // Set the resolution of the camera
    // cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    auto rate = cap.get(CAP_PROP_FPS);

    // Create a VideoWriter object to save the video to disk
    VideoWriter writer("output.mp4", VideoWriter::fourcc('M', 'P', '4', 'V'),
                       rate, frame.size());

    if (!writer.isOpened())
    {
        cerr << "Failed to open video file for writing" << endl;
        return -1;
    }

    // Main loop to capture frames from the camera and write them to disk
    while (true)
    {
        cap.read(frame);
        if (frame.empty())
        {
            cerr << "Failed to capture frame" << endl;
            break;
        }

        writer.write(frame);
        imshow("Video", frame);

        // Exit the loop if the user presses the "q" key
        if (waitKey(1) == 'q')
        {
            break;
        }
    }

    // Release the camera and video writer
    cap.release();
    writer.release();

    return 0;
}
