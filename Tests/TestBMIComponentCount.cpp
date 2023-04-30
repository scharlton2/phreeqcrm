#include <cstdlib>
#include "BMIPhreeqcRM.h"

int main(void)
{
    BMIPhreeqcRM* bmi = new BMIPhreeqcRM;

    bmi->Initialize("AdvectBMI_cpp.yaml");

    void* ptr = bmi->GetValuePtr("ComponentCount");
    int n = *((int*)ptr);
    assert(n == 8);

    delete bmi;
    return EXIT_SUCCESS;
}
