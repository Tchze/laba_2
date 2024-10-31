#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fun(double x){
    if(-4<=x&&x<-1){
        return abs(x-3)/fabs(pow(x,3)-5)-exp(x+1);
    }else if(2<=x&&x<5){
        return 3*x+1;
    }else if(10<=x&&x<=20){
        return 1/x;
    }else return (x-1);
}

int main(){
    double x;
    printf("Enter x:\n");
    scanf("%lf",&x);
    printf("%.3lf\n",fun(x));
}
