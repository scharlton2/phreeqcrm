#include <cstdlib>
#include "BMIPhreeqcRM.h"

int main(void)
{
    BMIPhreeqcRM* bmi = new BMIPhreeqcRM;

    bmi->Initialize("AdvectBMI_cpp.yaml");

    int nxyz = bmi->GetGridSize(0);
    assert(nxyz == 40);

    std::vector<double> por(40, 0.2);
    //bmi->SetPorosity(por);
    bmi->SetValue("Porosity", por);

    delete bmi;
    return EXIT_SUCCESS;
}
