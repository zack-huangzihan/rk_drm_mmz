#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <vector>
#include <mutex>

// #include <libdrm/drm.h>
// #include <libdrm/drm_fourcc.h>

#include <drm/drm.h>
#include <drm/drm_fourcc.h>

#include "linux5.10/rockchip_drm.h"
#include "rk_drm.h"

static int drm_fd = -1;

static int drm_open()
{
    if (drm_fd < 0) {
        drm_fd = open("/dev/dri/card0", O_RDONLY | O_CLOEXEC);
        if (drm_fd < 0) {
            printf("open /dev/dri/card0 failed: %s \n", strerror(errno));
        }
    }

    return drm_fd;
}

static void drm_close()
{
    if (drm_fd >= 0) {
        close(drm_fd);
        drm_fd = -1;
    }
}

static int drm_ioctl(uint32_t req, void* arg) {
    if (drm_open() < 0) {
        return -1;
    }
    uint32_t ret = ioctl(drm_fd, req, arg);
    if (ret < 0) {
        printf("fail to drm_ioctl(fd = %d, req =%d), error: %s \n", drm_fd, req, strerror(errno));
        return -1;
    }
    return ret;
}

int drm_alloc(uint32_t len, bool is_cma, bool is_cacheable, uint32_t *handle) {
	//struct rockchip_bo *bo;
    struct drm_mode_create_dumb dmcb;
    dmcb.bpp = 8;
    dmcb.width = (len + 4096 - 1) & (~(4096 - 1));
    dmcb.height = 1;
    dmcb.flags = 0;

    if (is_cma) {
        //printf("is_cma \n");
        dmcb.flags = ROCKCHIP_BO_CONTIG;
    } 

    if (is_cacheable) {
        //printf("is_cacheable \n");
    	dmcb.flags = dmcb.flags | ROCKCHIP_BO_CACHABLE;
    }

    if (dmcb.flags == (uint32_t)0) {
        printf("Can not find heap %s\n", is_cma?"CMA":"SYSTEM");
        return -1;
    }
    
    if(drm_ioctl(DRM_IOCTL_MODE_CREATE_DUMB, &dmcb)) {
    	printf("failed to create dumb object[%s].\n", strerror(errno));
    	return -1;	
    }

	*handle = dmcb.handle;
    
    return 0;
}

int drm_free(uint32_t handle) {
	struct drm_mode_destroy_dumb data = {
			.handle = handle,
			};
	return drm_ioctl(DRM_IOCTL_MODE_DESTROY_DUMB, &data);
}

int drm_handle_to_fd(uint32_t handle, int *map_fd) {
    uint32_t ret;
    struct drm_prime_handle dph;
    memset(&dph, 0, sizeof(struct drm_prime_handle));
    dph.handle = handle;
    dph.fd = -1;
    dph.flags = O_CLOEXEC | O_RDWR;

    if (map_fd == NULL)
        return -1;

    ret = drm_ioctl(DRM_IOCTL_PRIME_HANDLE_TO_FD, &dph);
    if (ret < 0) {
        return ret;
    }
    *map_fd = dph.fd;
    if (*map_fd < 0) {
        printf("fail to handle_to_fd(fd=%d) \n", map_fd);
        return -1;
    }

    return ret;
}

int drm_get_phys(uint32_t handle, uint32_t *phy) {

    struct drm_rockchip_gem_phys phys_arg;
    phys_arg.handle = handle;
    int ret = drm_ioctl(DRM_IOCTL_ROCKCHIP_GEM_GET_PHYS, &phys_arg);
    if (ret < 0) {
        printf("fail to get phys(handle=%d), error: %s \n", handle, strerror(errno));
        return ret;
    } else {
        *phy = phys_arg.phy_addr;
    }
    return ret;
}
