//
//  Coordinates.hpp
//  lol
//
//  Created by Daniel Morales on 5/8/18.
//  Copyright © 2018 Daniel Morales. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;
using namespace aruco;

class Coordinates{
public:
    Coordinates();
    vector<vector<vector<float>>> getCoordinates(Mat image);
    vector<float> getMarkerCenter();
    vector<int> getMarkerIds();
    vector<vector<vector<float>>> normalizedCoordinates();
private:
    int rows;
    int cols;
    float arucoSquareDimension;
    Ptr<Dictionary> dictionary;
    vector<int> markerIds;
    vector<vector<Point2f>> point2fMarkerCorners;
    vector<vector<float>> markerCorners;
};

#endif /* Coordinates_hpp */
