---
title: note

description: text note

categories:
 - object
pdcategory: GUI

arguments:
- description: none
  type:
  default:

inlets:
  1st:
  - description: sets a new text note
    type: set <anything>

flags:
  - name: -font <symbol>
    description: default: 'dejavu sans mono' or 'menlo' for mac
  - name: -bold
    description:
  - name: -italic
    description:
  - name: -size <float>
    description: default patch's
  - name: -just <float>
    description: default 0
  - name: -color <f, f, f>
    description: default 0 0 0
  - name: -bgcolor <f, f, f>
    description: default 255 255 255
  - name: -bg
    description:
  - name: -outline
    description:
  - name: -note <anything>
    description: sets note (default "note")
  - name: -underline
    description:
  - name: -receive <symbol>
    description: default 'empty'
  - name: -width <float>
    description: default 0

methods:
  - type: set <anything>
    description: sets a new text note
  - type: append <anything>
    description: appends a message to the note
  - type: prepend <anything>
    description: prepends a message to the note
  - type: font <symbol>
    description: sets font name
  - type: size <float>
    description: sets font size
  - type: bold <float>
    description: non zero sets to bold
  - type: italic <float>
    description: non zero sets to italic
  - type: underline <float>
    description: non zero sets underline
  - type: just <float>
    description: sets justification (0: left, 1: center, 2: right)
  - type: width <float>
    description: sets width in pixels
  - type: color <f, f, f>
    description: sets RGB text color (values from 0 to 255)
  - type: bgcolor <f, f, f>
    description: sets RGB background color (values from 0 to 255)
  - type: bg <float>
    description: background flag (0 suppresses background)
  - type: outline <float>
    description: non zero sets an outline
  - type: receive <symbol>
    description: sets receive symbol
---

[note] is a GUI meant only to display text notes. This is basically the same of Pd's comment but with the advantage of being able to set the font, size, color, background color, bold, italic, underline and justification.
