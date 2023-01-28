---
title: lastvalue~

description: report last value

categories:
 - object

pdcategory: Analysis

arguments:
- type: float
  description: initial last value
  default: 0

inlets:
  1st:
  - type: signal
    description: signal to detect the last value
  2nd:
  - type: float
    description: set new last value

outlets:
  1st:
  - type: signal
    description: last input value

---

[lastvalue~] reports the last value when the signal changes

