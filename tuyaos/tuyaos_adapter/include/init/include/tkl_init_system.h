/**
* @file tkl_init_system.h
* @brief Common process - tkl init system object descption
* @version 0.1
* @date 2021-08-06
*
* @copyright Copyright 2021-2030 Tuya Inc. All Rights Reserved.
*
*/
#ifndef __TKL_INIT_SYSTEM_H__
#define __TKL_INIT_SYSTEM_H__

#include "tuya_cloud_types.h"
#include "tkl_system.h"
#include "tkl_memory.h"
#include "tkl_thread.h"
#include "tkl_mutex.h"
#include "tkl_semaphore.h"
#include "tkl_output.h"
#include "tkl_queue.h"
#include "tkl_ota.h"
#include "tkl_sleep.h"

#ifdef ENABLE_FILE_SYSTEM
#include "tkl_fs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief the description of tuya kernel adapter layer system api
 *
 */


typedef struct {
    //! system (cpu)
    VOID_T              (*reset)                    (VOID_T);
    int               (*get_free_heap_size)       (VOID_T);
    SYS_TICK_T          (*get_tick_count)           (VOID_T);
    SYS_TIME_T          (*get_millisecond)          (VOID_T);
    int               (*get_random)               (uint32_t range);
    TUYA_RESET_REASON_E (*get_reset_reason)        (CHAR_T** describe);
    void                (*sleep)                    (const uint32_t num_ms);
    OPERATE_RET         (*cpu_sleep_mode_set)       (BOOL_T enable, TUYA_CPU_SLEEP_MODE_E mode);
    OPERATE_RET         (*get_cpu_info)             (TUYA_CPU_INFO_T **cpu_ary, int *cpu_cnt);
    //! output     
    VOID_T              (*log_output)               (const CHAR_T *log, ...);
    OPERATE_RET         (*log_close)                (VOID_T);
    OPERATE_RET         (*log_open)                 (VOID_T);
    //! ota
    OPERATE_RET         (*ota_get_ability)          (uint32_t *image_size, TUYA_OTA_TYPE_E *type);
    OPERATE_RET         (*ota_start)                (uint32_t image_size, TUYA_OTA_TYPE_E type, TUYA_OTA_PATH_E path);
    OPERATE_RET         (*ota_process)              (TUYA_OTA_DATA_T *pack, uint32_t* remain_len);
    OPERATE_RET         (*ota_end)                  (BOOL_T reset);
    //! memory
    VOID_T*             (*malloc)                   (const size_t size);
    VOID_T              (*free)                     (VOID_T* ptr);
    VOID_T*             (*calloc)                   (size_t nitems, size_t size);
    VOID_T*             (*realloc)                  (VOID_T* ptr, size_t size);
    //! thread
    OPERATE_RET         (*thread_create)            (TKL_THREAD_HANDLE* thread, const CHAR_T* name, const uint32_t stack_size, const uint32_t priority, const THREAD_FUNC_T func, VOID_T* const arg);
    OPERATE_RET         (*thread_release)           (const TKL_THREAD_HANDLE thread);
    OPERATE_RET         (*thread_set_name)          (const CHAR_T* name);
    OPERATE_RET         (*thread_set_priority)      (TKL_THREAD_HANDLE thread, int  priority);
    OPERATE_RET         (*thread_get_priority)      (TKL_THREAD_HANDLE thread, int *priority);
    OPERATE_RET         (*thread_get_watermark)     (const TKL_THREAD_HANDLE thread, uint32_t* watermark);    
    OPERATE_RET         (*thread_get_id)            (TKL_THREAD_HANDLE* thread);
    OPERATE_RET         (*thread_is_self)           (TKL_THREAD_HANDLE thread, BOOL_T* is_self);
    OPERATE_RET         (*thread_diagnose)          (TKL_THREAD_HANDLE thread);
    int               (*getheapsize)              (VOID_T);
    //! mutex
    OPERATE_RET         (*mutex_init)               (TKL_MUTEX_HANDLE *handle);
    OPERATE_RET         (*mutex_lock)               (const TKL_MUTEX_HANDLE handle);
    OPERATE_RET         (*mutex_trylock)            (const TKL_MUTEX_HANDLE handle);
    OPERATE_RET         (*mutex_unlock)             (const TKL_MUTEX_HANDLE handle);
    OPERATE_RET         (*mutex_release)            (const TKL_MUTEX_HANDLE handle);
    //! semaphore
    OPERATE_RET         (*sem_init)                 (TKL_SEM_HANDLE *handle, const uint32_t sem_cnt, const uint32_t sem_max);
    OPERATE_RET         (*sem_wait)                 (const TKL_SEM_HANDLE handle, const uint32_t timeout);
    OPERATE_RET         (*sem_post)                 (const TKL_SEM_HANDLE handle);
    OPERATE_RET         (*sem_release)              (const TKL_SEM_HANDLE handle);
    OPERATE_RET         (*sem_wait_timeout)         (const TKL_SEM_HANDLE handle, const uint32_t timeout);
    //! queue
    OPERATE_RET         (*queue_init)               (TKL_QUEUE_HANDLE *queue, const int msgsize, const int msgcount);
    VOID_T              (*queue_free)               (const TKL_QUEUE_HANDLE queue);
    OPERATE_RET         (*queue_post)               (const TKL_QUEUE_HANDLE queue, VOID_T *data, const uint32_t timeout);
    OPERATE_RET         (*queue_fetch)              (const TKL_QUEUE_HANDLE queue, VOID_T *msg, const uint32_t timeout);
} TKL_OS_T;

