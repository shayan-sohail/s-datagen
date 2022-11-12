#ifndef HOME_H
#define HOME_H

#include <QObject>
#include <QWidget>
#include "guicomponents.h"

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
    void onSelect_Clicked();
    void onExit_Clicked();
};

#endif // HOME_H
