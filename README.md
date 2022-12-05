# arduino-drone

This is my repository for my open-source drone flight controller and remote using 2 ARDUINOs and 2 NODEMCUs.

# Drone

## Flight Controller
I am using one arduino as a main flight controller. This has a MPU-6050, as an inertial measurement sensor (6-Axis Accelaerometer + Gyroscope). It communicates with the arduino flight controller with I2C protocol (Inter Integrated Communication). Also, it receives the controller data from Nodemcu via SPI protocol (Serial Peripherral Interface).

## Server
One nodemcu (ESP8266) is used for receiving the controller data. It hosts a server, along with a websocket, to receive data from the controller. After receiving, it sends data to flight controller, in special format via SPI.
Ex-> <49,42,47,59>

# Controller

## Analog Reader
One Arduino is reading 4 analog values from 2 joy-sticks. It is working as an I2C slave, which sends 16X4-bit data to master (Client), when requested.

## Client
This nodemcu is used to connect to the server and the websocket. It is configured as an I2C master, which requests and receives data from arduino slave, that contains joy-stick values. Then, it sends websocket event to the server, with JSON paylaod, which is processed in server and ultimately sent to the flight controller.
