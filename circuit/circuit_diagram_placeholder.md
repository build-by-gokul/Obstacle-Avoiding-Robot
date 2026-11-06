# 📐 Circuit Diagram — Placeholder

> **Reconstruction Notice:** The original circuit diagram from the first-year
> college project is no longer available. This placeholder documents what the
> diagram should contain and how to create one.

## Status: ⏳ Diagram Not Yet Created

A proper circuit/schematic diagram needs to be created using one of the recommended tools below.

## What the Diagram Should Show

The circuit diagram should clearly illustrate:

1. **Arduino Uno** with labeled pin connections
2. **HC-SR04 Ultrasonic Sensor** with VCC, TRIG, ECHO, GND connections
3. **L298N Motor Driver** with all control pins, power terminals, and motor outputs
4. **Four DC Motors** connected in two pairs (left pair, right pair)
5. **Battery Pack** with polarity markings
6. **Common ground connections** between all components
7. **Power distribution** paths clearly marked
8. **Wire labels** indicating signal names

## Recommended Tools for Creating the Diagram

### Free Online Tools
| Tool | URL | Best For |
|------|-----|----------|
| Tinkercad Circuits | https://www.tinkercad.com | Beginners — drag-and-drop, includes simulation |
| Fritzing | https://fritzing.org | Breadboard-style diagrams, very visual |
| Circuit.io | https://www.circuito.io | Auto-generates wiring guides |

### Professional Tools
| Tool | URL | Best For |
|------|-----|----------|
| KiCad | https://www.kicad.org | Professional PCB design (free, open-source) |
| EasyEDA | https://easyeda.com | Online schematic + PCB design |
| Eagle | https://www.autodesk.com/products/eagle | Industry-standard PCB design |

## How to Add the Diagram

1. Create the circuit diagram using one of the tools above
2. Export as PNG or SVG (recommended resolution: 1920×1080 or higher)
3. Save the file to the `images/` directory:
   - `images/circuit_diagram.png` — for a visual wiring diagram
   - `images/schematic_diagram.png` — for a formal schematic
4. Update the main `README.md` to reference the image:
   ```markdown
   ![Circuit Diagram](images/circuit_diagram.png)
   ```
5. Update this file to indicate the diagram has been added

## Text-Based Connection Reference

Until a visual diagram is available, refer to:
- [`wiring_guide.md`](wiring_guide.md) — Complete wiring instructions
- [`pin_configuration.md`](pin_configuration.md) — Pin mapping tables
