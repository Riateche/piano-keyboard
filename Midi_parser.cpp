#include "Midi_parser.h"
#include <QDebug>
#include "Note.h"
#include <QStringList>
#include <QTime>

Midi_parser::Midi_parser() {
  last_time = QTime::currentTime();
  connect(&check_timer, SIGNAL(timeout()), this, SLOT(check()));
  check_timer.start(commit_delay / 3);

}

void Midi_parser::add(int note, int volume) {
  check();
  Note n(note);
  if (volume > 0) {
    new_event.insert(n);
    last_time = QTime::currentTime();
  } else {
    if (!new_event.isEmpty()) {
      emit key_event(new_event, true);
      emit key_event(new_event, false);
      new_event.clear();
    }
    foreach(Note_set set, current_sets) {
      if (set.contains(n)) {
        current_sets.removeAll(set);
        emit key_event(set, false);
      }
    }
  }
  QStringList d;
  //foreach(const Note& n, new_event) d << n.to_string();
  //qDebug() << d.join(" ");
}

void Midi_parser::add_cc(int controller, int value) {
  Note n(controller, value);

  Note_set set;
  set.insert(n);
  emit key_event(set, true);
  emit key_event(set, false);
}

void Midi_parser::check() {
  if (!new_event.isEmpty() &&
      QTime::currentTime().msec() - last_time.msec() > commit_delay) {
    emit key_event(new_event, true);
    current_sets.append(new_event);
    new_event.clear();
  }
}
