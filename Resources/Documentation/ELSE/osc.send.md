---
title: osc.send
description: Send OSC messages

categories:
 - object

pdcategory: General

arguments:
  - type: anything
    description: address/port to connect to at load time

inlets:
  1st:
  - type: disconnect
    description: disconnect from network
  - type: connect <address, port>
    description: connect to address/port

outlets:
  1st:
  - type: float
    description: connection status

---

[osc.send] sends OSC messages over the network and is an abstraction based on [osc.format] and [netsend].

