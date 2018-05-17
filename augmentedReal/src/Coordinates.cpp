//
//  Coordinates.cpp
//  lol
//
//  Created by Daniel Morales on 5/8/18.
//  Copyright © 2018 Daniel Morales. All rights reserved.
//

#include "Coordinates.hpp"

Coordinates::Coordinates(){
    dictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
    arucoSquareDimension = 0.0508f;
}

vector<vector<vector<float>>> Coordinates::getCoordinates(Mat image){

	rows = image.rows;
	cols = image.cols;	

	Mat cameraMatrix, distCoeffs;
	
	vector<Vec3d> rvecs, tvecs;

    	detectMarkers(image, dictionary, point2fMarkerCorners, markerIds);
    
     
    	return normalizedCoordinates();
}

vector<float> Coordinates::getMarkerCenter(){
    vector<float> f;
    return f;
}

vector<int> Coordinates::getMarkerIds(){
    return markerIds;
}


vector<vector<vector<float>>> Coordinates::normalizedCoordinates(){
			
	vector<vector<vector<float>>> cm;

	for(int i=0; i<point2fMarkerCorners.size(); i++){

		vector<vector<float>> m;

		for(int j=0; j<point2fMarkerCorners[0].size(); j++){
			vector<float> xAndY(2);
			xAndY[0] = (point2fMarkerCorners[i][j].x/(cols*1.0) - .5)*2;
			xAndY[1] = (point2fMarkerCorners[i][j].y/(rows*1.0) - .5)*2;
			m.push_back(xAndY);
		}

		cm.push_back(m);

	}
	
	return cm;
}
