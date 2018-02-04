void drawLogo()
{
  if (logo_time > 1500)
  {
    if (strcmp(hotspot_, "1") == 0) {
      wifi_status = 5;
      state = 20;
      ui_state = 20;
    }
    else {
      state = 1;
      ui_state = 1;
      //      analogWriteFreq(1000);
      //      analogWrite(BUZZ_PIN, 512);
      //      delay(250);
      //      analogWrite(BUZZ_PIN, 0);
      for (long i = 0; i < 250; i++ )
      {
        digitalWrite(BUZZ_PIN, HIGH);
        delayMicroseconds(500);
        digitalWrite(BUZZ_PIN, LOW);
        delayMicroseconds(500);
      }
    }

  }

}

void wifi_init()
{
  //noTone(BUZZ_PIN);
  wifi_status = 1;

  state = 2;
  ui_state = 2;

}

void menu_1()
{
  analogWrite(IR_PIN, 0);
  digitalWrite(BUZZ_PIN, LOW);
  if (prev_inf == 1 && WiFi.status() == WL_CONNECTED && mqttClient.connected() == true)
  {

    _dripo.setR2set(String(R2set_eeprom)); //save rate to set
    _dripo.setDf(String(df_eeprom));
    _dripo.setTvol(String(tvol_eeprom));
    _dripo.setMed(String(med_eep));
    _dripo.setTimetable(String(timet_eep));
    _dripo.setDcount(dcount_eep);

    //    ui_state = 3;   //testing
    //    state = 9;
    //    MonState = 3;


    ui_state = 16;
    state = 18;

  }

  else {


    switch (get_button())
    {
      case 3: Menu.up();
        break;
      case 4: Menu.dwn();
        break;
      case 1 : switch (Menu.getSelected())
        {
          case 0 :   state = 19;
            ui_state = 19;

            break;

          case 1 :
            state = 6;
            ui_state = 7;

            break;

          case 2 : state = 7;
            ui_state = 6; ///offline
            //               WiFi.disconnect();
            //           WiFi.forceSleepBegin();    //sleep modem in offline mode
            //             delay(1); //
            //            Of_infuseMenu = 0;
            //            state = 12;
            //            ui_state = 18;
            //          _dripo.setTvol("500");
            //            _dripo.setR2set("100");
            //            _dripo.setDf("60");
            //            ui_state = 3;
            //            state = 9;


            break;

            //          case 3 : state = 7;
            //            ui_state = 6;
            //            break;
        }


        break;
    }

  }
}

void reset_menu()
{
  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "No") {

        state = 6;
        ui_state = 7;

      }
      else if (dialogbox.getDia() == "Yes") {
        EEPROM.begin(512);
        // write a 0 to all 512 bytes of the EEPROM
        for (int i = 0; i < 512; i++)
          EEPROM.write(i, 0);
        EEPROM.end();
        delay(250);
        wifi_status = 3;
      }
      break;
    case 3: dialogbox._diaup();
      break;
    case 4: dialogbox._diadwn();
      break;
  }

}

void Server_Err()
{

  switch (get_button())
  {
    case 1: state = prev_state;
      ui_state = prev_ui_state;
      prev_state = 4;
      prev_ui_state = 17;
      break;
  }

}


void M_infuse()
{
  if (DataStatus == "nill")
  {
    ui_state = 4;

  }


}

void M_setup()
{
  switch (get_button())
  {
    case 1: if (Setup.getSelect() == "<<back")
      {
        state = 2;
        ui_state = 2;
      }
      else  if (Setup.getSelect() == "wifi") {
        //        wifi_status = 4;
        //        state = 20;
        //        ui_state = 20;
        EEPROM.begin(512);
        EEPROM.put(270, "1");
        EEPROM.commit();
        EEPROM.end();

        ESP.restart();
      }
      else  if (Setup.getSelect() == "reset") {
        ui_state = 9;
        state = 3;
      }
      else  if (Setup.getSelect() == "system") {
        ui_state = 10;
        state = 13;
      }
      else  if (Setup.getSelect() == "update") {
        ui_state = 5;
        state = 8;
      }
      break;
    case 3: Setup.up();
      break;
    case 4: Setup.dwn();
      break;
  }
}
void M_pwroff()
{

  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "No") {
        state = 2;
        ui_state = 2;

      }
      else if (dialogbox.getDia() == "Yes") {
        //        if (mqttClient.connected()) {
        //  sprintf(will_msg, mqtt_channel_will, id);
        //          mqttClient.publish(will_msg, "offline", true);                // publishes the device status to chennel
        //
        //          mqttClient.disconnect();
        //
        //        }
        switchon = 0;
        // digitalWrite(WAKE_PIN, HIGH);
        u8g2.setPowerSave(1);
        //  system_deep_sleep_set_option(2);
        //  system_deep_sleep(0);
        yield();
        // delay(500);
      }
      break;
    case 3: dialogbox._diaup();
      break;
    case 4: dialogbox._diadwn();
      break;
  }
}

void update_dripo()
{
  if (up_date == true)
  {
    t_httpUpdate_return ret = ESPhttpUpdate.update(mqtt_server, 3000, "/update_dripo", VERSION);
    if (ret == HTTP_UPDATE_FAILED)
    {
      up_status = "failed";

    }
    else if (ret == HTTP_UPDATE_NO_UPDATES)
    {
      up_status = "no update";     


    }


  }


    switch (get_button()) {

      case 1:

        state = 6;
        ui_state = 7;
        up_date = false;
        up_status = "Exit";


        break;
    }
  

  switch (checkLongHold())
  {

    case 5:
      up_date = true;
      up_status = "updating";

      break;


  }
}

