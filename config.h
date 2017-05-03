#ifndef CONFIG_H
    #define CONFIG_H
    //Encoder Config
    #define EN1 31
    #define EN2 33
    #define ENC 35
    #define ENSTP 4
    //Buzzer Config
    #define BEEPER_PIN 37
    //LCD config
    #define LCD_PINS_RS 16
    #define LCD_PINS_ENABLE 17
    #define LCD_PINS_D4 23
    #define LCD_PINS_D5 25
    #define LCD_PINS_D6 27
    #define LCD_PINS_D7 29
    //TEMP_SENSORS
    #define TEMP_LICOR_PIN         13   // ANALOG NUMBERING
    #define TEMP_MACERADOR_PIN         15   // ANALOG NUMBERING
    #define TEMP_HERVIDO_PIN       14   // ANALOG NUMBERING
    //Types
    typedef unsigned long millis_t;
#endif