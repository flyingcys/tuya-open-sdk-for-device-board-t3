/**
* @file tkl_init_network.h
* @brief Common process - tkl init network description
* @version 0.1
* @date 2021-08-06
*
* @copyright Copyright 2021-2030 Tuya Inc. All Rights Reserved.
*
*/
#ifndef __TKL_INIT_NETWORK_H__
#define __TKL_INIT_NETWORK_H__

#include "tkl_network.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief the description of tuya kernel adapter layer network
 *
 */
typedef struct {
    TUYA_ERRNO            (*tkl_get_errno)          (VOID);
    OPERATE_RET           (*tkl_fd_set1)            (CONST int32_t fd, TUYA_FD_SET_T* fds);
    OPERATE_RET           (*tkl_fd_clear)           (CONST int32_t fd, TUYA_FD_SET_T* fds);
    OPERATE_RET           (*tkl_fd_isset)           (CONST int32_t fd, TUYA_FD_SET_T* fds);
    OPERATE_RET           (*tkl_fd_zero)            (TUYA_FD_SET_T* fds);
    int32_t                 (*tkl_select)             (CONST int32_t maxfd, TUYA_FD_SET_T *readfds, TUYA_FD_SET_T *writefds, TUYA_FD_SET_T *errorfds, CONST UINT_T ms_timeout);
    TUYA_ERRNO            (*tkl_close)              (CONST int32_t fd);
    int32_t                 (*tkl_socket_create)      (CONST TUYA_PROTOCOL_TYPE_E type);
    TUYA_ERRNO            (*tkl_connect)            (CONST int32_t fd, CONST TUYA_IP_ADDR_T addr, CONST UINT16_T port);
    TUYA_ERRNO            (*tkl_connect_raw)        (CONST int32_t fd, VOID *p_socket, CONST int32_t len);
    TUYA_ERRNO            (*tkl_bind)               (CONST int32_t fd, CONST TUYA_IP_ADDR_T addr, CONST UINT16_T port);
    TUYA_ERRNO            (*tkl_listen)             (CONST int32_t fd, CONST int32_t backlog);
    TUYA_ERRNO            (*tkl_send)               (CONST int32_t fd, CONST VOID *buf, CONST UINT_T nbytes);
    TUYA_ERRNO            (*tkl_send_to)            (CONST int32_t fd, CONST VOID *buf, CONST UINT_T nbytes, CONST TUYA_IP_ADDR_T addr, CONST UINT16_T port);
    TUYA_ERRNO            (*tkl_recv)               (CONST int32_t fd, VOID *buf, CONST UINT_T nbytes);
    TUYA_ERRNO            (*tkl_recvfrom)           (CONST int32_t fd, VOID *buf, CONST UINT_T nbytes, TUYA_IP_ADDR_T *addr, UINT16_T *port);
    TUYA_ERRNO            (*tkl_accept)             (CONST int32_t fd, TUYA_IP_ADDR_T *addr, UINT16_T *port);
    int32_t                 (*tkl_recv_nd_size)       (CONST int32_t fd, VOID *buf, CONST UINT_T buf_size, CONST UINT_T nd_size);
    OPERATE_RET           (*tkl_socket_bind)        (CONST int32_t fd, CONST CHAR_T *ip);
    OPERATE_RET           (*tkl_set_block)          (CONST int32_t fd, CONST BOOL_T block);
    OPERATE_RET           (*tkl_set_cloexec)        (CONST int32_t fd);
    OPERATE_RET           (*tkl_get_socket_ip)      (CONST int32_t fd, TUYA_IP_ADDR_T *addr);
    int32_t                 (*tkl_get_nonblock)       (CONST int32_t fd);
    OPERATE_RET           (*tkl_gethostbyname)      (CONST CHAR_T *domain, TUYA_IP_ADDR_T *addr);
    TUYA_IP_ADDR_T        (*tkl_str2addr)           (CONST CHAR_T *ip_str);
    CHAR_T*               (*tkl_addr2str)           (CONST TUYA_IP_ADDR_T ipaddr);
    OPERATE_RET           (*tkl_setsockopt)         (CONST int32_t fd, CONST TUYA_OPT_LEVEL level, CONST TUYA_OPT_NAME optname, CONST VOID_T *optval, CONST int32_t optlen);
    OPERATE_RET           (*tkl_getsockopt)         (CONST int32_t fd, CONST TUYA_OPT_LEVEL level, CONST TUYA_OPT_NAME optname, VOID_T *optval, int32_t *optlen);
    OPERATE_RET           (*tkl_set_timeout)        (CONST int32_t fd, CONST int32_t ms_timeout, CONST TUYA_TRANS_TYPE_E type);
    OPERATE_RET           (*tkl_set_bufsize)        (CONST int32_t fd, CONST int32_t buf_size, CONST TUYA_TRANS_TYPE_E type);
    OPERATE_RET           (*tkl_set_reuse)          (CONST int32_t fd);
    OPERATE_RET           (*tkl_disable_nagle)      (CONST int32_t fd);
    OPERATE_RET           (*tkl_set_broadcast)      (CONST int32_t fd);
    OPERATE_RET           (*tkl_set_keepalive)      (int32_t fd, CONST BOOL_T alive, CONST UINT_T idle, CONST UINT_T intr, CONST UINT_T cnt);
    OPERATE_RET           (*tkl_getsockname)        (int32_t fd, TUYA_IP_ADDR_T *addr, UINT16_T *port);
    OPERATE_RET           (*tkl_getpeername)        (int32_t fd, TUYA_IP_ADDR_T *addr, UINT16_T *port);
    OPERATE_RET           (*tkl_sethostname)        (CONST CHAR_T *hostname);
} TKL_NETWORK_DESC_T;

/**
 * @brief register wired description to tuya object manage
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
TKL_NETWORK_DESC_T* tkl_network_desc_get(VOID_T);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __TKL_INIT_WIRED_H__

