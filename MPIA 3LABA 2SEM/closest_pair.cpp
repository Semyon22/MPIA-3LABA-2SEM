#include "closest_pair.h"

#include <stdexcept>

using namespace std;

std::pair<Point, Point> min_distance(const std::vector<Point>& points) {//������� ������ ���������� ���������
	if (points.size() == 2) {
		return std::make_pair(points[0], points[1]);
	}
	Point p1 = points[0];
	Point p2 = points[1];
	double min_d = p1.distance(p2);
	for (int i = 0; i < points.size() - 1; i++) {//������� ���� ��� ����� 
		for (int j = i + 1; j < points.size(); j++) {
			if (points[i].distance(points[j]) < min_d && points[i] != points[j]) {
				p1 = points[i];
				p2 = points[j];
				min_d = points[i].distance(points[j]);
			}
		}
	}
	return std::make_pair(p1, p2);
}

std::pair<Point, Point> closest_pair_between(const std::vector<Point>& pLeft, const std::vector<Point>& pRight, double d) {
	double xm = (pLeft[pLeft.size() - 1].x + pRight[0].x) / 2;//������� ����� PLeft � PRight �� x-����������
	vector<Point> pStripe;//������ �� ��� ����� �� PLeft � PRight, ������� ������� �� �-���������� �� Xm ����� ��� �� ���������� d
	for (int i = 0; i < pLeft.size(); i++) {
		if (abs(pLeft[i].x - xm) < d) {
			pStripe.push_back(pLeft[i]);
		}
	}
	for (int i = 0; i < pRight.size(); i++) {
		if (abs(pRight[i].x - xm) < d) {
			pStripe.push_back(pRight[i]);
		}
	}
	sort(pStripe.begin(), pStripe.end(), [](const Point& p1, const Point& p2) {
		return p1.y < p2.y;
		});//C��������� ����� � PStripe �� y-����������.
    if (pStripe.size() == 0) {
		return std::make_pair(pLeft[0], pRight[0]);
	}
	Point p1 = pStripe[0];
	Point p2 = pStripe[1];

	for (int i = 0; i < pStripe.size() - 1; i++) {//����� ��������� ����� � pStripe
		for (int j = i + 1; j < pStripe.size(); j++) {
			if (abs(pStripe[i].y - pStripe[j].y) < d) {
				p1 = pStripe[i];
				p2 = pStripe[j];
			}
		}
	}
	return std::make_pair(p1, p2);
}

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}
	vector<Point> points_t(points.begin(), points.end());
	sort(points_t.begin(), points_t.end(), [](const Point& p1, const Point& p2) {
		return p1.x < p2.x;
		});//���������� �� � ���������� 
	if (points_t.size() <= 3) {
		auto result = min_distance(points_t);
		return result;
	}
	else {
		std::vector<Point> pLeft;//������ ��� ����� ����� 
		std::vector<Point> pRight;//������ ��� ������ ����� 
		for (int i = 0; i < points_t.size() / 2; i++) {//���������� ����� ����� �������
			pLeft.push_back(points_t[i]);
		}
		for (int i = points_t.size() / 2; i < points_t.size(); i++) {
			pRight.push_back(points_t[i]);//���������� ������ ����� �������
		}
		std::pair<Point, Point> pl = closest_pair(pLeft);//���� ��������� ����� � ����� ��������
		std::pair<Point, Point> pr = closest_pair(pRight);//���� ��������� ����� � ������ ��������
		double pl_dist = pl.first.distance(pl.second);//��������� ��������� ����� ����� �������� 
		double pr_dist = pr.first.distance(pr.second);//��������� ��������� ����� ������ �������� 
		double d = min(pl_dist, pr_dist);//����� ��������� ���� ����� �� ������ �������� � �� ����� �������� 
		std::pair<Point, Point> pb = closest_pair_between(pLeft, pRight, d);// ���� ��������� ����� ����� ���������� PLeft � PRight.
        double pb_dist = pb.first.distance(pb.second);//������� ��������� ����� ����������� ������� 
		double min_dist = min(min(pl_dist, pr_dist), pb_dist);//����� ������������ ���������� ����� �������
		if (min_dist == pl_dist) {
			return pl;
		}
		if (min_dist == pr_dist) {
			return pr;
		}
		return pb;
	}
}