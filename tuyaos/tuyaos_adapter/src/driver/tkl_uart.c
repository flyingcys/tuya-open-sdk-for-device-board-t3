#include "tkl_uart.h"

#include "drv_model_pub.h"
#include "uart_pub.h"
// #include "BkDriverUart.h"
#include <driver/uart.h>
#include "uart_statis.h"
#include "bk_uart.h"
//#include "uart.h"
#include <components/log.h>

#define UART_TAG "uart"
#define UART_LOGI(...) BK_LOGI(UART_TAG, ##__VA_ARGS__)
#define UART_LOGW(...) BK_LOGW(UART_TAG, ##__VA_ARGS__)
#define UART_LOGE(...) BK_LOGE(UART_TAG, ##__VA_ARGS__)
#define UART_LOGD(...) BK_LOGD(UART_TAG, ##__VA_ARGS__)

#define CLI_GETCHAR_TIMEOUT           (120000)

volatile int g_test_mode = 1;

/**
 * @brief uart init
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] cfg: uart config
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_uart_init(TUYA_UART_NUM_E port_id, TUYA_UART_BASE_CFG_T *cfg)
{
    int port_num = TUYA_UART_GET_PORT_NUMBER(port_id);
    uart_id_t port;
    uart_config_t bkcfg;

    memset(&bkcfg, 0, sizeof(uart_config_t));

    if(CONFIG_UART_PRINT_PORT == port_num) {
        UART_LOGI("tkl_uart_init: print port already init.\n");
        return OPRT_INVALID_PARM;
    } else if (0 == port_num) {
        port = UART_ID_0;
    } else if (1 == port_num) {
        port = UART_ID_1;
    } else {
        return OPRT_INVALID_PARM;
    }

    //! data bits
    if (TUYA_UART_DATA_LEN_5BIT == cfg->databits) {
        bkcfg.data_bits = UART_DATA_5_BITS;
    } else if (TUYA_UART_DATA_LEN_6BIT == cfg->databits) {
        bkcfg.data_bits = UART_DATA_6_BITS;
    } else if (TUYA_UART_DATA_LEN_7BIT ==  cfg->databits) {
        bkcfg.data_bits = UART_DATA_7_BITS;
    } else if (TUYA_UART_DATA_LEN_8BIT == cfg->databits) {
        bkcfg.data_bits = UART_DATA_8_BITS;
    } else {
        return OPRT_OS_ADAPTER_INVALID_PARM;
    }

    //! stop bits
    if (TUYA_UART_STOP_LEN_1BIT == cfg->stopbits) {
        bkcfg.stop_bits = UART_STOP_BITS_1;
    } else if (TUYA_UART_STOP_LEN_2BIT == cfg->stopbits) {
        bkcfg.stop_bits = UART_STOP_BITS_2;
    } else {
        return OPRT_OS_ADAPTER_INVALID_PARM;
    }

    //!  parity bits
    if (TUYA_UART_PARITY_TYPE_NONE == cfg->parity) {
        bkcfg.parity = UART_PARITY_NONE;
    } else if (TUYA_UART_PARITY_TYPE_EVEN == cfg->parity) {
        bkcfg.parity = UART_PARITY_EVEN;
    } else if (TUYA_UART_PARITY_TYPE_ODD == cfg->parity) {
        bkcfg.parity = UART_PARITY_ODD;
    } else {
        return OPRT_OS_ADAPTER_INVALID_PARM;
    }

    bkcfg.baud_rate = cfg->baudrate;
    bkcfg.flow_ctrl = UART_FLOWCTRL_DISABLE;
    bkcfg.src_clk   = UART_SCLK_XTAL_26M;

    bk_printf("tkl_uart_init, port: %d, baudrate %d\r\n", port_num, cfg->baudrate);

    bk_uart_init(port, &bkcfg);

    return OPRT_OK;
}

/**
 * @brief uart deinit
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_uart_deinit(TUYA_UART_NUM_E port_id)
{
    int port_num = TUYA_UART_GET_PORT_NUMBER(port_id);
    uart_id_t port;

    if( CONFIG_UART_PRINT_PORT == port_num)
    {
        UART_LOGI("tkl_uart_init: print port already inuse.\n");
        return OPRT_INVALID_PARM;
    } else if ( 0 == port_num)
    {
        port = UART_ID_0;
    } else if ( 1 == port_num)
    {
        port = UART_ID_1;
    } else
    {
        return OPRT_INVALID_PARM;
    }
    bk_uart_deinit(port);
    return OPRT_OK;
}

/**
 * @brief uart write data
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] data: write buff
 * @param[in] len:  buff len
 *
 * @return return > 0: number of data written; return <= 0: write errror
 */

