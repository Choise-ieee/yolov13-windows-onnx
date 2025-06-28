
// Include necessary headers
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "YOLO12.hpp" 
#include <Windows.h>

int main() {

    // Configuration parameters
    const std::string labelsPath = "coco.names";       // Path to class labels
    const std::string modelPath = "yolov13l.onnx";     // Path to YOLO12 model
    const std::string imagePath = "data/dog.jpg";           // Path to input image
    bool isGPU = false;                                           // Set to false for CPU processing

    // Initialize the YOLO12 detector
    YOLO12Detector detector(modelPath, labelsPath, isGPU);

    while (1)
    {
        DWORD start_time = GetTickCount();

        // Load an image
        cv::Mat image = cv::imread(imagePath);

        // Perform object detection to get bboxs
        std::vector<Detection> detections = detector.detect(image);

        // Draw bounding boxes on the image
        detector.drawBoundingBoxMask(image, detections);

        DWORD end_time = GetTickCount();
        printf("The run time is:%dms\n", end_time - start_time);
    }
   

    // Display the annotated image
    //cv::imshow("YOLO12 Detections", image);
    cv::waitKey(0); // Wait indefinitely until a key is pressed

    return 0;
}

