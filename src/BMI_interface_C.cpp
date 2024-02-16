#ifdef USE_MPI
#include "mpi.h"
#endif
//#include "BMIVariant.h"
#include "BMIPhreeqcRM.h"
#include "BMI_interface_C.h"
#include "BMI_interface_F.h"
//#include "IPhreeqcPhastLib.h"
//#include "Phreeqc.h"
//#include "PHRQ_io.h"
// "BMIVariant.h"
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
//static void
//rmpadfstring(char* dest, const char* src, unsigned int len)
//{
//	size_t sofar;
//
//	for (sofar = 0; (sofar < len) && (*src != '\0'); ++sofar)
//		*dest++ = *src++;
//
//	while (sofar++ < len)
//		*dest++ = ' ';
//}
static IRM_RESULT
rmpadfstring(char* dest, const char* src, int len)
{
	size_t sofar;
	std::string str = src;
	if (len == 0) 
	{
		return IRM_INVALIDARG;
	}
	size_t l = (size_t)len - 1;
	if (str.size() < l)
	{
		memcpy(dest, (void*)str.c_str(), str.size());
		dest[str.size()] = '\0';
		return IRM_OK;
	}
	else
	{
		memcpy(dest, (void*)str.c_str(), l);
		dest[l] = '\0';
		return IRM_INVALIDARG;
	}
}
#ifdef SKIP
#ifdef USE_MPI
/* ---------------------------------------------------------------------- */
int
BMI_Create(int nxyz, int nthreads)
/* ---------------------------------------------------------------------- */
{
	//
	// Creates reaction module, called by root and MPI workers
	//
	int id = BMIPhreeqcRM::CreateBMIModule(nxyz, MPI_Comm_f2c(nthreads));
	// Returns ith output variable name
	if (id >= 0)
	{
		BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
		if (bmirm_ptr)
		{
			IRM_RESULT status = bmirm_ptr->SetLanguage("C");
		}
	}
	return id;
}
#else
/* ---------------------------------------------------------------------- */
int
BMI_Create_default()
/* ---------------------------------------------------------------------- */
{
	//
	// Creates reaction module, called by root and MPI workers
	//
	int id = BMIPhreeqcRM::CreateBMIModule();
	if (id >= 0)
	{
		BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
		if (bmirm_ptr)
		{
			IRM_RESULT status = bmirm_ptr->SetLanguage("C");
		}
	}
	return id;
}
/* ---------------------------------------------------------------------- */
int
BMI_Create(int nxyz, int nthreads)
/* ---------------------------------------------------------------------- */
{
	//
	// Creates reaction module, called by root and MPI workers
	//
	int id = BMIPhreeqcRM::CreateBMIModule(nxyz, nthreads);
	if (id >= 0)
	{
		BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
		if (bmirm_ptr)
		{
			IRM_RESULT status = bmirm_ptr->SetLanguage("C");
		}
	}
	return id;
}
#endif
IRM_RESULT
BMI_Destroy(int id)
/* ---------------------------------------------------------------------- */
{
	//
	// Creates reaction module, called by root and MPI workers
	//
	return BMIPhreeqcRM::DestroyBMIModule(id);
}
IRM_RESULT
BMI_Finalize(int id)
/* ---------------------------------------------------------------------- */
{
	return BMI_Destroy(id);
}
IRM_RESULT        
BMI_AddOutputVars(int id, char* option_in, char* def_in)
{
	return RMF_BMI_AddOutputVars(&id, option_in, def_in);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetComponentName(int id, char* chem_name, int l1)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string str = bmirm_ptr->GetComponentName();
		return rmpadfstring(chem_name, str.c_str(), l1);
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
double
BMI_GetCurrentTime(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetCurrentTime(&id);
}
/* ---------------------------------------------------------------------- */
double
BMI_GetEndTime(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetCurrentTime(&id);
}
/* ---------------------------------------------------------------------- */
int 
BMI_GetGridRank(int id, int n)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		return bmirm_ptr->GetGridRank(n);
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
int
BMI_GetGridSize(int id, int n)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		return bmirm_ptr->GetGridSize(n);
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetGridType(int id, int n, char* string, int l)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string str = bmirm_ptr->GetGridType(n);
		return rmpadfstring(string, str.c_str(), l);
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
int        
BMI_GetInputItemCount(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetInputItemCount(&id);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetInputVarName(int id, int i, char* name, int l)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::vector<std::string> names = bmirm_ptr->GetInputVarNames();
		return  rmpadfstring(name, names[i].c_str(), l);
	}
	return IRM_BADINSTANCE;
}
#ifdef SKIP
/* ---------------------------------------------------------------------- */
int
BMI_GetInputVarNamesSize(int id)
/* ---------------------------------------------------------------------- */
{
	IRM_RESULT status;
	int l;
	status = (IRM_RESULT)RMF_BMI_GetNamesSize(&id, "inputvarnames", &l);
	l = l + 1;
	if (status != IRM_OK) l = -1;
	return l;
}
#endif

