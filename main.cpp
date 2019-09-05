// Fluid System
#include "fluid_system.h"

int main ( int argc, const char** argv ) 
{
	cuInit(0);			// Initialize
	int deviceCount = 0;
	cuDeviceGetCount(&deviceCount);
	if (deviceCount == 0) {printf("There is no device supporting CUDA.\n"); exit (0);}

	CUdevice cuDevice;
	cuDeviceGet(&cuDevice, 0);
	CUcontext cuContext;
	cuCtxCreate(&cuContext, 0, cuDevice);

    	FluidSystem fluid;
    	fluid.SetDebug ( false );
    	int m_numpnts = 150000;   	// number of particles
    
    	fluid.Initialize ();
    	fluid.Start ( m_numpnts );	// transfers data to gpu
    	for(int i=0;i<20;i++){    	
		fluid.Run ();  		// run the simulation
    	}

	fluid.TransferFromCUDA ()	// retrieve outcome
	// NB fluid.m_Fluid.bufC(FPOS) returns a char* for fluid.m_Fluid.mcpu[n]

	//fluid.SaveResults ();
	//int NumPoints (){ return mNumPoints; }
	//Vector3DF* getPos(int n){ return &m_Fluid.bufV3(FPOS)[n]; }
	//Vector3DF* getVel(int n){ return &m_Fluid.bufV3(FVEL)[n]; }
	//uint* getClr (int n){ return &m_Fluid.bufI(FCLR)[n]; }

	//write fluid.m_Fluid.mcpu[n] to file. where n=bufferID : FPOS=0, FVEL=1
	
	// mcpu[MAX_BUF] where MAX_BUF = 25, is an array of buffers.
	// FluidSystem::AllocateParticles ( int cnt=numParticles )
	// calls FluidSystam::AllocateBuffer(...) for each each buffer
	// which calls m_Fluid.setBuf(buf_id, dest_buf);
	// to save the pointer to the allocated buffer to fluid.m_Fluid.mcpu[n]
	// FPOS, has a stride : sizeof(Vector3DF) , and 'numParticles' elements

	// create file
	
	// write HDF5 data to store fluid.m_Fluid.mcpu[FPOS][numParticles][Vector3DF]
	// use h5ex_t_array.c example

	
	
	
	
    	fluid.Exit ();			// Clean up and close
	CUresult cuResult = cuCtxDestroy ( cuContext ) ;
	if (cuResult!=0){printf("error closing, cuResult = %i \n",cuResult);}
	printf("\nClosing fluids_v4.\n");
    	return 0;
}

// note: Any memory allocated with cuMemAllocManaged should be released with cuMemFree. 	