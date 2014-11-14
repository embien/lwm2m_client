                        LWM2M Client for SkyCase/REST and Server/CoAP
                        =============================================
This file provides a brief overview of the source code organization of the project.
The primary directories in the project are 
app         - Contains application implementations. User can implement new applications
              here or compile the rest of the code as library and link with thier application.
  full_demo - A Command line demo to test each communication funcaitonality
  xor_demo  - A demo application that integrates with the XoR2 Demo app in SkyCase IoT Store 
              for digital IO manipulation
bin         - Contains compilation procedures and make files
  frdm_kl25 - For Freescale FRDM-KL25 board
  rpi       - For Raspberry PI
  win32     - For Win32
comm        - Implements lower level communication protocols
  coap      - CoAP implementation
  skycase   - REST implementation
doc         - Documentation
hal         - Hardware Abstraction Layer
  frdm_kl25 - For Freescale FRDM-KL25 board
  rpi       - For Raspberry PI
  win32     - For Win32
lwm2m       - Higher level object implementation for LWM2M
  core      - Core functions
  objects   - Object implementations
misc        - Other utilities and libraries
  