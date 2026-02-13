#include "Plotter.h"
#include "vector.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    PenStyle style={1,"black"};
    double x1=0,y1=0,x2,y2;
    bool state=0;
    for(string line ; getline(input,line);){
        Vector<string> todo=stringSplit(line," ");
        if(todo.size()==1 and todo[0]=="PenDown"){
            state=true;
        }else if(todo[0]=="PenUp"){
            state=false;
        }else if(todo[0]=="MoveAbs"){
            x2=stringToDouble(todo[1]),y2=stringToDouble(todo[2]);
            if(state){drawLine(x1,y1,x2,y2,style);}
            x1=x2,y1=y2;
        }else if(todo[0]=="MoveRel"){
            x2+=stringToDouble(todo[1]),y2+=stringToDouble(todo[2]);
            if(state){drawLine(x1,y1,x2,y2,style);}
            x1=x2,y1=y2;
        }else if(todo[0]=="PenWidth"){
            style.width=stringToDouble(todo[1]);
        }else if(todo[0]=="PenColor"){
            style.color=todo[1];
        }
    }
}
