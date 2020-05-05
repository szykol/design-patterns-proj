#include "Random.h"
#include <iostream>

int main()
{
    auto randomInt = Random::Instance().get<int>(1, 10);

    std::cout << "Your random int is: " << randomInt << std::endl;
}