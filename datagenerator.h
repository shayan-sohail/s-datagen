#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QMainWindow>
#include <QObject>
#include "guicomponents.h"

namespace Ui {
class sdr;
}

class DataGenerator : public QMainWindow
{
    Q_OBJECT
public:
    explicit DataGenerator(QWidget *parent = 0);
    void setComboBox(QComboBox* ComboBox);
};

#endif // DATAGENERATOR_H
