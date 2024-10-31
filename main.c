#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double integrand_expression(double x){
    return 1/(2*x+1.5);
}

double num_comput_integral_l_re(double x1,double x2,unsigned int n){
    double integral_s=0,h=(x2-x1)/n;
    for(int i=0;i<=n-1;++i){
        integral_s+=integrand_expression(x1+i*h);
    }
    return integral_s*h;
}

double num_comput_integral_r_re(double x1,double x2,unsigned int n){
    double integral_s=0,h=(x2-x1)/n;
    for(int i=1;i<=n;++i){
        integral_s+=integrand_expression(x1+i*h);
    }
    return integral_s*h;
}


double num_comput_integral_trapeze(double x1,double x2,unsigned int n){
    double integral_s=0,x,h=(x2-x1)/n;
    x=x1;
    for(int i=0;i<=n-1;++i){
        integral_s+=(integrand_expression(x+i*h)+integrand_expression(x+(i+1)*h))/2;
    }
    return integral_s*h;
}

double num_comput_integral_Simps(double x1,double x2,unsigned int n){
    double x,h=(x2-x1)/n;
    double integral_s=0,s1=0,s2=0;
    x=x1;
    integral_s+=integrand_expression(x1);

    for(int i=1;i<=n-1;i+=2){
        s1+=integrand_expression(x+i*h);
    }

    s1*=4;
    x=x1+h;
    for(int i=2;i<=n-2;i+=2){
        s2+=integrand_expression(x+i*h);
    }
    s2*=2;
    integral_s+=s1+s2;
    integral_s+=integrand_expression(x2);

    return integral_s*h/3;
}

unsigned int calculate_integral
    (double (*f)(double,double,unsigned int),double x1,double x2,double err){
    unsigned int n=2;
    double I1=f(x1,x2,n),I2=f(x1,x2,n+2);
    int flag=1;
    while(flag){
        n+=2;
        I2=f(x1,x2,n);
        if(fabs(I1-I2)<err){
            flag=0;
        }
        else I1=I2;
    }
    return n;
}

int main(){
    double x1=0,x2=0,err=0;
    int n=0,var,i,integral_s;
    while(1){
        printf("\n\tEnter the left boundary \n X(first)=");
        scanf("%lf",&x1);
        printf("\n\tEnter the right boundary \n X(last)=");
        scanf("%lf",&x2);
        do{
            printf("\tEnter the number of partition intervals (N>0)\nN=");
            scanf("%u",&n);
        }while(n<=0);

        printf("\n\tEnter the measurment error of integration\n Measurment error=");
        scanf("%lf",&err);

        do{
            printf("\nChoose the method of calculating:\n");
            printf("\t1. By Left Rectangles :\n");
            printf("\t2. By Right Rectangles:\n");
            printf("\t3. By trapeze method:\n");
            printf("\t4. By integral_Simps's method (parabola method):\n");
            scanf("%u", &var);
            if (var!=1&&var!=2&&var!=3&&var!=4)
                printf("\nYou are mistaken\n");
        }while(var!=1&&var!=2&&var!=3&&var!=4);
        system("cls");
        switch(var){
            case 1:
                printf("\n\n\t*Left Rectangles method*\n");
                printf("\n\ta=%.2lf \n\tb=%.2lf \n\tIntegral=%.8lf \n\tN = %d",x1,x2,
                       num_comput_integral_l_re(x1,x2,n),calculate_integral(num_comput_integral_l_re,x1,x2,err));
                break;
            case 2:
                printf("\n\n\t======*Right Rectangles method*======\n");
                printf("\n\ta=%.2lf \n\tb=%.2lf \n\tIntegral=%.8lf \n\tN = %d",x1,x2,
                       num_comput_integral_r_re(x1,x2,n),calculate_integral(num_comput_integral_r_re,x1,x2,err));
                break;
            case 3:
                printf("\n\n\t======*Trapeze  method*======\n");
                printf("\n\ta=%.2lf \n\tb=%.2lf \n\tIntegral=%.8lf \n\tN = %d",x1,x2,
                       num_comput_integral_trapeze(x1,x2,n),calculate_integral(num_comput_integral_trapeze,x1,x2,err));
                break;
            case 4:
                printf("\n\n\t======*Simps's method *======\n");
                printf("\n\ta=%.2lf \n\tb=%.2lf \n\tIntegral=%.8lf \n\tN = %d",x1,x2,
                       num_comput_integral_Simps(x1,x2,n),calculate_integral(num_comput_integral_Simps,x1,x2,err));
                break;
        }
        getch();
        system("cls");
    }
}
