#include "Headers/home.h"
#include "Headers/puresinusoid.h"


void Home:: setComboBox()
{
    cb_InputType->setEditable(true);
    cb_InputType->lineEdit()->setReadOnly(true);
    cb_InputType->lineEdit()->setAlignment(Qt::AlignCenter);
    QStringList InputTypes = (QStringList() << "Pure Sinusoid" << "Pulsed Sinusoid");
    cb_InputType->addItems(InputTypes);
    for (int i = 0 ; i < cb_InputType->count() ; ++i)
    {
        cb_InputType->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    };
}

Home::Home(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(400, 150);
    this->move(screen()->geometry().center() - frameGeometry().center());
    this->setWindowTitle("Synthetic Data Generator");

    l_InputType = new QLabel("Input Type");
    cb_InputType = new QComboBox();
    hlo_InputType = new QHBoxLayout;

    pb_Select = new QPushButton("Select");
    pb_Exit = new QPushButton("Exit");
    hlo_InputOptionButtons = new QHBoxLayout;

    vlo_MainScreen = new QVBoxLayout;

    l_InputType->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setComboBox();
    hlo_InputType->addWidget(l_InputType);
    hlo_InputType->addWidget(cb_InputType);

    hlo_InputOptionButtons->addWidget(pb_Select);
    hlo_InputOptionButtons->addWidget(pb_Exit);

    vlo_MainScreen->addLayout(hlo_InputType);
    vlo_MainScreen->addLayout(hlo_InputOptionButtons);

    this->setLayout(vlo_MainScreen);

    connect(pb_Select, SIGNAL(pressed()), this, SLOT(onSelect_Clicked()));
    connect(pb_Exit, SIGNAL(pressed()), this, SLOT(onExit_Clicked()));

}

void Home::onSelect_Clicked()
{
    if (this->cb_InputType->currentIndex() == 0)
    {
        PureSinusoid *pureSin = new PureSinusoid();
        connect(pureSin,&PureSinusoid::Want2Close,this,&QWidget::show);
        connect(pureSin,&PureSinusoid::destroyed,this,&QWidget::show);
        pureSin->show();
        this->hide();
    }
}
void Home::onExit_Clicked()
{
    this->close();
}
Home::~Home()
{
}
