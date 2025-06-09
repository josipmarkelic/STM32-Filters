# 🎛️ STM32-Digital-Filter

A flexible and efficient digital filter project using STM32F407 microcontroller. This project demonstrates real-time signal filtering using IIR filters (Low-pass, High-pass, Band-pass, Band-stop) implemented in C. The filtering is performed using the STM32’s ADC, DAC, and DMA peripherals, suitable for audio signal processing, sensor data conditioning, or lab experimentation.

---

## ✨ Features

✅ Real-time signal filtering with IIR filter design  
✅ Supports four filter types: Low-pass, High-pass, Band-pass, and Band-stop  
✅ Efficient DMA-based data handling (ADC-to-memory, memory-to-DAC)  
✅ Configurable filter coefficients (e.g., via MATLAB or Python design tools)  
✅ Minimal CPU overhead using interrupt/DMA-driven processing  
✅ STM32F407 compatible (e.g., STM32F4Discovery board)  
✅ Ideal for educational use, DSP learning, or lab testing

---

## 🧰 Requirements

- STM32F407 microcontroller (tested on STM32F4Discovery)  
- STM32CubeIDE  
- STM32 HAL library  
- UART or USB (optional for debugging or filter switching)

---

## 📁 Project Structure

```
Src/     – Source files for filtering, peripherals, and main control loop  
Inc/     – Header files and filter coefficient definitions  
Core/    – Startup code, system config, and initialization  
Filters/ – IIR filter implementation (coefficients, processing functions)
```

---

## 🚀 Getting Started

1. Flash firmware to STM32F407 board  
2. Connect analog input to ADC (e.g., via function generator or sensor)  
3. Connect DAC output to oscilloscope or speaker  
4. Select desired filter via code or UART interface  
5. Observe filtered output in real-time

---

## 📊 Filter Details

- **Low-Pass**: Passes low frequencies, attenuates high frequencies  
- **High-Pass**: Passes high frequencies, attenuates low frequencies  
- **Band-Pass**: Passes a specific frequency range  
- **Band-Stop (Notch)**: Rejects a specific frequency range  
- **Design**: Filters implemented as IIR (e.g., biquad form)
