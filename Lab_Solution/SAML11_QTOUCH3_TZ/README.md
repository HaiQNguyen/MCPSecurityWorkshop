# Access control application using Peripheral Touch Controller and Arm TrustZone on SAML11

## Overview

This  application  demonstrates the access  control  use  case  by  using  a QT3 Xplained keypad and SAML11 microcontroller with Arm TrustZone capability. 

![use case setup](https://bitbucket.org/hainguyenprivaterepo/saml11_qtouch3/raw/1c3965249a527dc3779545e33792832308e16501/Image/setup.jpg)

## Requirements

### Hardware

* SAML11 Xplained board
* QT3 Xplained board
* Type A - micro USB cable

### Software

* Atmel Studio
* TeraTerm

## Description 

![Use case diagram](https://bitbucket.org/hainguyenprivaterepo/saml11_qtouch3/raw/1c3965249a527dc3779545e33792832308e16501/Image/Usecase_Diagram.png)

The secure application located in TrustZone initializes the PTC and process the input from the keypad. Whenever user presses a key,the pressed key is displayed on the console terminal. The user can enter the pass code through the keypad. The user can enter number from 0 –9 as pass code, clear the previous value, and start authenticating.

![OUtput on terminal](https://bitbucket.org/hainguyenprivaterepo/saml11_qtouch3/raw/1c3965249a527dc3779545e33792832308e16501/Image/ConsoleTerminal.png)

When the authentication process has been started, the secure application verifies if the passcode entered by user is correct or not, and prints the result on the console terminal.

## How to run the use case

Download the project to your machine  
Open the project with Atmel Studio  
Compile the project  
Start TeraTerm with the following configuration:  

* Baud: 9600
* Data: 8 bits
* Stop bit: 1 bit
* Parity: none

In Atmel Studio, run the project.

Enter the pass code using key pad from 0 to 9. The pass code has 5 digits. The correct pass quote is 63263

User can clear the previous digit by pressing keypad "C"

User can start authentication by pressing key "#"

## Contact  

Quang Hai Nguyen  

Field Application Engineer  

Arrow Central Europe GmbH  

qnguyen@arroweurope.com  

   