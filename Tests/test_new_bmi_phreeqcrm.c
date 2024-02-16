#include <assert.h>
#include <stdlib.h> // NULL

#include <BMI_interface_C.h>

int
main(void)
{
  PhreeqcRMBmi *model = (PhreeqcRMBmi*)malloc(sizeof(PhreeqcRMBmi));
  register_bmi_phreeqcrm(model);
  return EXIT_SUCCESS;
}

