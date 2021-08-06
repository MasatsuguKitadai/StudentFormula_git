#include <Wire.h>
#include <VL53L0X.h>
#include <SD.h>
#include <DS3232RTC.h>

VL53L0X sensor;

// SD card
const int chipSelect = 10;
char filename[20] = "datalog.csv";

// number setting
int i = 0;

void setup()
{
  Serial.begin(9600);
  
  //I2C setup
  Wire.begin();

 // SD setup

  Serial.print("Initializing SD card...");
   pinMode(SS, OUTPUT);
 if (!SD.begin(chipSelect))
 {
    Serial.print("Card failed, or not present");
    // 失敗、何もしない
    while(1);
  }
  Serial.println(F("ok."));

  // setup time log 
  Wire.begin();
  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");
  
  File datafile;
  datafile = SD.open(filename, FILE_WRITE);
  datafile.print("(start) ");
  datafile.print(year());
  datafile.print("/");
  datafile.print(month());
  datafile.print("/");
  datafile.print(day());
  datafile.print(" ");
  datafile.print(hour());
  datafile.print(":");
  datafile.print(minute());
  datafile.print(":");
  datafile.print(second());
  datafile.println();
  datafile.close();

  // VL52LOX setup

  //タイムアウトまでの時間をセット
  sensor.setTimeout(500);
  
  //距離センサ(VL53L0X)の初期化
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  
  sensor.startContinuous();
}

void loop()
{
  // data number
  i = i + 1;
  
  // Serial
  Serial.println();
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(",\t");
  Serial.print(i);
  Serial.print(",\t");
  Serial.print(sensor.readRangeContinuousMillimeters());
  
  // タイムアウトが起きた場合はタイムアウトが起きたことを出力
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  // SDcard
  File datafile;
  datafile = SD.open(filename, FILE_WRITE);
  datafile.print(hour());
  datafile.print(":");
  datafile.print(minute());
  datafile.print(":");
  datafile.print(second());
  datafile.print(",\t");
  datafile.print(i);
  datafile.print(",\t");
  datafile.print(sensor.readRangeContinuousMillimeters());
  datafile.println();
  
  datafile.close();

  delay(100);
}
