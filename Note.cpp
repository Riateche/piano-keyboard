#include "Note.h"
#include <QObject>
#include <QStringList>


Note::Note(int midi_number) {
  int n = midi_number - 21;
  octave = n / 12;
  tone = (n - octave * 12);
}

QString Note::to_string() const {
  return QObject::tr("%1%2").arg(octave).arg(
    tone == 0?  "A":
    tone == 1?  "A#":
    tone == 2?  "B":
    tone == 3?  "C":
    tone == 4?  "C#":
    tone == 5?  "D":
    tone == 6?  "D#":
    tone == 7?  "E":
    tone == 8?  "F":
    tone == 9?  "F#":
    tone == 10? "G":
    tone == 11? "G#": "??"
  );
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
