#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tiobj.hpp>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <stdio.h>
#include <tiobj-cv.hpp>

using namespace std;
using namespace cv;


vector<std::string> loadFolder(std::string url){
	DIR *dir;
	struct dirent *ent;
	vector<std::string> names;
	if (   (  dir = opendir(url.c_str())  ) != NULL   ){
		while ((ent = readdir (dir)) != NULL) {
			if ( ent->d_name[0] == '.' )
				continue;
			names.push_back(ent->d_name);
		}
		closedir (dir);
	}
	std::sort(names.begin(), names.end());
	return names;
}




int main(){
	TiObj params( getenv("params") );
	int freq   = params.atInt("freq",10);


	string left_path  = "const/" + params.atStr("left", ".");
	string right_path = "const/" + params.atStr("right", ".");
	unsigned sleep_time = 1000000 / freq;


	vector<std::string> left_names = loadFolder(left_path);
	vector<std::string> right_names = loadFolder(right_path);


	Mat left, right;
	TiObj p_left, p_right;
	for (int i=0; i<right_names.size(); i+=1){
		string left_url  = left_path +"/" + left_names[i];
		string right_url = right_path + "/" + right_names[i];
		
		left = imread(left_url);
		right = imread(right_url);
		
		p_left << left;
		p_right << right;
		
		p_left.save("left", true);
		p_right.save("right", true);
		
		printf("#end\n");
		fflush(stdout);
		usleep( sleep_time );
	}


	return 0;
}