/* ---------------------------------------------------------------------- */
int
BMI_GetOutputItemCount(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetOutputItemCount(&id);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetOutputVarName(int id, int i, char* name, int l)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::vector<std::string> names = bmirm_ptr->GetOutputVarNames();
		return  rmpadfstring(name, names[i].c_str(), l);
	}
	return IRM_BADINSTANCE;
}
#ifdef SKIP
/* ---------------------------------------------------------------------- */
int        
BMI_GetOutputVarNamesSize(int id)
/* ---------------------------------------------------------------------- */
{
	IRM_RESULT status;
	int l;
	status = (IRM_RESULT) RMF_BMI_GetNamesSize(&id, "outputvarnames", &l);
	l = l + 1;
	if (status != IRM_OK) l = -1;
	return l;
}
#endif

/* ---------------------------------------------------------------------- */
int
BMI_GetPointableItemCount(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetPointableItemCount(&id);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetPointableVarName(int id, int i, char* name, int l)
/* ---------------------------------------------------------------------- */
{
	// Returns ith output variable name
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::vector<std::string> names = bmirm_ptr->GetPointableVarNames();
		return  rmpadfstring(name, names[i].c_str(), l);
	}
	return IRM_BADINSTANCE;
}
#ifdef SKIP
/* ---------------------------------------------------------------------- */
int
BMI_GetPointableVarNamesSize(int id)
/* ---------------------------------------------------------------------- */
{
	IRM_RESULT status;
	int l;
	status = (IRM_RESULT)RMF_BMI_GetNamesSize(&id, "pointablevarnames", &l);
	l = l + 1;
	if (status != IRM_OK) l = -1;
	return l;
}
#endif
/* ---------------------------------------------------------------------- */
double
BMI_GetStartTime(int id)
/* ---------------------------------------------------------------------- */
{
	return BMI_GetCurrentTime(id);
}
/* ---------------------------------------------------------------------- */
double
BMI_GetTime(int id)
/* ---------------------------------------------------------------------- */
{
	return BMI_GetCurrentTime(id);
}
/* ---------------------------------------------------------------------- */
double
BMI_GetTimeStep(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetTimeStep(&id);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetTimeUnits(int id, char* units, int l1)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = bmirm_ptr->GetTimeUnits();
		return	rmpadfstring(units, name.c_str(), l1);
	}
	return IRM_BADINSTANCE;
}

/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetValueChar(int id, char* var, char* dest, int l)
/* ---------------------------------------------------------------------- */
{
	//BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	//if (bmirm_ptr)
	//{
	//	std::string name = var;
	//	std::string value;
	//	bmirm_ptr->GetValue(name, value);
	//	IRM_RESULT return_value = rmpadfstring(dest, value.c_str(), l);
	//	//bmirm_ptr->GetValue(name, dest);
	//	return return_value;
	//}
	int nbytes = RMF_BMI_GetVarNbytes(&id, var);
	if (nbytes + 1 > l)
	{
		return IRM_INVALIDARG;
	}
	IRM_RESULT status = RMF_BMI_GetValue(&id, var, dest);
	if (status >= 0)
	{
		dest[nbytes] = '\0';
	}
	return status;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetValueDouble(int id, char* var, double* dest)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->GetValue(name, dest);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetValueInt(int id, char* var, int* dest)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->GetValue(name, dest);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
void*
BMI_GetValuePtr(int id, char* var)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		return bmirm_ptr->GetValuePtr(name);
	}
	return NULL;
}

