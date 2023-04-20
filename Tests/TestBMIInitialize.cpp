#include <cstdlib>
#include "BMIPhreeqcRM.h"

int main(void)
{
    BMIPhreeqcRM* bmi = new BMIPhreeqcRM;

    bmi->Initialize("");

    int n0 = bmi->GetGridCellCount();
    assert(n0 == 10);

    int n1 = bmi->GetGridSize(0);
    assert(n1 == 10);

    int n3;
    bmi->GetValue("GridCellCount", n3);
    assert(n3 == 10);

    //int tc0 = bmi->GetThreadCount()
    //assert(tc0 == 10);

    //int tc1;
    //bmi->GetValue("ThreadCount", tc1);
    //assert(tc1 == 10);

    delete bmi;
    return EXIT_SUCCESS;
}
