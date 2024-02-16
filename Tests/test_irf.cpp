#include <math.h> // fabs

#include <gtest/gtest.h>

#include <BMI_interface_C.h>


TEST(test_irf, test_get_component_name)
{
	PhreeqcRMBmi *phreeqcrmbmi = (PhreeqcRMBmi*) malloc(sizeof(PhreeqcRMBmi));
	Bmi* model = (Bmi*) register_bmi_phreeqcrm(phreeqcrmbmi);

    char name[BMI_MAX_COMPONENT_NAME];
    int status = model->get_component_name(model, name);
	ASSERT_EQ(status, BMI_SUCCESS);

	ASSERT_STREQ(name, "BMI PhreeqcRM");

	free(phreeqcrmbmi);
}

TEST(test_irf, test_get_start_time)
{
	PhreeqcRMBmi *phreeqcrmbmi = (PhreeqcRMBmi*) malloc(sizeof(PhreeqcRMBmi));
	Bmi* model = (Bmi*) register_bmi_phreeqcrm(phreeqcrmbmi);

	int status = model->initialize(model, NULL);
	ASSERT_EQ(status, BMI_SUCCESS);

	double time;
	status = model->get_start_time(model, &time);

	ASSERT_DOUBLE_EQ(time, 0.0);
	
	free(phreeqcrmbmi);
}

TEST(test_irf, test_initialize)
{
	PhreeqcRMBmi *phreeqcrmbmi = (PhreeqcRMBmi*) malloc(sizeof(PhreeqcRMBmi));
	Bmi* model = (Bmi*) register_bmi_phreeqcrm(phreeqcrmbmi);

	int status = model->initialize(model, NULL);
	ASSERT_EQ(status, BMI_SUCCESS);
	
	free(phreeqcrmbmi);
}

TEST(test_irf, test_get_end_time)
{
	PhreeqcRMBmi *phreeqcrmbmi = (PhreeqcRMBmi*) malloc(sizeof(PhreeqcRMBmi));
	Bmi* model = (Bmi*) register_bmi_phreeqcrm(phreeqcrmbmi);

	int status = model->initialize(model, NULL);
	ASSERT_EQ(status, BMI_SUCCESS);

	double time;
	status = model->get_end_time(model, &time);
	ASSERT_EQ(status, BMI_SUCCESS);
	
	free(phreeqcrmbmi);
}


TEST(test_irf, test_irf)
{
	int status = BMI_SUCCESS;
	PhreeqcRMBmi *phreeqcrmbmi = (PhreeqcRMBmi*) malloc(sizeof(PhreeqcRMBmi));
	Bmi* model = (Bmi*) register_bmi_phreeqcrm(phreeqcrmbmi);

	{
		fprintf(stdout, "Initializing... ");
		fflush(stdout);

		status = model->initialize(model, NULL);
		ASSERT_EQ(status, BMI_SUCCESS);

		fprintf (stdout, "PASS\n");
	}

	{
		int i;
		const int n_steps = 10;
		double time;
		double dt;

		int status = model->get_time_step(model, &dt);
		ASSERT_EQ(status, BMI_SUCCESS);

		for (i = 0; i < n_steps; i++)
		{
			fprintf(stdout, "Running until t = %d... ", i + 1);

			// status = model->update(model);
			// ASSERT_EQ(status, BMI_SUCCESS);

			// status = model->get_current_time(model, &time);
			// ASSERT_EQ(status, BMI_SUCCESS);

			// ASSERT_LT(fabs(time / dt - (i + 1)), 1e-6);
		}

	// 	// fprintf(stdout, "Running until t = %f... ", 1000.5);

	// 	// status = model->update_until(model, 1000.5);
	// 	// if (status == BMI_FAILURE)
	// 	// 	return BMI_FAILURE;

	// 	// status = model->get_current_time(model, &time);
	// 	// if (status == BMI_FAILURE)
	// 	// 	return BMI_FAILURE;

	// 	// if (fabs(time - 1000.5) < 1e-6)
	// 	// 	fprintf(stdout, "PASS\n");
	// 	// else
	// 	// {
	// 	// 	fprintf(stdout, "%f\n", time);
	// 	// 	return BMI_FAILURE;
	// 	// }
	}

	free(phreeqcrmbmi);
}
