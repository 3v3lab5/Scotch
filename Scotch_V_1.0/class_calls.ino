boolean call_err_handler(boolean flag){
  if(flag){
    sleeper= _errAlert.display_err(_dripo.getTimetable(), altmsg, devAck, staAck, id, _dripo.getMed(), _dripo.getRateMl(), _dripo.getvolInf(), _dripo.getRtime(), _dripo.getTvol(), prev_inf_save, stateOfCharge);
    yield();
    }
    return false;

}