int32_t tkl_uart_write(TUYA_UART_NUM_E port_id, VOID_T *buff, UINT16_T len)
{
    uart_id_t port;

    if (0 == TUYA_UART_GET_PORT_NUMBER(port_id)) {
        port = UART_ID_0;
    } else if ( 1 == TUYA_UART_GET_PORT_NUMBER(port_id)) {
        port = UART_ID_1;
    } else {
        return OPRT_INVALID_PARM;
    }

    bk_uart_write_bytes(port, buff, len);
    return len;
}

/**
 * @brief uart read data
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[out] data: read data
 * @param[in] len:  buff len
 *
 * @return return >= 0: number of data read; return < 0: read errror
 */
int32_t tkl_uart_read(TUYA_UART_NUM_E port_id, VOID_T *buff, UINT16_T len)
{
    uart_id_t port;

    if ( 0 == TUYA_UART_GET_PORT_NUMBER(port_id)) {
        port = UART_ID_0;
    } else if ( 1 == TUYA_UART_GET_PORT_NUMBER(port_id)) {
        port = UART_ID_1;
    } else {
        return OPRT_INVALID_PARM;
    }

    uint32_t length = bk_uart_read_bytes(port, buff, len, CLI_GETCHAR_TIMEOUT);

    return length;
}

/**
 * @brief set uart transmit interrupt status
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] enable: TRUE-enalbe tx int, FALSE-disable tx int
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_uart_set_tx_int(TUYA_UART_NUM_E port_id, BOOL_T enable)
{
    return OPRT_OK;
}

/**
 * @brief set uart receive flowcontrol
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] enable: TRUE-enalbe rx flowcontrol, FALSE-disable rx flowcontrol
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_uart_set_rx_flowctrl(TUYA_UART_NUM_E port_id, BOOL_T enable)
{
    return OPRT_OK;
}

void uart_dev_irq_handler(int uport, void *param)
{
    TUYA_UART_IRQ_CB uart_irq_cb = (TUYA_UART_IRQ_CB)param;

    uart_irq_cb((UINT_T)uport);
}

TUYA_UART_IRQ_CB tkl_rx_cb = NULL;
static void uart_isr_t_cb(uart_id_t id, void  *param) {
    if (NULL != tkl_rx_cb) {
        tkl_rx_cb((UINT_T)id);
    }
}
/**
 * @brief enable uart rx interrupt and regist interrupt callback
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] rx_cb: receive callback
 *
 * @return none
 */
VOID_T tkl_uart_rx_irq_cb_reg(TUYA_UART_NUM_E port_id, TUYA_UART_IRQ_CB rx_cb)
{
    int port_num = TUYA_UART_GET_PORT_NUMBER(port_id);
    uart_id_t port;

    UART_LOGI("tkl_uart_rx_irq_cb_reg: port_num(%d).rx_cb(%p).\n", port_num, rx_cb);

    if( CONFIG_UART_PRINT_PORT == port_num) {
        UART_LOGI("tkl_uart_rx_irq_cb_reg: print port already inuse.\n");
        return;
    } else if ( 0 == port_num) {
        port = UART_ID_0;
    } else if ( 1 == port_num) {
        port = UART_ID_1;
    } else {
        return;
    }
    tkl_rx_cb = rx_cb;

    bk_uart_disable_sw_fifo(port);
	bk_uart_register_rx_isr(port, uart_isr_t_cb, NULL);
    bk_uart_enable_rx_interrupt(port);
}

/**
 * @brief regist uart tx interrupt callback
 * If this function is called, it indicates that the data is sent asynchronously through interrupt,
 * and then write is invoked to initiate asynchronous transmission.
 *
 * @param[in] port_id: uart port id,
 *                     the high 16bit - uart type
 *                                      it's value must be one of the TKL_UART_TYPE_E type
 *                     the low 16bit - uart port number
 *                     you can input like this TKL_UART_PORT_ID(TKL_UART_SYS, 2)
 * @param[in] rx_cb: receive callback
 *
 * @return none
 */
VOID_T tkl_uart_tx_irq_cb_reg(TUYA_UART_NUM_E port_id, TUYA_UART_IRQ_CB tx_cb)
{

}