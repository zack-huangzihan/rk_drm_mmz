#include <stdint.h>
#include <stdio.h>
#include "rk_mpi_mmz.h"

int main() {
	printf("mmz test start\n");
	MB_BLK buffer;
	RK_S32 phy = 0;
	RK_VOID *vaddr = NULL;
	RK_S32 fd = 0; 
	RK_S32 flags = RK_MMZ_ALLOC_CACHEABLE | RK_MMZ_ALLOC_TYPE_CMA;
	int ret = 0;
	while(1) {
		ret = RK_MPI_MMZ_Alloc(&buffer, 4096, flags);
		if (ret < 0) {
			printf("RK_MPI_MMZ_Alloc  fail\n");
			return ret;
		}
		int size = RK_MPI_MMZ_GetSize(buffer);
		if(size == 0) {
			printf("RK_MPI_MMZ_GetSize fail\n");
			return -1;
		}
		phy = RK_MPI_MMZ_Handle2PhysAddr(buffer);
		if(phy == 0) {
			printf("RK_MPI_MMZ_Handle2PhysAddr fail\n");
			return -1;
		} 

		vaddr = RK_MPI_MMZ_Handle2VirAddr(buffer);
		if(vaddr == NULL) {
			printf("RK_MPI_MMZ_Handle2VirAddr fail\n");
			return -1;
		}

		fd = RK_MPI_MMZ_Handle2Fd(buffer);
		if(fd == -1) {
			printf("RK_MPI_MMZ_Handle2Fd fail\n");
			return -1;
		}
		buffer = RK_MPI_MMZ_Fd2Handle(fd);
		if(buffer == NULL) {
			printf("RK_MPI_MMZ_Fd2Handle fail\n");
			return -1;
		}
    
		ret = RK_MPI_MMZ_Free(buffer);
		if(ret == -1) {
			printf("RK_MPI_MMZ_Free fail\n");
			return -1;
		}
		printf("mmz test success\n");
	}

    return ret;
}
