#include <QtCore/QCoreApplication>
#include "portmidi.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include "Midi_reader.h"

using namespace std;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qDebug() << "started!";
  int good_id = -1;
  int count = Pm_CountDevices();
  for(int i = 0; i < count; i++) {
    const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
    if ( info->input == 1 && QString(info->name).contains("YAMAHA")) {
      good_id = i;
    }
    qDebug() << i << (good_id == i? "(*)":"") << ": " << info->name <<  " input: " << info->input << " output: " << info->output;
  }
  if (good_id < 0) {
    qDebug() << "Device not found";
    return 1;
  }
  PortMidiStream* s = 0;
  PmError e = Pm_OpenInput(&s, good_id, 0, 100, 0, 0);
  if (e != pmNoError) {
    qDebug() << "Can't open input, error: " << e << endl;
    return 2;
  }
  qDebug() << "Open successful: " << s << endl;
  Midi_reader mini_reader(s);
  return a.exec();
}