///* ---------------------------------------------------------------------- */
//IRM_RESULT
//BMI_GetValuePtrChar(int id, char* var, char** dest)
///* ---------------------------------------------------------------------- */
//{
//	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
//	if (bmirm_ptr)
//	{
//		std::string name = var;
//		*dest = (char*)bmirm_ptr->GetValuePtr(name);
//		return IRM_OK;
//	}
//	return IRM_BADINSTANCE;
//}
///* ---------------------------------------------------------------------- */
//double*
//BMI_GetValuePtrDouble(int id, char* var)
///* ---------------------------------------------------------------------- */
//{
//	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
//	if (bmirm_ptr)
//	{
//		std::string name = var;
//		return (double*)bmirm_ptr->GetValuePtr(name);
//	}
//	return NULL;
//}
///* ---------------------------------------------------------------------- */
//int*
//BMI_GetValuePtrInt(int id, char* var)
///* ---------------------------------------------------------------------- */
//{
//	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
//	if (bmirm_ptr)
//	{
//		std::string name = var;
//		return (int*)bmirm_ptr->GetValuePtr(name);
//	}
//	return NULL;
//}
/* ---------------------------------------------------------------------- */
int
BMI_GetVarGrid(int id, char* var)
/* ---------------------------------------------------------------------- */
{
	int g;
	return 1;
}
/* ---------------------------------------------------------------------- */
int
BMI_GetVarItemsize(int id, char* var)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetVarItemsize(&id, var);
}
/* ---------------------------------------------------------------------- */
int
BMI_GetVarNbytes(int id, char* var)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_GetVarNbytes(&id, var);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetVarType(int id, char* var, char* vtype, int l1)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = bmirm_ptr->GetVarType(var);
		return	rmpadfstring(vtype, name.c_str(), l1);
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_GetVarUnits(int id, char* var, char* units, int l1)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = bmirm_ptr->GetVarUnits(var);
		return	rmpadfstring(units, name.c_str(), l1);
	}
	return IRM_BADINSTANCE;
}
#ifdef USE_YAML
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_Initialize(int id, char* config_file)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_Initialize(&id, config_file);
}
#endif


