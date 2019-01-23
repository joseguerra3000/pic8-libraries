# Library for 8bits PIC microcontrollers 

 This collection contains a set of routines implemented to facilitate the design of systems based on 8-bit PIC microcontrollers


## Compatibility 
* IDE     : MPLABX IDE v5.10 or any other IDE using XC8 v2.00 compiler.
* Compiler: XC8 v2.00

## Prerequisites
* MPLABX IDE v5.10 is recommended (go to microchip site for download).
* XC8 must be installed (go to microchip site for download).

## Structure
 The collection is divided on various sections.

### Peripheral 
 Contains routines to manipulate the peripherals of the microcontroller. 
 Internaly poses a folder for every microcontroler suported.

### Drivers 
 Contains routines for interaction with external components like LCD Display,
 Temperature Sensors, DAC, etc...
 Theoretically the implemented drivers are compatible with any 8 bit PIC microcontroller.

### Util
 Contains useful routines and macros like: character generator for displays, numerical methods, bit operation macros, etc...
 This section does not have dependencies with microcontrollers therefore it is compatible with any microcontroller.
  
## How to use
   1. **Create a New Project (Pick XC8 as compiler)**
   
   1.1 Go to File>New Project...
   
   2. **Add libray to your project**
   
   2.1. Copy library folder inside the project folder.
   
   2.2. Go to peripherial section and delete all folders except the folder of microcontroller used.
   
   2.3. Optionally you can delete all not used driver, but is not necessary.
   
   2.4. Right click on the project and select "Add existing Items from folders" 
   
   2.5. On 'Add Folder' window push Add Folder Button
   
   2.6. Go to the route of library on your project( Ex: my_project.X/library ).
   
   2.7. Select type of sources 'All Sources File' and click on Select button.
   
   2.8. Push Add button on the right-down corner.
   
   3. **Add _XTAL_FREQ macro as general macro**
   
   3.1. Go to Project Properties windows (File>Project Properties).
   
   3.2. Select the 'XC8 Compiler' Category (on left side of the window).
   
   3.3. Select the 'Preprocessing and Message' on 'Option Categories' (on top of the window).
   
   3.4. Use the option 'Define Macro' to define _XTAL_FREQ macro (down of 'Option Categories') with the Frequency used.
   
   Ex: _XTAL_FREQ=8000000.
   
   Now Generated command line have: -D_XTAL_FREQ=8000000 