void Sho_Rate()
{


  if (_dripo.MonRate() == 1 && MonState == 0)
  {
    PMonState = MonState;
    MonState = 2;
  }


  if (MonState == 0 || (MonState == 3 && (altmsg == NO_ERR || devAck == true))) {


    switch (get_button())

    {
      case 1:  PMonState = MonState;
        MonState = 1;
        break;
    }
  }


  else if (MonState == 2) {


    if (_dripo.MonRate() == 0)

    {
      MonState = PMonState;
    }


    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          MonState = PMonState;
        }
        else if (dialogbox.getDia() == "Yes") {
          EEPROM.begin(512);
          EEPROM.put(200, 1);    //infusion started and it is not completed
          EEPROM.commit();
          EEPROM.end();
          MonState = 3;
          DataStatus = "start";
        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }

  else if (MonState == 1) {

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          MonState = PMonState;
        }
        else if (dialogbox.getDia() == "Yes") {

          EEPROM.begin(512);
          EEPROM.put(200, 0);    //no prev infusions pending
          EEPROM.commit();
          EEPROM.end();
          prev_inf = 0;

          // dpf->~MENU();
          // delete dpf;
          //MENU *dpf= new MENU;
          //  if (PMonState == 3)
          //   {
          DataStatus = "stop";
          //   }
          state = 2;
          ui_state = 2;
          infuseMenu = 1;
          MonState = 0;

        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }
}


void WifiConf()
{
  switch (get_button())
  {
    case 1: if (dialogbox.getDia() == "No") {
        state = 19;
        ui_state = 19;

      }
      else if (dialogbox.getDia() == "Yes") {
        state = 6;
        ui_state = 7;
      }
      break;
    case 3: dialogbox._diaup();
      break;
    case 4: dialogbox._diadwn();
      break;
  }
}

void Sleep()
{
  idle_time = 0;
  u8g2.setPowerSave(1);
  if (sleeper == false)
  {
    u8g2.setPowerSave(0);
    idle_time = 0;
    sleeper = false;
    state = prev_state;
  }
  switch (get_button())
  {
    case 1: u8g2.setPowerSave(0);
      idle_time = 0;
      sleeper = false;
      state = prev_state;
      break;
    case 3: u8g2.setPowerSave(0);
      sleeper = false;
      idle_time = 0;
      state = prev_state;
      break;
    case 4: u8g2.setPowerSave(0);
      sleeper = false;
      idle_time = 0;
      state = prev_state;
      break;
  }

}
void M_Offline()
{

}

void Developer()
{
  switch (get_button())
  {
    case 1:

      state = 6;
      ui_state = 7;
      break;


    case 3:if(scroller<0)
      {
      scroller = scroller + 5;
       }
      break;
    case 4: if(scroller>-40)
       {
      scroller = scroller - 5;
       }
      break;
  }


}


void ServErr()
{
  switch (get_button())
  {
    case 1: //if (dialogbox.getDia() == "Ok") {
        state = 19;
        ui_state = 19;
        break;

      //}

  }
}
void batlowoff()
{
  if (logo_time > 3500)
  {
    //    if (mqttClient.connected()) {
    //        sprintf(will_msg, mqtt_channel_will, id);
    //      mqttClient.publish(will_msg, "offline", true);                // publishes the device status to chennel
    //      mqttClient.disconnect();
    //
    //    }
    switchon = 0;
    u8g2.setPowerSave(1);
    //    system_deep_sleep_set_option(2);
    //    system_deep_sleep(0);
    //    delay(500);
  }
}
void Infbatchk()
{
  switch (get_button())
  {
    case 1: if (dialogbox1.getDia() == "Ok") {
        ui_state = 16;
        state = 18;
      }
      break;
  }
}
void Batchk()
{
  if (logo_time > 3500)
  {
    ui_state = prev_ui_state;
    state = prev_b_state;
  }

}


void SensorCalib()
{

  analogWriteFreq(38000);
  analogWrite(IR_PIN, irAmp);
  if (analogRead(A0) < 512)
  {
    irAmp = irAmp + 10;
  }

  else if (analogRead(A0) > 530)
  {
    irAmp = irAmp - 5;
  }
  else {

    if (prev_inf == 1 )
    {
      ui_state = 3;   //testing
      state = 9;
      MonState = 3;
    }
    else {
      ui_state = 3;
      state = 9;
    }

  }

  switch (get_button())    /// detect button press. exit frm hotspot if button press is detected
  {
    case 1:
      EEPROM.begin(512);
      EEPROM.put(200, 0);    //no prev infusions pending
      EEPROM.commit();
      EEPROM.get(200, prev_inf);
      EEPROM.end();
      state = 2;
      ui_state = 2;

      break;
  }
}

void OnOfselect()
{
  switch (get_button())
  {
    case 1: if (select.getSelect() == "<<back")
      {
        state = 2;
        ui_state = 2;
      }
      else  if (select.getSelect() == "ONLINE") {

        if (WiFi.status() == WL_CONNECTED)
        { if (mqttClient.connected()) {
            DataStatus = "bed";
            //           state = 5;

          }
          else {
            state = 14;
            ui_state = 11;
          }
        }

        else {
          state = 10;
          ui_state = 8;
        }
      }
      else  if (select.getSelect() == "OFFLINE") {
        Of_infuseMenu = 0;
        state = 12;
        ui_state = 18;
      }

      break;
    case 3: select.up();
      break;
    case 4: select.dwn();
      break;
  }
}

void Wifi_Hotspot()

{

  switch (get_button())    /// detect button press. exit frm hotspot if button press is detected
  {
    case 1:  EEPROM.begin(512);
      EEPROM.put(270, "0");
      EEPROM.commit();
      EEPROM.end();

      ESP.restart();
      break;
  }
}

