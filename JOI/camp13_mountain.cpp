#include "grader.h"

void Rescue(int R, int C, int RS, int CS, int X){
    int px = 1, py = CS;
    while (px <= RS && py) {
        int t = Measure(px,py);
        if(t < X){
            px++;
        }
        else if(t > X){
            py--;
        }
        else{
            Pinpoint(px,py);
            return;
        }
    }
    px = R, py = CS;
    while (px >= RS && py) {
        int t = Measure(px,py);
        if(t < X){
            px--;
        }
        else if(t > X){
            py--;
        }
        else{
            Pinpoint(px,py);
            return;
        }
    }
    px = 1, py = CS;
    while (px <= RS && py <= C) {
        int t = Measure(px,py);
        if(t < X){
            px++;
        }
        else if(t > X){
            py++;
        }
        else{
            Pinpoint(px,py);
            return;
        }
    }
    px = R, py = CS;
    while (px >= RS && py <= C) {
        int t = Measure(px,py);
        if(t < X){
            px--;
        }
        else if(t > X){
            py++;
        }
        else{
            Pinpoint(px,py);
            return;
        }
    }
}