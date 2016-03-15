#include <random>
#include <fstream>
#include <iostream>
#include <time.h>
#include <math.h>
#include <bitset>
#include <map>
#include <opencv.hpp>
using namespace cv;
using namespace std;
int L = 0,
	d = 1;
const int K = 2,	
	I = 4;

double tn = 1,
	tc = 1,
	ts = 1,
  koef = 0.5;
double r = 0;

struct MyPoint
{
	double x;
	double y;
	int type;
  MyPoint() : x(0), y(0), type(0) {};
  MyPoint(double _x, double _y) : x(_x), y(_y) { type = 0; };
};

struct Claster
{
  MyPoint center;
  vector<MyPoint> MyPoints;
  double radius;
  MyPoint sigma;
  double maxsigma;  
  bool isMerged;
  Claster() : radius(0), maxsigma(0), isMerged(0){};
};

vector<Claster> clasters;

vector<MyPoint> study;

vector<vector<double>> dist;

struct ClastersPairs
{
  int first;
  int second;
  double dist;
  ClastersPairs() : first(0), second(0), dist(0) {};
};

vector<ClastersPairs> distances;



default_random_engine generator(time(0));
void generateNumbers(vector<MyPoint> &temp, double m1, double sigma1, double m2, double sigma2, int size)
{
	normal_distribution<double> normdist1(m1, sigma1);
	normal_distribution<double> normdist2(m2, sigma2);
	for (int i = 0; i < size; ++i)
	{
		MyPoint tempMyPoint;
		tempMyPoint.type = 0;
		tempMyPoint.x = normdist1(generator);
		tempMyPoint.y = normdist2(generator);
		temp.push_back(tempMyPoint);
	}	
}

void p2()
{
  clasters.resize(d);
	for (int i = 0; i < d; ++i)
	{
		bitset<1000> isused;
		int index = 0;
		while (true)
		{
			index = rand()%study.size();
			//index = 0;
			if (!isused[index])
				break;
		}
		isused.set(index);
    clasters[i].center = study[index];
    clasters[i].center.type = i + 1;
    study[index].type =  i + 1;  
	//clasters[i].MyPoints.push_back(study[i]);
	clasters[i].MyPoints.push_back(study[index]);
  }
}

void typetonul()
{
	for (int i = 0; i < study.size(); ++i)
		study[i].type = 0;

	for (int i = 0; i < clasters.size(); ++i)
	{
		clasters[i].isMerged = false;
		clasters[i].maxsigma = 0;
		clasters[i].MyPoints.clear();
		clasters[i].radius = 0;
		clasters[i].sigma.x = 0;
		clasters[i].sigma.y = 0;
	}

	distances.clear();

}


void p3() 
{
	for (int i = 0; i < study.size(); ++i)
	{
		if (study[i].type == 0)
		{
			double mindist = INT_MAX;
			int centertype = 0;
			for (int j = 0; j < d; ++j)
			{
				double dist = sqrt(pow(study[i].x - clasters[j].center.x, 2) + pow(study[i].y - clasters[j].center.y, 2));
				if (dist < mindist)
				{
					mindist = dist;
					//centertype = centrals[j].type;
          centertype = j;
				}
			}
			study[i].type = 1;
      clasters[centertype].MyPoints.push_back(study[i]);      
			//centernum[centertype]++;
		}
	}

}
void p4()
{
  for (int i = 0; i < d; ++i)
  {
    if (clasters[i].MyPoints.size() < tn)
    {
      for (int j = 0; j < study.size(); ++j)
        if (study[j].type == i + 1)
        {
          study[j].type = 0;
          break;
        }
      d--;
      clasters.erase(clasters.begin() + i);
    }    
  }
}

//кластеры удал€ютс€ из того места, где были

void p5()
{
  for (int i = 0; i < clasters.size(); ++i)
  {
	  clasters[i].center.x = 0;
	  clasters[i].center.y = 0;
    for (int j = 0; j < clasters[i].MyPoints.size(); ++j)
    {
      clasters[i].center.x += clasters[i].MyPoints[j].x;
      clasters[i].center.y += clasters[i].MyPoints[j].y;
    }
    clasters[i].center.x /= (clasters[i].MyPoints.size());
    clasters[i].center.y /= (clasters[i].MyPoints.size());
  }

}

void p6()
{
  for (int i = 0; i < clasters.size(); ++i)
  {
    for (int j = 0; j < clasters[i].MyPoints.size(); ++j)
    {
      clasters[i].radius += sqrt(pow((clasters[i].MyPoints[j].x - clasters[i].center.x), 2) + pow((clasters[i].MyPoints[j].y - clasters[i].center.y), 2));
    }
    clasters[i].radius /= (clasters[i].MyPoints.size()); 
  }
}

void p7()
{
  for (auto i : clasters)
  {
    r += i.radius * i.MyPoints.size();
  }
  r /= study.size();

}

void p9()
{
  for (int j = 0; j < clasters.size(); ++j) //j
  {
    for (int i = 0; i < clasters[j].MyPoints.size(); ++i)
    {
      clasters[j].sigma.x += pow((clasters[j].MyPoints[i].x - clasters[j].center.x), 2);
      clasters[j].sigma.y += pow((clasters[j].MyPoints[i].y - clasters[j].center.y), 2);
    }
    clasters[j].sigma.x = sqrt(clasters[j].sigma.x / clasters[j].MyPoints.size());
    clasters[j].sigma.y = sqrt(clasters[j].sigma.y / clasters[j].MyPoints.size());
  }
}
void p10()
{
	for (int i = 0; i < clasters.size(); ++i)
		(clasters[i].sigma.x > clasters[i].sigma.y) ? clasters[i].maxsigma = clasters[i].sigma.x : clasters[i].maxsigma = clasters[i].sigma.y;
}

