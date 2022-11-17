#ifndef PURESINUSOID_H
#define PURESINUSOID_H

#include <QObject>
#include <QWidget>
#include "guicomponents.h"

class PureSinusoid : public QWidget
{
    Q_OBJECT
public:
    explicit PureSinusoid(QWidget *parent = nullptr);
    ~PureSinusoid();
    QLabel *l_FS;
    QSpinBox *sb_FS;

    QLabel *l_F;
    QSpinBox *sb_F;

    QLabel *l_A;
    QDoubleSpinBox *sb_A;

    QLabel *l_Dur;
    QDoubleSpinBox *sb_Dur;

    QCheckBox* chb_SaveToFile;
    QCheckBox* chb_Plot;

    QHBoxLayout *hlo_FS;
    QHBoxLayout *hlo_F;
    QHBoxLayout *hlo_A;
    QHBoxLayout *hlo_Dur;
    QHBoxLayout *hlo_Chbs;

    QPushButton *pb_Generate;
    QPushButton *pb_Back;
    QHBoxLayout *hlo_Buttons;

    QVBoxLayout *vlo_MainScreen;

private:
    void closeEvent(QCloseEvent *bar);
signals:
    void Want2Close();

public slots:
    void on_Generate_Clicked();
    void on_Back_Clicked();

};

#endif // PURESINUSOID_H
