#ifndef FILTER_H
#define FILTER_H

typedef enum {
    LOW_PASS,
    HIGH_PASS,
    BAND_PASS,
    ALL_PASS
} FilterType;

extern uint16_t adc_buffer[ADC_BUFFER_SIZE];
extern char uart_tx_buffer[UART_BUFFER_SIZE];
extern float filtered_signal[ADC_BUFFER_SIZE];
extern volatile uint16_t filter_type;

void apply_lowpass_filter(float* input, float* output, int length);
void apply_highpass_filter(float* input, float* output, int length);
void apply_bandpass_filter(float* input, float* output, int length);
void apply_allpass_filter(float* input, float* output, int length);


#endif // FILTER_H
