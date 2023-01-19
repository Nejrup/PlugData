---
title: blip~

description: Bandlimited cosine oscillator  

categories:
- object

pdcategory: Audio Oscillators and Tables

arguments:
- type: float
  description: fundamental frequency in Hz
  default: 0
- type: float
  description: number of partials
  default: 1
- type: float
  description: spectral multiplier
  default: 1
- type: float
  description: lowest harmonic
  default: 1

inlets:
  1st:
  - type: float/signal
    description: fundamental frequency in Hz
  2nd:
  - type: signal
    description: impulses reset phase
  3rd:
  - type: float/signal
    description: phase modulationa input
  4th:
    - type: float/signal
      description: spectral multiplier

outlets:
  1st:
  - type: signal
    description: band limited oscillator output

methods:
  - type: n <float>
    description: number of partials
  - type: low <float>
    description: lowest harmonic

draft: false
---

[blip~] uses DSF (Discrete-Summation Formulae) to generate waveforms as a sum of cosines. It takes a frequency in hertz for the fundamental, a number of harmonics, a multiplier for the partials after the first one and the lowest harmonic number (by default it generates an impulse waveform). This object is based on Csound's 'gbuzz' opcode.
