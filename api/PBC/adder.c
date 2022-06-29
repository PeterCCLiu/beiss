// #include <stdio.h>
__attribute__((export_name("adder")))
int add(int a, int b){
    return a + b;
}