///
//  Vase.cpp
//


#include <iostream>
#include <cmath>

using namespace std;

#include "Canvas.h"




void makeVase(Canvas &C) {
	
	int horiz_levels = 200;
	int vertical_levels = 200;

	int mincal = 50, maxcal = 100;//��С�ھ������ھ�
	double height = 380;//���廨ƿ�߶�
	int step = height / vertical_levels;
	float PI = 3.1415926;
	for (int i = -50; i < 330;i += step) {
		double r1 = mincal * sin(i / 180.0*PI) + maxcal;

		double r2 = mincal * sin((i + step) / 180.0*PI) + maxcal;

		for (int j = 0; j < horiz_levels;j++) { //ÿһ��Ļ���
			double angle1 = 360.0 / horiz_levels * j;
			double angle2 = 360.0 / horiz_levels * (j + 1);
			//���ɶ���v1,v2����Ƭi�� v3,v4����Ƭi+step�ϣ��ĸ��㹹��һ���Ľ���
			Vertex v1 = { r1*cos(angle1 / 180.0*PI), i, r1*sin(angle1 / 180.0*PI) };
			Vertex v2 = { r1*cos(angle2 / 180.0*PI), i, r1*sin(angle2 / 180.0*PI) };
			Vertex v3 = { r2*cos(angle2 / 180.0*PI), i + step, r2*sin(angle2 / 180.0*PI) };
			
			//���ɶ�Ӧ����������
			Normal t1 = { (double)j / horiz_levels, (i + 50) / height };
			Normal t2 = { (double)(j + 1) / horiz_levels, (i + 50) / height };
			Normal t3 = { (double)(j + 1) / horiz_levels, (i + step + 50) / height };
			
			



		}
	}
}