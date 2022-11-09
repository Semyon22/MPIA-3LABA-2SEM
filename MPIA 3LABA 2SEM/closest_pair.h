#pragma once
#include "point.h"

#include <vector>
#include <algorithm>

std::pair<Point, Point> min_distance(const std::vector<Point>& points);
std::pair<Point, Point> closest_pair_between(const std::vector<Point>& pLeft, const std::vector<Point>& pRight, double d);
std::pair<Point, Point> closest_pair(const std::vector<Point>& points);

std::vector <Point> random_data(int size);
void measure_time();
double closest_pair_time(std::vector<Point>& points);
double min_distance_time(std::vector<Point>& points);




