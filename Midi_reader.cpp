#include "Midi_reader.h"
#include <QStringList>
#include <QFile>
#include <QSettings>

Midi_reader::Midi_reader(PortMidiStream *p_stream):
  stream(p_stream),
  display(XOpenDisplay(0))
{
  read_layout();
  connect(&parser, SIGNAL(key_event(Note_set,bool)), this, SLOT(new_event(Note_set,bool)));
  connect(&read_timer, SIGNAL(timeout()), this, SLOT(read()));
  read_timer.start(10);
}

void Midi_reader::emulate_key(QString key, bool pressed) {
  KeySym sym = XStringToKeysym(key.toAscii());
  if (sym == NoSymbol) {
    qWarning() << "Failed to emulate key: " << key;
    return;
  }
  XTestFakeKeyEvent(display, XKeysymToKeycode(display, sym), pressed, 0);
  XFlush(display);
}

void Midi_reader::read() {
  PmEvent event;
  int c = Pm_Read(stream, &event, 1);
  if (c != 0) {
    int status = Pm_MessageStatus(event.message) & 0xf0; // Strip channel

    if (status == 0x90) { // Note On
      parser.add(
            Pm_MessageData1 (event.message),
            Pm_MessageData2 (event.message)
      );
    } else if (status == 0xB0){ // Control Change
      parser.add_cc(
            Pm_MessageData1 (event.message),
            Pm_MessageData2 (event.message)
      );
    }
  }
}

void Midi_reader::new_event(Note_set set, bool pressed) {
  QString s = set.to_string();
  qDebug() << s;
  if (layout.contains(s)) {
    qDebug() << "Matched. Sending key " << layout[s];
    emulate_key(layout[s], pressed);
  }
}

void Midi_reader::read_layout() {
  QSettings s("layout.ini", QSettings::IniFormat);
  foreach(QString key, s.allKeys()) {
    QString note = s.value(key).toString();
    if (note.isEmpty()) {
      qWarning() << "Note missing for key: " << key;
    } else {
      if (layout.contains(note)) {
        qWarning() << "Layout duplicate: " << note;
      } else {
        layout.insert(note, key);
      }
    }
  }
}
