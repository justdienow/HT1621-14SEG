# Arduino library to work with LCD via HT1621 controller

## WHY

The HT1621 chip is used in many consumer electronic appliances such as stereo units, microwaves, VCR's, and DVD players. The process of salvaging and the reuse of these parts can bring new life to what was destined to become landfill.

Most Chips are from Holtek, but any 48-pin SSOP with 1621 in it's name is probably an HT.

An added bonus, the HT1621 chip has an integrated 2Khz/4Khz buzzer pins, howerver, not utilised in this case.

## WHAT

The HT1621 is a 128 pattern (32x4), memory mapping, and multi-function LCD driver. 
The S/W configuration feature of the HT1621 makes it suitable for multiple LCD applications including LCD modules and display subsystems.
Only 3 or 4 lines are required for the interface between the host controller and the HT1621.
The HT1621 contains a power down command to reduce power consumption.
Operating voltage is 2.4 - 5.2 V.

## CIRCUIT

Bellow is a screenshot of the panel circuit, from the Panasonic SC-HC20 Service Manual.  
![Panel Circuit](/extras/PanelCircuit.png)

## Links

- Datasheet: <https://www.holtek.com/documents/10179/116711/HT1621v321.pdf>
- [Enumerating LCD segments with OpenCV for reverse-engineering](https://eleif.net/lcd-segmentation.html)
- Original source code and idea: <https://macduino.blogspot.com/2015/02/HT1621.html>
- Fork from https://github.com/ipanin/ht1621ex
