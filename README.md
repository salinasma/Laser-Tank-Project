# Laser-Tank-Project
Freshman video game design project. 
This project was not sucessfull due to too many levels of complexity. Throught the final phase of the project the group struggled with connecting all the individual modules. Some of the main problems were:
  Multiple members of the team used busy-wait to poll the sensons which reduced performace when all the modules were connected.
  PWM functions were not created using interunt service routeens, causing the PWM fuctions to act much slower than intended.
  We used a chain of 4 devices to send and recieve information though UART(TI TM4C123G LaunchPad to arduino bluetooth module to arduino bluetooth module to TM4C123G LaunchPad) and we did not used the proper harware to inplement the design correctly.
  
Leasson learned:
  Importance of using a lower level language, like C or assembly, in projects the involve numerous hardware devices that need to link together.
  Consistent naming standards amough all members of the group helps debuging.
  Strong communication skills are needed to keep the team working smoothly.
  
  