void p11()
{
	//for (int i = 0; i < clasters.size(); ++i)
	int i = 0;	
	int oldd = d;
	while (i < oldd)
	{
		if (clasters[i].maxsigma > ts && ((clasters[i].radius < r && clasters[i].MyPoints.size() > 2 * (tn + 1)) || d <= K / 2))
			//расщепление
		{
			d++;
			Claster cl_plus,
				cl_minus;

			if (clasters[i].sigma.x > clasters[i].sigma.y)
			{
				cl_plus.center.x = clasters[i].center.x + koef * clasters[i].sigma.x;
				cl_minus.center.x = clasters[i].center.x - koef * clasters[i].sigma.x;
				cl_plus.center.y = cl_minus.center.y = clasters[i].center.y;
			}
			else
			{
				cl_plus.center.y = clasters[i].center.y + koef * clasters[i].sigma.y;
				cl_minus.center.y = clasters[i].center.y - koef * clasters[i].sigma.y;
				cl_plus.center.x = cl_minus.center.x = clasters[i].center.x;
			}
			clasters[i] = cl_plus;
			clasters.push_back(cl_minus);
			
		}
    i++;
	}

}


void p12()
{
  for (int i = 0; i < clasters.size(); ++i)
    for (int j = i + 1; j < clasters.size(); ++j)
    {
      ClastersPairs temp;
      temp.first = i;
      temp.second = j;
      temp.dist = sqrt(pow((clasters[i].center.x + clasters[j].center.x), 2) + pow((clasters[i].center.y + clasters[j].center.y), 2));
      distances.push_back(temp);
    }

}

void p13()
{
	vector<ClastersPairs> distanceslessts;
	int l = 0;
	for (auto i : distances)
	{
		if (i.dist < ts && l < L)
		{
			l++;
			distanceslessts.push_back(i);
		}
	}

	if (distanceslessts.size() > 1)
		for (int i = 0; i < distanceslessts.size() - 1; ++i)
			for (int j = 0; j < distanceslessts.size() - i - 1; ++j)
				if (distanceslessts[j].dist > distanceslessts[j + 1].dist)
					swap(distanceslessts[j], distanceslessts[j + 1]);
	distances.clear();
	distances = distanceslessts;
}


void p14()
{
  for (int i = 0; i < distances.size(); ++i)
  {
    if (!clasters[distances[i].first].isMerged && !clasters[distances[i].second].isMerged)
    {
      clasters[distances[i].first].isMerged = true;
      clasters[distances[i].second].isMerged = true;

      d--;

      Claster newcl;
      newcl.center.x = (clasters[distances[i].first].center.x * clasters[distances[i].first].MyPoints.size() + 
        clasters[distances[i].second].center.x * clasters[distances[i].second].MyPoints.size()) / (clasters[distances[i].second].MyPoints.size() + clasters[distances[i].first].MyPoints.size());
      newcl.center.y =(clasters[distances[i].first].center.y * clasters[distances[i].first].MyPoints.size() + 
        clasters[distances[i].second].center.y * clasters[distances[i].second].MyPoints.size()) / (clasters[distances[i].second].MyPoints.size() + clasters[distances[i].first].MyPoints.size());
      
      clasters[distances[i].first] = newcl;
      clasters.erase(clasters.begin() + distances[i].second);
    }
  }
}


void p8()
{
	p2();
	for (int i = 1; i <= I; ++i)
	{
		if (i > 1)
      typetonul();
		p3();
		p4();
		p5();
		p6();
		p7();
		p9();
		p10();
		if (i == I)
			tc = 0;
		else if (i % 2 != 0 && !(d >= 2*K))
		//else if (d <= K / 2 || !(i % 2 == 0 || d >= 2 * K))
		{
			p11();
		}
		p12();
		p13();
		p14();
	}
}


void print()
{

  for (auto i : clasters)
    cout << i.center.x << "  " << i.center.y << endl;
}

void printCV()
{
  int height = 300,
    width = 300;
  CvPoint point = cvPoint( height/2, width/2 );
  IplImage* hw = cvCreateImage(cvSize(width, height), 8, 3);
  cvSet(hw, cvScalar(255, 255, 255));
  
  //

  cvNamedWindow("smth");
  cvShowImage("smth1", hw);
  cvWaitKey();
  cvReleaseImage(&hw);
  cvDestroyAllWindows();
}


int main()
{
  generateNumbers(study, 0, 2, 0, 2, 100);
  /*MyPoint x1(0, 0),
    x2(1, 1),
    x3(2, 2),
    x4(4, 3),
    x5(4, 4),
    x6(5, 3),
    x7(5, 4),
    x8(6, 5);
  study.push_back(x1);
  study.push_back(x2);
  study.push_back(x3);
  study.push_back(x4);
  study.push_back(x5);
  study.push_back(x6);
  study.push_back(x7);
  study.push_back(x8);*/
  p8();
  //print();
  printCV();
	return 0;
}
