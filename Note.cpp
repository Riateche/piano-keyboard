#include "Note.h"
#include <QObject>
#include <QStringList>


Note::Note(int midi_number) {
  int n = midi_number - 21;
  octave = n / 12;
  tone = (n - octave * 12);
  cc_message = false;
}

Note::Note(int controller, int value) :
  controller(controller),
  value(value)
{
  cc_message = true;
}

QString Note::to_string() const {
  if (!cc_message) {
    const char* tones[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    return QObject::tr("%1%2").arg(octave).arg(tone < 12? tones[tone]: "??");
  } else {
    return QObject::tr("CC%1/%2").arg(controller).arg(value);
  }
}

QDebug operator<<(QDebug debug, const Note& note) {
  debug.nospace() << "Note(" << note.to_string() << ")";
  return debug.space();
}

bool operator==(const Note& n1, const Note& n2) {
  return n1.tone == n2.tone && n1.octave == n2.octave;
}

uint qHash(const Note& note) {
  return qHash(qMakePair(note.tone, note.octave));
}

QString Note_set::to_string() {
  QStringList d;
  foreach(const Note& n, *this) d << n.to_string();
  qSort(d);
  return d.join("+");
}
