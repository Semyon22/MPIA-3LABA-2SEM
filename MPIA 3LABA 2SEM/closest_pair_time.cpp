#include "closest_pair.h"
#include <iostream>
#include <random>
#include <numeric>
#include <chrono>

std::vector <Point> random_data(int size) {
    std::vector <Point> result;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-10, 10);
    for (int i = 0; i < size; i++) {
        result.push_back(Point(distribution(generator), distribution(generator)));
    }
    return result;
}

void measure_time() {
    const int N = 1e2;
    std::vector<Point> points = random_data(N);
    std::cout << "closest_pair_time: " << "N = " << N << ", " << "time = " << closest_pair_time(points) << std::endl;
    std::cout << "min_distance_time: " << "N = " << N << ", " << "time = " << min_distance_time(points) << std::endl;;
}

double closest_pair_time(std::vector<Point>& points) {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::pair<Point, Point> p = closest_pair(points);
    auto t2 = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(t2 - t1).count();
    return time;
}

double min_distance_time(std::vector<Point>& points) {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::pair<Point, Point> p;
    p = min_distance(points);
    auto t2 = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(t2 - t1).count();
    return time;
}