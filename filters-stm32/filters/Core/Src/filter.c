#include "main.h"
#include "filter.h"
#include "stdio.h"

uint16_t adc_buffer[ADC_BUFFER_SIZE];
char uart_tx_buffer[UART_BUFFER_SIZE];
float filtered_signal[ADC_BUFFER_SIZE];
volatile uint16_t filter_type = 0;

void apply_lowpass_filter(float* input, float* output, int length) {
    float fc = 100.0f;                   // cutoff frequency
    float dt = 1.0f / SAMPLE_RATE;       // time between samples
    float RC = 1.0f / (2.0f * PI * fc);  // RC constant
    float alpha = dt / (RC + dt);
    output[0] = input[0];
    for (int i = 1; i < length; i++) {
        output[i] = alpha * input[i] + (1 - alpha) * output[i - 1];
    }
}

void apply_highpass_filter(float* input, float* output, int length) {
    float fc = 100.0f;  // cutoff frequency (Hz)
    float RC = 1.0f / (2.0f * PI * fc);
    float dt = 1.0f / SAMPLE_RATE;
    float alpha = RC / (RC + dt);
    output[0] = input[0];
    for (int i = 1; i < length; i++) {
        output[i] = alpha * (output[i - 1] + input[i] - input[i - 1]);
    }
}

void apply_bandpass_filter(float* input, float* output, int length) {
    float temp[ADC_BUFFER_SIZE];

    // First apply high-pass filter (500 Hz cutoff)
    float fc_high = 500.0f;
    float dt = 1.0f / SAMPLE_RATE;
    float RC_high = 1.0f / (2.0f * PI * fc_high);
    float alpha_high = RC_high / (RC_high + dt);
    temp[0] = input[0];
    for (int i = 1; i < length; i++) {
        temp[i] = alpha_high * (temp[i - 1] + input[i] - input[i - 1]);
    }

    // Then apply low-pass filter (3000 Hz cutoff)
    float fc_low = 3000.0f;
    float RC_low = 1.0f / (2.0f * PI * fc_low);
    float alpha_low = dt / (RC_low + dt);
    output[0] = temp[0];
    for (int i = 1; i < length; i++) {
        output[i] = output[i - 1] + alpha_low * (temp[i] - output[i - 1]);
    }
}

void apply_allpass_filter(float* input, float* output, int length) {
    float fc = 100.0f;                   // cutoff frequency
    float dt = 1.0f / SAMPLE_RATE;
    float RC = 1.0f / (2.0f * PI * fc);
    float alpha = (RC - dt) / (RC + dt);

    output[0] = input[0];
    for (int i = 1; i < length; i++) {
        output[i] = -alpha * input[i] + input[i - 1] + alpha * output[i - 1];
    }
}
