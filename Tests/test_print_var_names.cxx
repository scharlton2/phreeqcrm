#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "PhreeqcRM.h"

void print_var_names(PhreeqcRM &model);

#define GetComponentName   BMI_GetComponentName
#define GetInputVarNames   BMI_GetInputVarNames
#define GetInputItemCount  BMI_GetInputItemCount
#define GetOutputItemCount BMI_GetOutputItemCount

int
main(void)
{
  PhreeqcRM model(3, 4);

  // model.Initialize(""); @todo

  std::cout << model.GetComponentName() << std::endl;

  print_var_names(model);

  // model.Finalize(""); @todo

  return EXIT_SUCCESS;
}

void
print_var_names(PhreeqcRM &model)
{
  int number_of_names;
  std::vector<std::string> names;

  number_of_names = model.GetInputItemCount();
  std::cout << "Number of input names: " << number_of_names << std::endl;
  names = model.BMI_GetInputVarNames();
  assert(names.size() == number_of_names);
  for (auto name : names) {
    std::cout << name << std::endl;
  }
  std::cout << std::endl;

  number_of_names = model.GetOutputItemCount();
  std::cout << "Number of output names: " << number_of_names << std::endl;
  names = model.BMI_GetOutputVarNames();
  assert(names.size() == number_of_names);
  for (auto name : names) {
    std::cout << name << std::endl;
  }
  std::cout << std::endl;
}
