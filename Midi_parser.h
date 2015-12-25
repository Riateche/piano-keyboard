#ifndef MIDI_PARSER_H
#define MIDI_PARSER_H

#include "Note.h"
#include <QSet>
#include <QTime>
#include <QTimer>

class Midi_parser: public QObject {
  Q_OBJECT
public:
  Midi_parser();
  void add(int note, int volume);
  void add_cc(int controller, int value);
  //bool has_note();
  //QPair<Note_set, bool> get();

signals:
  void key_event(Note_set set, bool pressed);

private slots:
  void check();

private:
  Note_set new_event;
  //QList< QPair<Note_set, bool> > new_events;
  QList<Note_set> current_sets;
  QTime last_time;
  static const int commit_delay = 50;

  QTimer check_timer;
};

#endif // MIDI_PARSER_H
