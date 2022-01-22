#ifndef __RK_DRM_H__
#define __RK_DRM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
    申请drm内存
    is_cma 是否申请CMA heap内存，若为false则申请SYSTEM heap内存
    is_cacheable 申请的内存是否支持cache
    fd 存放返回的ion内存的dmabuf fd
    成功 返回0
    失败 返回负值
 */
int drm_alloc(uint32_t len, bool is_cma, bool is_cacheable, uint32_t *handle);

int drm_free(uint32_t handle);
/*
    从handle转化为buf fd
 */
int drm_handle_to_fd(uint32_t handle, int *map_fd);

/*
    获取drm内存的物理地址
    fd dmabuf's fd
    paddr 存放返回的物理地址，如果非物理连续的内存，则地址被设置为-1
    成功 返回0
    失败 返回负值
 */
int drm_get_phys(uint32_t handle, uint32_t *phy);

#ifdef __cplusplus
}
#endif

#endif
