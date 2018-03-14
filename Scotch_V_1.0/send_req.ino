String send_req(String Data)
{
  const char* DRIPO_NAME = "DRIPO-%d";
  sprintf(id, DRIPO_NAME, ESP.getChipId());
  if (Data == "nill")
  {
    return "nill";
  }

  else if (!mqttClient.connected())
  {
    return "nill";

  }
  else if (Data == "df")
  {
    char e_data[50];
    String medi = _dripo.getMed();
    const char* chr = medi.c_str();
    sprintf(e_data, "%s", chr);
    sprintf(pat_channel, mqtt_channel_req, id);
    mqttClient.publish(pat_channel, chr);
    yield();
    return "nill";
  }

  else if (Data == "bed")
  {
    //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_bedreq, id);
    mqttClient.publish(pat_channel, "bed");
    yield();
    return "nill";
  }
  else if (Data == "med")
  {
    String medi = _dripo.getBed();
    const char* chr = medi.c_str();
    //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_medreq, id);
    mqttClient.publish(pat_channel, chr);
    yield();
    return "nill";
  }
  else if (Data == "rate")
  {
    //String medi=_dripo.getBed()+"-"+_dripo.getMed();
    String medi = _dripo.getMed();
    const char* chr = medi.c_str();
    //   mqttClient.connect(id);
    sprintf(pat_channel, mqtt_channel_ratereq, id);
    mqttClient.publish(pat_channel, chr);
    yield();
    return "nill";
  }

  else if (Data == "start")
  {

    char e_data[80];

    int SRate = _dripo.getRateMl();
    int SIvol = _dripo.getvolInf();
    int SRtime = _dripo.getRtime();
    int Tvol = _dripo.getTvol();
    //  int S_df = _dripo.getDf();
    //  long _DropCount = _dripo.getDcount();                          //get drop count

    //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
    String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + Data;
    const char* chr = medi.c_str();
    //   mqttClient.connect(id);
    sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);
    sprintf(pat_channel, mqtt_channel_mon, id);

    mqttClient.publish(pat_channel, e_data);
    yield();
    return "nill";
  }


  else if (Data == "stop")
  {
    char e_data[80];

    int SRate = _dripo.getRateMl();
    int SIvol = _dripo.getvolInf();
    int SRtime = _dripo.getRtime();
    int Tvol = _dripo.getTvol();
    // int S_df = _dripo.getDf();
    // long _DropCount = _dripo.getDcount();                          //get drop count


    //  String medi=Data+"-"+_dripo.getBed()+"-"+_dripo.getMed();
    String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + Data;
    const char* chr = medi.c_str();
    //   mqttClient.connect(id);
    sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);
    sprintf(pat_channel, mqtt_channel_mon, id);
    mqttClient.publish(pat_channel, e_data);
    yield();
    return "nill";
  }

  else if (Data == "log")
  {
    char e_data[80];                   // all data will merged to this
    int SRate = _dripo.getRateMl();    //get rate in ml
    int SIvol = _dripo.getvolInf();    // get infused volume
    int Tvol = _dripo.getTvol();       //get total volume
    int SRtime = _dripo.getRtime();    //get remaining time
    String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + "infusing"; //get medicine id,timetable id and status and merged
    const char* chr = medi.c_str();                                          // converted to const char to send via mqtt
    sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);     // all data is merged
    sprintf(rate_channel, mqtt_channel_mon, id);                           // merge device id with the rate channel to publish data
    mqttClient.publish(rate_channel, e_data);                        // publish data to rate channel and data is retained true so that if a new client is
    yield() ;

    return "nill";
  }

  else
  {
        return "nill";
  }


}

