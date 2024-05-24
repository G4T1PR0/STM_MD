/*
 * stm32halAbstractionLayer.hpp
 *
 *  Created on: Dec 4, 2023
 *      Author: G4T1PR0
 */

#ifndef APP_DEVICES_STM32HALABSTRACTIONLAYER_STM32HALABSTRACTIONLAYER_HPP_
#define APP_DEVICES_STM32HALABSTRACTIONLAYER_STM32HALABSTRACTIONLAYER_HPP_

#include <Devices/McuAbstractionLayer/RingBuffer.hpp>
#include <Devices/McuAbstractionLayer/baseMcuAbstractionLayer.hpp>

#define UART_BUFFER_SIZE 512
#define ADC_BUFFER_SIZE 50

class stm32halAbstractionLayer : public baseMcuAbstractionLayer {
   public:
    stm32halAbstractionLayer();
    virtual void init(void);

    // ADC
    virtual uint16_t adcGetValue(P_ADC p);
    virtual void adcGetBufferValue(P_ADC p, uint16_t* buffer, uint16_t size);

    // PWM
    virtual void pwmSetDuty(P_PWM p, float duty);
    virtual void pwmSetFrequency(P_PWM p, uint32_t frequency);

    // Encoder
    virtual void encoderSetCnt(P_Encoder p, uint32_t cnt);
    virtual uint32_t encoderGetCnt(P_Encoder p);

    // GPIO
    virtual void gpioSetValue(P_GPIO p, bool value);
    virtual bool gpioGetValue(P_GPIO p);

    // UART
    virtual void uartPutChar(P_UART p, uint8_t data);
    virtual uint8_t uartGetChar(P_UART p);

    virtual void uartWriteViaBuffer(P_UART p, uint8_t* data, uint32_t size);
    virtual void uartReadViaBuffer(P_UART p, uint8_t* data, uint32_t size);
    virtual uint32_t uartGetRxDataSize(P_UART p);

    // Interrupt
    virtual void interruptSetCallback(P_Interrupt p, void (*callback)(void));
    static void (*_timerInterruptCallback[P_Interrupt::End_T])(void);

    // Wait
    virtual void waitMs(uint32_t ms);

   private:
    // ADC
    void _initADC();

    static uint16_t _data[3][3 * ADC_BUFFER_SIZE];

    // Timer Encoder
    void _initEncoder();

    // Timer PWM
    void _initPWM();
    unsigned int _current_pwm_hz[P_PWM::End_P] = {0};

    // UART
    void _initUART();
    uint32_t _uartGetRxBufferDmaWriteAddress(P_UART p);
    static RingBuffer<uint8_t, UART_BUFFER_SIZE> _uartRxBuffer[P_UART::End_U];
    uint32_t _uartRxBufferReadAddress[P_UART::End_U] = {0};

    // Interrupt
    void _initTimerInterrupt();
};

#endif /* APP_DEVICES_STM32HALABSTRACTIONLAYER_STM32HALABSTRACTIONLAYER_HPP_ */