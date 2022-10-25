#ifndef HOME_H
#define HOME_H

#include <QObject>
#include <QWidget>
#include "guicomponents.h"
#include "puresinusoid.h"

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void setComboBox();

    QLabel *l_InputType;
    QComboBox *cb_InputType;
    QHBoxLayout *hlo_InputType;
    QPushButton *pb_Select;
    QPushButton *pb_Exit;
    QHBoxLayout *hlo_InputOptionButtons;

    QVBoxLayout *vlo_MainScreen;

signals:

public slots:
    void on_Select_Clicked();
    void on_Exit_Clicked();
};

#endif // HOME_H
