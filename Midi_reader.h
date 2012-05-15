#ifndef MIDI_READER_H
#define MIDI_READER_H

#include "portmidi.h"
#include <QTimer>
#include "Midi_parser.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <stdlib.h>


class Midi_reader: public QObject {
  Q_OBJECT
public:
  Midi_reader(PortMidiStream* stream);
  void emulate_key(QString key, bool pressed);

private slots:
  void read();
  void new_event(Note_set set, bool pressed);

private:
  Display* display;
  PortMidiStream* stream;
  QTimer read_timer;
  Midi_parser parser;
  QHash< QString, QString > layout;
  void read_layout();
};

#endif // MIDI_READER_H
