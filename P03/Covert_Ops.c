#include <stdio.h>
#define N 4

int f0();
int f1();
int f2(int i);
void f3(int i, int *p);
void f3_helper(int *p);
int Is_Number_Correct(int input, int answer, int i);

int main() {
    int i;
    int n[N];
    int a[N];
    int c = 0;

    // get numbers from user
    printf("Enter four numbers: ");
    for (i = 0; i<N; i++) scanf("%d", &n[i]);
    printf("\nYou have entered: %d, %d, %d, %d\n",n[0], n[1], n[2], n[3]);
    
    // get answers
    a[0] = f0(); 
    a[1] = f1();
    a[2] = f2(i);
    a[3] = 4046;  
    f3(a[3], &a[3]);

    // print answers
    // for (i = 0; i< N; i++) printf("answers #%d = %d\n",i,a[i]);

    // test 
    c += Is_Number_Correct(n[0], a[0], 0);
    c += Is_Number_Correct(n[1], a[1], 1);
    c += Is_Number_Correct(n[2], a[2], 2);
    c += Is_Number_Correct(n[3], a[3], 3);

    // report results
    if (c==0) printf("You didn't get any correct numbers. Please try again.\n");
    if (c > 0 && c < N) printf("You got %d correct numbers.  Please try again.\n", c);
    if (c==N) printf("All numbers are correct! Nice work!\n");

    return 0;
}

int Is_Number_Correct(int input, int answer, int i){
    if(input - answer == 0){
        printf("Number %d: Correct. Nice Job.\n", i);
        return 1;
    }
    else{
        printf("Number %d: Incorrect\n", i);
        return 0;
    }
}

void f3_helper(int *p){
    int a = 3;
    *p = *p + 3; 
}

void f3(int i, int *p){
    f3_helper(&i);
    f3_helper(&i);
    *p = (i<<3) + *p;
}

int f2(int i){
    int a = 0;
    int b = 0;
    do{
        b = b + i + a*a;
        a = a + 1;
    }while(a <= 27);
    return b;
}

int f1(){
    int a = 0x61c3;
    int b = 0xc882;
    int c = 0x107dc;
    int d = 0x76c4;
    int e = 0x31;
    int f = 0x11;
    
    if(a-b-c <= 0){
        if(d - a*b >= 0){
            d = d/f;
            return d;
        }
        else{
            c = c%e;
            return c;
        }   
    }
    else{
        a = a >> 4;
        return a;
    }
}

int f0(){
    return 5589516;
}
