# Adjustable Bench Power Supply Enclosure

A custom-designed 3D printable enclosure for a portable laboratory bench power supply based on a high-power buck-boost converter module. The system can accept a wide input voltage range (7–70V DC) and provide an adjustable output from 2–55V at up to 20A, with a maximum power rating of 600W.

Unlike traditional bench power supplies, the design can be powered from a variety of sources including DC power supplies, batteries, USB-C Power Delivery adapters, and power banks supporting PD/QC protocols, making it suitable for both desktop and portable applications.

## Features

* Integrated mounting for a 10A digital voltmeter/ammeter display.
* Front panel support for:
  * 100kΩ 3590S precision multi-turn potentiometer for voltage adjustment.
  * 20kΩ potentiometer for current limiting adjustment.
* Hexagonal patten ventilation designed to improve airflow while maintaining structural strength.
* Adjustable fan placement to increase cooling efficiency across power components.
* Compact and organized front-panel layout for improved usability.
* Designed for straightforward FDM 3D printing and assembly.

## Design Improvements Following Testing

Initial testing revealed that while the power supply control board is capable of delivering up to 20A, the integrated digital ammeter is rated for only 10A. To prevent accidental overcurrent conditions and keep measurements within the meter's operating range, the current adjustment circuit was modified by replacing the original potentiometer with a 10kΩ unit and adding a 10kΩ resistor in series. This limits the maximum adjustable current to approximately 10A.

## Known Limitations

* The shunt resistor supplied with the 10A digital ammeter begins to heat noticeably at currents above approximately 5A.
* As shunt temperature increases, measurement accuracy decreases and the displayed current may read higher than the actual output current.
* Users should consider this limitation when operating near the upper end of the meter's range.

## Future Development

A next-generation enclosure and measurement system is currently under development, featuring:
* USB-C and DC female_port for  input integration.
* Higher-current shunt design capable of accurate measurements above 10A.
* Improved ventilation and airflow management with automated fan with temperature regulation
* USB-C output integration.
* Further refinement of component placement and serviceability.



## Components Used

* 100kΩ 3590S multi-turn potentiometer (voltage control)
* 10kΩ potentiometer with 10kΩ series resistor (current control)
* 10A digital voltmeter/ammeter
* Cooling fan
* Buck boost converter

## Intended Applications

* DIY laboratory bench power supplies
* Electronics prototyping and testing
* Educational electronics projects
* Repair and troubleshooting workstations

**Software:** Fusion 360
**Manufacturing Method:** FDM 3D Printing
**Project Status:** Functional Prototype (Revision 2 in development)

This project demonstrates practical engineering iteration, combining CAD design, electronics integration, thermal management, and real-world testing to improve the safety, usability, and reliability of a DIY bench power supply enclosure.
