
#include <Arduino.h>
#define IR_RECEIVE_PIN 14
// #include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#if !defined(RAW_BUFFER_LENGTH)
#if RAMEND <= 0x4FF || RAMSIZE < 0x4FF
#define RAW_BUFFER_LENGTH 180  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#elif RAMEND <= 0x8FF || RAMSIZE < 0x8FF
#define RAW_BUFFER_LENGTH 600  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#else
#define RAW_BUFFER_LENGTH 750  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#endif
#endif

/*
 * MARK_EXCESS_MICROS is subtracted from all marks and added to all spaces before decoding,
 * to compensate for the signal forming of different IR receiver modules. See also IRremote.hpp line 142.
 *
 * You can change this value accordingly to the receiver module you use.
 * The required value can be derived from the timings printed here.
 * Keep in mind that the timings may change with the distance
 * between sender and receiver as well as with the ambient light intensity.
 */
#define MARK_EXCESS_MICROS 20  // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

#define RECORD_GAP_MICROS 50000 // Default is 5000. Activate it for some LG air conditioner protocols
//#define DEBUG // Activate this for lots of lovely debug output from the decoders.

#include <IRremote.hpp>

//+=============================================================================
// Configure the Arduino

void setup() {

  Serial.begin(115200);  // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/ || defined(USBCON) /*STM32_stm32*/ || defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
  delay(4000);  // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  // Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));

  // infos for receive
  Serial.print(RECORD_GAP_MICROS);
  Serial.println(F(" us is the (minimum) gap, after which the start of a new IR packet is assumed"));
  Serial.print(MARK_EXCESS_MICROS);
  Serial.println();
  Serial.println(F("Because of the verbose output (>200 ms at 115200), repeats are probably not dumped correctly!"));
  Serial.println();
}

//+=============================================================================
// The repeating section of the code
//
void loop() {
  if (IrReceiver.decode()) {  // Grab an IR code
    // At 115200 baud, printing takes 200 ms for NEC protocol and 70 ms for NEC repeat
    Serial.println();  // blank line between entries
    Serial.println();  // 2 blank lines between entries
    IrReceiver.printIRResultShort(&Serial);
    // Check if the buffer overflowed
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
      // Serial.println(F("Try to increase the \"RAW_BUFFER_LENGTH\" value of " STR(RAW_BUFFER_LENGTH) " in " __FILE__));
      // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
    } else {
      if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      }
      Serial.println();
      IrReceiver.printIRSendUsage(&Serial);
      Serial.println();
      Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
      IrReceiver.printIRResultRawFormatted(&Serial, false);  // Output the results in RAW format
      Serial.println(F("Raw result in microseconds - with leading gap"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
      Serial.println();                                     // blank line between entries
      Serial.print(F("Result as internal 8bit ticks (50 us) array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, false);  // Output the results as uint8_t source code array of ticks
      Serial.print(F("Result as microseconds array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, true);  // Output the results as uint16_t source code array of micros
      IrReceiver.printIRResultAsCVariables(&Serial);                 // Output address and data as source code variables

      IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);

    }
    IrReceiver.resume();  // Prepare for the next value
  }
  delay(40);
}
