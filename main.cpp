#include <QtCore/QCoreApplication>
#include <QStringList>
#include "portmidi.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include "Midi_reader.h"

using namespace std;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QStringList args = a.arguments();
  QString deviceName;
  if (args.size() == 2) {
    if ((args[1] == "-h") || (args[1] == "--help")) {
      qDebug("Usage: %s [device_name]", qPrintable(args[0]));
      return 0;
    }
    deviceName = args[1];
  }

  qDebug() << "started!";
  int good_id = -1;
  if (!deviceName.isNull()) {
    int count = Pm_CountDevices();
    for(int i = 0; i < count; i++) {
      const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
      if ( info->input == 1 && QString(info->name) == deviceName) {
        good_id = i;
      }
      qDebug() << i << (good_id == i? "(*)":"") << ": " << info->name <<  " input: " << info->input << " output: " << info->output;
    }
  }
  if (good_id < 0) {
    if (!deviceName.isNull()) {
      qDebug() << "Device not found";
      return 1;
    } else {
      good_id = Pm_GetDefaultInputDeviceID();
    }
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
