#ifndef SALLECONTROL_H
#define SALLECONTROL_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/salle.h"
#include "definition.h"

bool addSalleCSV(int numero, cours cours);

#endif // SALLECONTROL_H
