# Laser-Tank-Project
Freshman video game design project (04/18/2016-05/3/2016)
group members: Miguel Salinas, Charley Yeng, Shwetha Swaminathan

This project was unsucessful due to too many levels of complexity. Throughout the project's final phase,the group struggled with connecting all the individual modules. Some of the main problems were:
  
  Multiple members of the team used busy-wait to poll the sensons which reduced performace when all the modules were connected.
  PWM functions were not created using interunt service routeens, causing the PWM fuctions to act much slower than intended.
  We used a chain of 4 devices to send and recieve information through UART(TI TM4C123G LaunchPad to one arduino bluetooth module to another arduino bluetooth module to TM4C123G LaunchPad) and we did not used the proper harware to implement the design correctly.
  
Leasson learned:
  In projects the involve numerous hardware devices that need to link together, it is important to use a lower-level coding language, such as C or assembly.
  Establish consistent naming standards with all members of the group helps debuging.
  Strong group communication and regular "check-ins" are needed to keep the team working smoothly and create accurate expectations for final results.
  
  
