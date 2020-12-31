# d_organ

Drone Organ Synthesizer. Manipulates high quality organ samples to create a powerful sound.

Built with the JUCE framework and a Raspberry Pi 

## Parts:

- 1X Raspberry Pi 4
- 24X Linear Potentiometers
- 4X Analog to Digital Converters (MCP3008)


## Layout / Functionality
- 4 Oscillators with "Gain" and "Frequency (Hz)" knobs
- Dedicated filter for each oscillator (mix of LPFs, HPFs, etc), as well as a master filter (LPF)
- LFOs for modulating the filter cutoff of the master filter, as well as oscillator 3's filter
- Built in delay and distortion effect (UNFINISHED)
<img src="https://github.com/tparker48/d_organ/blob/master/Images/layout1.jpg" />

