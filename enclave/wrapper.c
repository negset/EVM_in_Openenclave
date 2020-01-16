//
// Created by liang on 1/13/20.
//
#include <stdio.h>
#include "Greeting.h"
#include "SumTest.h"
int wrapHelloWorld(){
    fprintf(stdout, "Hello world from wrapHelloWorld1\n");
    sayHello();

    fprintf(stdout, "Test SUMTest\n");
    test_sum();
}