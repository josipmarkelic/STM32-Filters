#include "main.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stdbool.h"
#include "peripheral_init.h"
#include "filter.h"


volatile bool g_irq_happened = false;

void apply_selected_filter(float* input, float* output, int length);
void send_signal_pair(float* input, float* output, int length);

int main(void) {
    peripheral_init();

    // Send startup message
    HAL_UART_Transmit(&huart4, (uint8_t*)"System started\r\n", 15, HAL_MAX_DELAY);

    float input_normalized[ADC_BUFFER_SIZE];

    while (1) {
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, ADC_BUFFER_SIZE);
        HAL_Delay(15);  // Wait for conversion to complete

        // Normalize ADC values to voltage (0-3.3V)
        for (int i = 0; i < ADC_BUFFER_SIZE; i++) {
            input_normalized[i] = (float)adc_buffer[i] * 3.3f / 4095.0f;
        }

        // Check for button press
        if (g_irq_happened) {
            g_irq_happened = false;
            filter_type = (filter_type + 1) % 4;  // Cycle through 0-3
            memset(input_normalized, 0, sizeof(input_normalized));
            // Send filter change notification
            char msg[50];
            int len = snprintf(msg, sizeof(msg), "Filter changed to: %d\r\n", filter_type);
            HAL_UART_Transmit(&huart4, (uint8_t*)msg, len, HAL_MAX_DELAY);
        }

        apply_selected_filter(input_normalized, filtered_signal, ADC_BUFFER_SIZE);
        send_signal_pair(input_normalized, filtered_signal, ADC_BUFFER_SIZE);
    }
}


void apply_selected_filter(float* input, float* output, int length) {
    switch (filter_type) {
        case 0: apply_lowpass_filter(input, output, length); break;
        case 1: apply_highpass_filter(input, output, length); break;
        case 2: apply_bandpass_filter(input, output, length); break;
        case 3: apply_allpass_filter(input, output, length); break;
        default: apply_lowpass_filter(input, output, length); break;
    }
}


void send_signal_pair(float* input, float* output, int length) {
    for (int i = 0; i < length; i++) {
        int len = snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "%.4f,%.4f\r\n", input[i], output[i]);
        HAL_UART_Transmit(&huart4, (uint8_t*)uart_tx_buffer, len, HAL_MAX_DELAY);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == button_Pin) {
        // Simple debounce delay

        // Confirm button is still pressed
        if (HAL_GPIO_ReadPin(button_GPIO_Port, button_Pin) == GPIO_PIN_SET) {
            g_irq_happened = true;

            // Send debug message
            char dbg_msg[50];
            int len = snprintf(dbg_msg, sizeof(dbg_msg), "Button pressed! Current filter: %d\r\n", filter_type);
            HAL_UART_Transmit(&huart4, (uint8_t*)dbg_msg, len, HAL_MAX_DELAY);
        }
    }
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
