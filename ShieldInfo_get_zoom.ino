#include <BMDSDIControl.h>

/**
 *  Blackmagic Design 3G-SDI Shield Example Sketch
 *    Shield Info Example
 *
 *  This sketch extracts out the various version identifiers from the
 *  Blackmagic Design 3G-SDI Shield control library and hardware.
 *
 *  The version information of the shield and library should be printed to
 *  the serial port when run.
 *
 *  Setup Steps:
 *    1) Connect the Blackmagic Design 3G-SDI Shield to an Arduino board.
 *    2) Build and run the example sketch.
 *    3) Observe the information printed on the Serial Monitor.
 */

const int                shieldAddress = 0x6E;
BMD_SDICameraControl_I2C sdiCameraControl(shieldAddress);
BMD_SDITallyControl_I2C sdiTallyControl(shieldAddress);
int ZoomValue = 14; //14

void setup() {
  Serial.begin(9600);

  Serial.println("Blackmagic Design SDI Control Shield");

  Serial.print("Getting shield version info...");
  sdiCameraControl.begin();
  sdiTallyControl.begin();

// Turn on camera control overrides in the shield 
sdiCameraControl.setOverride(true);

// Turn on tally overrides in the shield
sdiTallyControl.setOverride(true);

pinMode(13, OUTPUT);                                     // initialize digital pin 13 as an output


  
  Serial.println("done.\n");

  // Show BMD SDI Control Shield for Arduino library version
  BMD_Version libraryVersion = sdiCameraControl.getLibraryVersion();
  Serial.print("Library Version:\t");
  Serial.print(libraryVersion.Major);
  Serial.print('.');
  Serial.println(libraryVersion.Minor);

  // Show shield firmware version
  BMD_Version firmwareVersion = sdiCameraControl.getFirmwareVersion();
  Serial.print("Firmware Version:\t");
  Serial.print(firmwareVersion.Major);
  Serial.print('.');
  Serial.println(firmwareVersion.Minor);

  // Show shield protocol version
  BMD_Version protocolVersion = sdiCameraControl.getProtocolVersion();
  Serial.print("Protocol Version:\t");
  Serial.print(protocolVersion.Major);
  Serial.print('.');
  Serial.println(protocolVersion.Minor);
  delay(5000);
  Serial.print("Waited long enough");
  
}

void loop() {

  sdiTallyControl.setCameraTally(                          // turn tally ON
    1,                                                     // Camera Number
    true,                                                  // Program Tally
    false                                                  // Preview Tally
  );

    Serial.print("Start");
    Serial.print('.');


  delay(500);                                             // leave it ON for 1 second

  sdiTallyControl.setCameraTally(                          // turn tally ON
    1,                                                     // Camera Number
    false,                                                  // Program Tally
    false                                                  // Preview Tally
  );



sdiCameraControl.writeCommandInt16(
1, // Destination: Camera 1
0, // Category: Lens
7, // Param: Focus
0, // Operation: Assign
ZoomValue // Value
);
Serial.println(ZoomValue);
   sdiTallyControl.setCameraTally(                          // turn tally ON
    1,                                                     // Camera Number
    true,                                                  // Program Tally
    false                                                  // Preview Tally
  );


  delay(1000);                                             // leave it ON for 1 second

  sdiTallyControl.setCameraTally(                          // turn tally ON
    1,                                                     // Camera Number
    false,                                                  // Program Tally
    false                                                  // Preview Tally
  );

   delay(500);

if (ZoomValue <= 26) 
    ZoomValue++;

    else
    {
    ZoomValue = 25; //14
    
    sdiCameraControl.writeCommandInt16(
    1, // Destination: Camera 1
    0, // Category: Lens
    7, // Param: Focus
    0, // Operation: Assign
    ZoomValue // Value
    );
    delay(5000);
    
    }
}
