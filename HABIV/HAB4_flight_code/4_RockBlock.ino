
/**
   This function initializes the RockBLOCK and tests its signal
   quality. It assumes that `Serial` has been initialized already.

   Will return false if initialization of the RockBLOCK was not successful.
*/
bool startRockBlock() {
  int signalQuality = -1;
  int err;

  IridiumSerial.begin(19200);

  setMode(3);

  Serial.println("Starting modem...");
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    Serial.print("Begin failed: error =========================================================== ");
    Serial.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      Serial.println("No modem detected: check wiring=============================================.");
    return false;
  }
  else {
    Serial.println("Modem started successfully=======================================================================================");
  }


  err = modem.getSignalQuality(signalQuality);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return false;
  }
  Serial.print("On a scale of 0 to 5, signal quality is currently ");
  Serial.print(signalQuality);
  Serial.println(".");

  return true;
}


/**
   Sends data through the RockBLOCK to the location we specified.
   Usually, only 50 bytes of data should be send in `data` so that
   only one credit is used during transmission.

   When the function is called, the main loop will stall until
   the RockBLOCK is able to send all the data. During this time,
   the function `ISBDCallBack` will be called instead of loop.
*/
void rockBlockSendData(const char* data) {

  int quality1 = -1;
  int quality2 = -1;
  int quality3 = -1;

  Serial.println("Determining antenna with best signal quality");
  setMode(1);
  delay(1000);
  modem.getSignalQuality(quality1);
  setMode(2);
  delay(1000);
  modem.getSignalQuality(quality2);
  setMode(3);
  delay(1000);
  modem.getSignalQuality(quality3);

  int bestQuality;

  if (quality1 > quality2 && quality1 > quality3) {
    Serial.print("1st antenna is best, with signal quality "); Serial.println(quality1); setMode(1); bestQuality = quality1;
  } else if (quality2 > quality1 && quality2 > quality3) {
    Serial.print("2nd antenna is best, with signal quality "); Serial.println(quality2); setMode(2); bestQuality = quality2;
  } else {
    Serial.print("Third antenna is best, with signal quality "); Serial.println(quality3); setMode(3); bestQuality = quality3;
  }

  if (bestQuality == 0) {
    Serial.println("No antenna can transmit... skipping.");
    return;
  }

  Serial.println("Attmepting to send message");
  int err = modem.sendSBDText(data);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT) {
      Serial.println("Try again with a better view of the sky.");
    }
  }
  else
  {
    Serial.print("Message <");
    Serial.print(data);
    Serial.println("> transmitted");
  }
}
