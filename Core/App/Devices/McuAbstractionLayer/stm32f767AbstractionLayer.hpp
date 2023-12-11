/*
 * stm32f767AbstractionLayer.hpp
 *
 *  Created on: Dec 4, 2023
 *      Author: G4T1PR0
 */

#ifndef APP_DEVICES_STM32F767ABSTRACTIONLAYER_STM32F767ABSTRACTIONLAYER_HPP_
#define APP_DEVICES_STM32F767ABSTRACTIONLAYER_STM32F767ABSTRACTIONLAYER_HPP_

#include <Devices/McuAbstractionLayer/baseMcuAbstractionLayer.hpp>

#define UART_RX_BUFFER_SIZE 64

class stm32f767AbstractionLayer : public baseMcuAbstractionLayer {
   public:
    virtual void init(void);

    virtual uint16_t adcGetValue(Peripheral_ADC p);

    virtual void pwmSetDuty(Peripheral_PWM p, float duty);

    virtual void encoderSetCnt(Peripheral_Encoder p, uint32_t cnt);
    virtual uint32_t encoderGetCnt(Peripheral_Encoder p);

    virtual void gpioSetValue(Peripheral_GPIO p, bool value);
    virtual bool gpioGetValue(Peripheral_GPIO p);

   private:
    // ADC
    void _initADC();
    static uint16_t _data[16];

    // Timer Encoder
    void _initEncoder();

    // Timer PWM
    void _initPWM();

    // UART
    void __initUART();
    static uint8_t _uart5RxBuffer[UART_RX_BUFFER_SIZE];
    static uint8_t _usart3RxBuffer[UART_RX_BUFFER_SIZE];
};

#endif /* APP_DEVICES_STM32F767ABSTRACTIONLAYER_STM32F767ABSTRACTIONLAYER_HPP_ */