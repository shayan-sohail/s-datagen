#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "qcombobox.h"
#include <QMainWindow>
#include <QObject>

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