extern const TKL_OS_T TKL_OS;

/**
 * @brief get system os description
 *
 * @return TKL_OS instance
 */
TKL_OS_T* tkl_os_desc_get(VOID_T);

//#ifdef ENABLE_FILE_SYSTEM
/**
 *
 * @brief the description of tuya kernel adapter layer file system
 *
 */
typedef struct {
    OPERATE_RET         (*fs_mkdir)                 (const CHAR_T* path);
    OPERATE_RET         (*fs_remove)                (const CHAR_T* path);
    OPERATE_RET         (*fs_mode)                  (const CHAR_T* path, uint32_t* mode);
    OPERATE_RET         (*fs_is_exist)              (const CHAR_T* path, BOOL_T* is_exist);
    OPERATE_RET         (*fs_rename)                (const CHAR_T* path_old, const CHAR_T* path_new);
    OPERATE_RET         (*dir_open)                 (const CHAR_T* path, TUYA_DIR* dir);
    OPERATE_RET         (*dir_close)                (TUYA_DIR dir);
    OPERATE_RET         (*dir_read)                 (TUYA_DIR dir, TUYA_FILEINFO* info);
    OPERATE_RET         (*dir_name)                 (TUYA_FILEINFO info, const CHAR_T** name);
    OPERATE_RET         (*dir_is_dir)               (TUYA_FILEINFO info, BOOL_T* is_dir);
    OPERATE_RET         (*dir_is_regular)           (TUYA_FILEINFO info, BOOL_T* is_regular);
    TUYA_FILE            (*fopen)                    (const CHAR_T* path, const CHAR_T* mode);
    OPERATE_RET         (*fclose)                   (TUYA_FILE file);
    OPERATE_RET         (*fread)                    (VOID_T* buf, int bytes, TUYA_FILE file);
    OPERATE_RET         (*fwrite)                   (VOID_T* buf, int bytes, TUYA_FILE file);
    CHAR_T*             (*fgets)                    (CHAR_T* buf, int len, TUYA_FILE file);
    OPERATE_RET         (*feof)                     (TUYA_FILE file);
    OPERATE_RET         (*fseek)                    (TUYA_FILE file, INT64_T offs, int whence);
    INT64_T             (*ftell)                    (TUYA_FILE file);
    int               (*fflush)                   (TUYA_FILE file);
    int               (*fileno)                   (TUYA_FILE file);
    int               (*fsync)                    (int fd);
    int               (*faccess)                  (const CHAR_T *filepath,IN int mode);
    int               (*fgetsize)                 (const CHAR_T *filepath);
    int               (*fgetc)                    (TUYA_FILE file);
    int               (*ftruncate)                (int fd, UINT64_T length);
} TKL_FS_T;

extern const TKL_FS_T TKL_FS;

/**
 * @brief get file system description
 *
 * @return TKL_FS instance
 */
TKL_FS_T* tkl_fs_desc_get(VOID_T);
//#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __TKL_INIT_SYSTEM_H__


