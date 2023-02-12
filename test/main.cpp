#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <valarray>

using namespace std;
int main(){
double pi = 0;
for (int i = 0; i < 100000000; i++) {
pi += pow(-1, i) / (2 * i + 1);
}
pi *= 4;
printf("%f", pi);
}
