boolean write_eprom(boolean flag){
  if(flag == true){
     EEPROM.begin(512);
     EEPROM.put(180, _dripo.getDcount());
     EEPROM.commit();
     EEPROM.end();
     yield();
  }
  return false;
}
     
    
