Project is based on Seeed Lora-E5 Dev board from a baerebones configuration. All the project I could find where base on STM Nucleo version of the chip.  
Hardware:
  - Seeed Lora-#5 Dev Board (LM75ADP)
  - St-Link/V2
  - M5 ENV. IV Sensor (SHT40, BMP280)

Tasks 
  - Open new project boiler template using stm32cubemx - done but need to add Lora boiler template software
  - implementation of 2IC2 - PA15 - SDA, PB15 - SCL and PA9 - 3V3 power enable (Functional)
  - implementation of 2IC2 LM75ADP - on board temp sensor (Functional)
  - implementation of 2IC2 SHT40 - plan to import existing code from external sources Temperature and Humidty (Not Functional)
  - implementation of 2IC2 BMP280 - plan to import existing code from external sources Temperature and Pressure (Not Functional)
  - implementation of Lora connect to Chirpstack bridge (Not Functional)
