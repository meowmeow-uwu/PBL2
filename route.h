#ifndef ROUTE_H
#define ROUTE_H

#include<string.h>
#include<iostream>
using namespace std;
enum RouteStatus { OFF = 0, ONL = 1 };  // Enum for truck status

struct Point{
    string diemDem;
    string status;
    int stt;
    Point* next;

    Point(string diem): diemDem(diem), status("chua den noi"), next(nullptr){}
};

class Route{
    private:
        Point* head;
        string status;
    public:
        Route():head(nullptr), status("off"){}

        //getter
        void setRouteStatus(RouteStatus newStatus){ status = newStatus;}
        string getStatus(){return status;}

        void addPoint(const string& kho, int pos);


        void erasePoint(int pos);

        void showRoute();
        Point* getPoint();

        void finishPont();

};


#endif