/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_SetValueChar(int id, char* var, const char* src)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->SetValue(name, src);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_SetValueDouble(int id, char* var, double src)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->SetValue(name, src);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_SetValueDoubleArray(int id, char* var, double* src)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->SetValue(name, src);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_SetValueInt(int id, char* var, int src)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->SetValue(name, src);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
#ifdef SKIP
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_SetValueIntArray(int id, char* var, int* src)
/* ---------------------------------------------------------------------- */
{
	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
	if (bmirm_ptr)
	{
		std::string name = var;
		bmirm_ptr->SetValue(name, src);
		return IRM_OK;
	}
	return IRM_BADINSTANCE;
}
#endif
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_Update(int id)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_Update(&id);
}
/* ---------------------------------------------------------------------- */
IRM_RESULT
BMI_UpdateUntil(int id, double time)
/* ---------------------------------------------------------------------- */
{
	return RMF_BMI_UpdateUntil(&id, &time);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetValueAtIndices(int id, char* name, void* dest, int* inds, int count)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_SetValueAtIndices(int id, char* name, int* inds, int count, void* src)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridShape(int id, const int grid, int* shape)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridSpacing(int id, const int grid, double* spacing)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridOrigin(int id, const int grid, double* origin)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridX(int id, const int grid, double* x)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridY(int id, const int grid, double* y)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridZ(int id, const int grid, double* z)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
int 
GetGridNodeCount(int id, const int grid)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
int 
GetGridEdgeCount(int id, const int grid)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
int 
GetGridFaceCount(int id, const int grid)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridEdgeNodes(int id, const int grid, int* edge_nodes)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridFaceEdges(int id, const int grid, int* face_edges)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridFaceNodes(int id, const int grid, int* face_nodes)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
/* ---------------------------------------------------------------------- */
void 
BMI_GetGridNodesPerFace(int id, const int grid, int* nodes_per_face)
/* ---------------------------------------------------------------------- */
{
	fprintf(stderr, "Not implemented\n"); exit(4);
}
#endif

#define NEW_BMI_C_INTERFACE
#if defined(NEW_BMI_C_INTERFACE)

// /* ---------------------------------------------------------------------- */
// IRM_RESULT
// BMI_GetComponentName(int id, char* chem_name, int l1)
// /* ---------------------------------------------------------------------- */
// {
// 	// Returns ith output variable name
// 	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(id);
// 	if (bmirm_ptr)
// 	{
// 		std::string str = bmirm_ptr->GetComponentName();
// 		return rmpadfstring(chem_name, str.c_str(), l1);
// 	}
// 	return IRM_BADINSTANCE;
// }


// /* ---------------------------------------------------------------------- */
// IRM_RESULT
// RMF_BMI_Initialize(int* id, char* config_file)
// /* ---------------------------------------------------------------------- */
// {
// 	// Returns units of variable var
// 	BMIPhreeqcRM* bmirm_ptr = BMIPhreeqcRM::GetInstance(*id);
// 	if (bmirm_ptr)
// 	{
// 		bmirm_ptr->Initialize(config_file);
// 		return IRM_OK;
// 	}
// 	return IRM_BADINSTANCE;
// }

static int
Get_start_time(Bmi *self, double *time)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			*time = bmirm_ptr->GetStartTime();
			return IRM_OK;
		}
		return IRM_BADINSTANCE;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_end_time(Bmi *self, double *time)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);	
		if (bmirm_ptr)
		{
			*time = bmirm_ptr->GetEndTime();
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_time_step(Bmi *self, double *dt)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);	
		if (bmirm_ptr)
		{
			*dt = bmirm_ptr->GetTimeStep();
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_time_units(Bmi *self, char *units)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			std::string str = bmirm_ptr->GetComponentName();
			//strncpy(units, str.c_str(), BMI_MAX_UNITS_NAME);
			return rmpadfstring(units, str.c_str(), BMI_MAX_UNITS_NAME);
		}
		return IRM_BADINSTANCE;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_current_time(Bmi *self, double *time)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			*time = bmirm_ptr->GetCurrentTime();
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Initialize(Bmi *self, const char *file)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			bmirm_ptr->Initialize(file ? file : std::string());
			return IRM_OK;
		}
		return IRM_BADINSTANCE;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Update(Bmi *self)
{
	try
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);	
		if (bmirm_ptr)
		{
			bmirm_ptr->Update();
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Update_until(Bmi *self)
{
	// TODO
	assert(false);
}

static int
Finalize(Bmi *self)
{
	try 
	{
		if (self)
		{
			delete ((BMIPhreeqcRM*)(self->data));
			self->data = (void*)new_bmi_phreeqcrm();
		}
		return BMI_SUCCESS;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_grid_rank(Bmi *self, int grid, int *rank)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);	
		if (bmirm_ptr)
		{
			*rank = bmirm_ptr->GetGridRank(grid);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_grid_size(Bmi *self, int grid, int *size)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);	
		if (bmirm_ptr)
		{
			*size = bmirm_ptr->GetGridSize(grid);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_grid_spacing(Bmi *self, int grid, double *spacing)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			bmirm_ptr->GetGridSpacing(grid, spacing);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_grid_origin(Bmi *self, int grid, double *origin)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			bmirm_ptr->GetGridOrigin(grid, origin);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_grid_type(Bmi *self, int grid, char *type)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			std::string str = bmirm_ptr->GetGridType(grid);
			//strncpy(type, str.c_str(), BMI_MAX_TYPE_NAME);
			return rmpadfstring(type, str.c_str(), BMI_MAX_TYPE_NAME);
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_var_grid(Bmi *self, const char *name, int *grid)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			*grid = bmirm_ptr->GetVarGrid(name);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_var_type(Bmi *self, const char *name, char *type)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			std::string str = bmirm_ptr->GetVarType(name);
			//strncpy(type, str.c_str(), BMI_MAX_TYPE_NAME);
			return rmpadfstring(type, str.c_str(), BMI_MAX_TYPE_NAME);
		}
		return IRM_BADINSTANCE;	
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_var_itemsize(Bmi *self, const char *name, int *size)
{
	try 
	{
		BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
		if (bmirm_ptr)
		{
			*size = bmirm_ptr->GetVarItemsize(name);
			return BMI_SUCCESS;
		}
		return IRM_BADINSTANCE;
	}
	catch(...)
	{
		return BMI_FAILURE;
	}
}

static int
Get_var_units(Bmi *self, const char *name, char *units)
{
	BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
	if (bmirm_ptr)
	{
		std::string str = bmirm_ptr->GetVarUnits(name);
		//strncpy(units, str.c_str(), BMI_MAX_UNITS_NAME);
		return rmpadfstring(units, str.c_str(), BMI_MAX_UNITS_NAME);
	}
	return IRM_BADINSTANCE;
}

static int
Get_var_nbytes(Bmi *self, const char *name, int *nbytes)
{
	BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
	if (bmirm_ptr)
	{
		*nbytes = bmirm_ptr->GetVarNbytes(name);
		return BMI_SUCCESS;
	}
	return IRM_BADINSTANCE;
}

static int
Get_var_location(Bmi *self, const char *name, char *location)
{
	BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
	if (bmirm_ptr)
	{
		std::string str = bmirm_ptr->GetVarLocation(name);
		//strncpy(location, str.c_str(), BMI_MAX_UNITS_NAME);
		return rmpadfstring(location, str.c_str(), BMI_MAX_UNITS_NAME);
	}
	return IRM_BADINSTANCE;
}

static int
Get_value_ptr(Bmi *self, const char *name, void **dest)
{
	BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
	if (bmirm_ptr)
	{
		*dest = bmirm_ptr->GetValuePtr(name);
		return BMI_SUCCESS;
	}
	return IRM_BADINSTANCE;
}

void *
new_bmi_phreeqcrm(void)
{
  BMIPhreeqcRM* data = new BMIPhreeqcRM;
  return data;
}

static int
Get_component_name(Bmi *self, char *name)
{
	BMIPhreeqcRM* bmirm_ptr = static_cast<BMIPhreeqcRM*>(self->data);
	if (bmirm_ptr)
	{
		std::string str = bmirm_ptr->GetComponentName();
		//strncpy(name, str.c_str(), BMI_MAX_COMPONENT_NAME);
		return rmpadfstring(name, str.c_str(), BMI_MAX_COMPONENT_NAME);
	}
	return IRM_BADINSTANCE;
}

PhreeqcRMBmi*
register_bmi_phreeqcrm(PhreeqcRMBmi *model)
{
  Bmi* bmi_model = (Bmi*) model;
  if (bmi_model) {

	bmi_model->data = new_bmi_phreeqcrm();

    bmi_model->initialize = Initialize;
    bmi_model->update = Update;
    bmi_model->update_until = nullptr;
    bmi_model->finalize = nullptr;

    bmi_model->get_component_name = Get_component_name;
    bmi_model->get_input_item_count = nullptr;
    bmi_model->get_output_item_count = nullptr;
    bmi_model->get_input_var_names = nullptr;
    bmi_model->get_output_var_names = nullptr;

    bmi_model->get_var_grid = nullptr;
    bmi_model->get_var_type = nullptr;
    bmi_model->get_var_itemsize = nullptr;
    bmi_model->get_var_units = nullptr;
    bmi_model->get_var_nbytes = nullptr;
    bmi_model->get_var_location = nullptr;

    bmi_model->get_current_time = nullptr;
    bmi_model->get_start_time = Get_start_time;
    bmi_model->get_end_time = Get_end_time;
    bmi_model->get_time_units = Get_time_units;
    bmi_model->get_time_step = Get_time_step;

    bmi_model->get_value = nullptr;
    bmi_model->get_value_ptr = nullptr;
    bmi_model->get_value_at_indices = nullptr;

    bmi_model->set_value = nullptr;
    bmi_model->set_value_at_indices = nullptr;

    bmi_model->get_grid_size = Get_grid_size;
    bmi_model->get_grid_rank = Get_grid_rank;
    bmi_model->get_grid_type = Get_grid_type;

    bmi_model->get_grid_shape = nullptr;
    bmi_model->get_grid_spacing = Get_grid_spacing;
    bmi_model->get_grid_origin = Get_grid_origin;

    bmi_model->get_grid_x = nullptr;
    bmi_model->get_grid_y = nullptr;
    bmi_model->get_grid_z = nullptr;

    bmi_model->get_grid_node_count = nullptr;
    bmi_model->get_grid_edge_count = nullptr;
    bmi_model->get_grid_face_count = nullptr;
    bmi_model->get_grid_edge_nodes = nullptr;
    bmi_model->get_grid_face_edges = nullptr;
    bmi_model->get_grid_face_nodes = nullptr;
    bmi_model->get_grid_nodes_per_face = nullptr;
  }

  return model;
}


#endif // defined(NEW_BMI_C_INTERFACE)