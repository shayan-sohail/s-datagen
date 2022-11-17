#ifndef UTILS_H
#define UTILS_H

#include <QPoint>
#include <QString>

#ifdef __UTILS_VAR
void saveToFile(QString path, float *waveform, unsigned numberOfSamples);
void plotChart(float *data, unsigned numberOfSamples, QPoint Center);
#else
extern void saveToFile(QString path, float *waveform, unsigned numberOfSamples);
extern void plotChart(float *data, unsigned numberOfSamples, QPoint Center);
#endif

#endif // UTILS_H
