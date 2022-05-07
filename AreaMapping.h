#ifndef ARDUINOROOMBA_AREAMAPPING_H
#define ARDUINOROOMBA_AREAMAPPING_H
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "ConvexHull.h"

class Segment{
        private:
            Point in, fin;
            int a, b, c;
        public:
            Segment(){}
            Segment(Point p1, Point p2){
                coord_t x1 = p1.x, y1 = p1.y;
                coord_t x2 = p2.x, y2 = p2.y;
                a = y2 - y1; b = x1 - x2;
                c = x1*(y1 - y2) + y1*(x2 - x1);
                in = p1; fin = p2;
            }

            int dist(Point p0){
                return abs(a*p0.x + b*p0.y + c) / (sqrt(pow(a,2) + pow(b,2)));
            }

        bool onSegment(Point q)
        {
            if (q.x <= std::max(in.x, fin.x) && q.x >= std::min(in.x, fin.x) &&
                q.y <= std::max(in.y, fin.y) && q.y >= std::min(in.y, fin.y))
                return true;

            return false;
        }
        static int orientation(Point p, Point q, Point r)
        {
            // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
            int val = (q.y - p.y) * (r.x - q.x) -
                      (q.x - p.x) * (r.y - q.y);

            if (val == 0) return 0;

            return (val > 0)? 1: 2;
        }
        bool doIntersect(Segment s)
        {

            int o1 = orientation(in, fin, s.getInizio());
            int o2 = orientation(in, fin, s.getFine());
            int o3 = orientation(s.getInizio(), s.getFine(), in);
            int o4 = orientation(s.getInizio(), s.getFine(), fin);

            if (o1 != o2 && o3 != o4)
                return true;

            if (o1 == 0 && onSegment(s.getInizio())) return true;
            if (o2 == 0 && onSegment(s.getFine())) return true;
            if (o3 == 0 && s.onSegment(in)) return true;
            if (o4 == 0 && s.onSegment(fin)) return true;

            return false;
        }

    std::string tostring(){
                return "\nInizio: " + in.tostring() + "Fine: " + fin.tostring() + "\n" + "a: " + std::to_string(a) + " b: " + std::to_string(b) + " c: " + std::to_string(c) + "\n-----------------\n";
            }
            Point getInizio(){
                return in;
            }
            Point getFine(){
                return fin;
            }

        };

class Polygon{
    protected:\
        std::vector<Segment> perimeter;
    public:
    Polygon(){};
    explicit Polygon(std::vector<Point> points){
            points.insert(points.end(), points.operator[](0));
            for (int i = 0; i < points.size()-1; i++){
                    Segment l (points.operator[](i), points.operator[](i+1) );
                    perimeter.push_back(l);
                }
            }
        std::string tostring(){
            std::string out = "";
            for(auto &s : perimeter){
                out += s.tostring();
            }
            return out;
        }
        std::vector<Segment> getPerimeter(){
            return perimeter;
        }

        bool isInside(Point point, int diameter){
            int count = 0;
            Segment s = Segment(Point(point.x, point.y), Point(+100, point.y) );
            for (Segment &w : perimeter){
                if(w.dist(point) < diameter){
                    return false;
                }
                if (w.onSegment(point)){
                    return false;
                }
                if(w.doIntersect(s)){
                    count++;
                };
            }
            if(count%2 == 0){
                return false;
            }
    }
        Segment closest(Point point){
            //segmento più vicino al punto
            Segment min = perimeter.operator[](0);
            for(auto &s : perimeter){
                if(s.dist(point) < min.dist(point)){
                    min = s;
                }
            return min;
            }
        }
    };

class MapArea{
    public:
        Polygon walls;
        std::vector<Polygon> obstacles;
        MapArea(){};

        MapArea(Polygon w){
            walls = w;
        }
        MapArea(Polygon w, std::vector<Polygon> obst ){
            walls = w;
            obstacles = obst;
        }

        bool validPoint(Point point, int diameter){
            if(!walls.isInside(point, diameter)){
                return false;
            }
            int i = 0;
            if(!obstacles.empty()) {
                while (i < obstacles.size()) {
                    if(obstacles.operator[](i).isInside(point, diameter)){
                       return false;
                    };
                    i++;
                }
            }
            return true;
        }
};


#endif