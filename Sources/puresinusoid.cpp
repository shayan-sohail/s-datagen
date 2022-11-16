#include "Headers/puresinusoid.h"

PureSinusoid::PureSinusoid(QWidget *parent) : QWidget(parent)
{

    /*Initializing Member Variables*/
    l_FS = new QLabel("Sampling Frequency");
    l_F = new QLabel("Waveform Frequency");
    l_A = new QLabel("Amplitude");
    l_Dur = new QLabel("Duration");

    sb_FS = new QSpinBox();
    sb_F = new QSpinBox();
    sb_A = new QDoubleSpinBox();
    sb_Dur = new QDoubleSpinBox();

    hlo_FS = new QHBoxLayout;
    hlo_F = new QHBoxLayout;
    hlo_A= new QHBoxLayout;
    hlo_Dur= new QHBoxLayout;
    hlo_Buttons = new QHBoxLayout;
    hlo_Chbs = new QHBoxLayout;

    chb_SaveToFile = new QCheckBox("Save");
    chb_Plot = new QCheckBox("Plot");

    pb_Generate = new QPushButton("Generate");
    pb_Back = new QPushButton("Back");

    vlo_MainScreen = new QVBoxLayout;

    this->setFixedSize(450, 200);
    this->move(screen()->geometry().center() - frameGeometry().center());
//    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    this->setWindowTitle("Pure Sinusoid");

    /*Setting Minimum Values for Labels*/
    l_FS->setMinimumSize(200,0);
    l_F->setMinimumSize(200,0);
    l_A->setMinimumSize(200,0);
    l_Dur->setMinimumSize(200,0);
    l_FS->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    l_F->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    l_A->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    l_Dur->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    /*Setting Sizes of Spin Boxes*/
    sb_FS->setMinimumSize(200,0);
    sb_F->setMinimumSize(200,0);
    sb_A->setMinimumSize(200,0);
    sb_Dur->setMinimumSize(200,0);
    sb_FS->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sb_F->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sb_A->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sb_Dur->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    /*Setting Values for Spin Boxes*/
    sb_FS->setMaximum(1300);
    sb_FS->setValue(1300);
    sb_FS->setSuffix(" MHz");
    sb_FS->setAlignment(Qt::AlignHCenter);

    sb_F->setMaximum(1300);
    sb_F->setValue(420);
    sb_F->setSuffix(" MHz");
    sb_F->setAlignment(Qt::AlignHCenter);

    sb_A->setValue(1.0);
    sb_A->setSuffix(" V");
    sb_A->setAlignment(Qt::AlignHCenter);

    sb_Dur->setValue(1.0);
    sb_Dur->setSuffix(" us");
    sb_Dur->setAlignment(Qt::AlignHCenter);

    /*Setting Properties of Checkboxes*/
    chb_SaveToFile->setChecked(true);
    chb_SaveToFile->setDisabled(false);
    /*Adding Widgets to their respective Layouts*/
    hlo_FS->addWidget(l_FS);
    hlo_FS->addWidget(sb_FS);
    hlo_F->addWidget(l_F);
    hlo_F->addWidget(sb_F);
    hlo_A->addWidget(l_A);
    hlo_A->addWidget(sb_A);
    hlo_Dur->addWidget(l_Dur);
    hlo_Dur->addWidget(sb_Dur);
    hlo_Buttons->addWidget(pb_Generate);
    hlo_Buttons->addWidget(pb_Back);
    hlo_Chbs->addWidget(chb_SaveToFile);
    hlo_Chbs->addWidget(chb_Plot);

    /*Adding Layout to Main Layout*/
    vlo_MainScreen->addLayout(hlo_FS);
    vlo_MainScreen->addLayout(hlo_F);
    vlo_MainScreen->addLayout(hlo_A);
    vlo_MainScreen->addLayout(hlo_Dur);
    vlo_MainScreen->addLayout(hlo_Chbs);
    vlo_MainScreen->addLayout(hlo_Buttons);

    this->setLayout(vlo_MainScreen);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(pb_Generate, SIGNAL(pressed()), this, SLOT(on_Generate_Clicked()));
    connect(pb_Back, SIGNAL(pressed()), this, SLOT(on_Back_Clicked()));


}

void PureSinusoid::on_Generate_Clicked()
{
    float FS = float(this->sb_FS->value()*1000000);
    float F = float(this->sb_F->value()*1000000);
    float Amplitude = this->sb_A->value();
    float Duration = this->sb_Dur->value() * 0.000001;

    unsigned numberOfSamples = Duration*FS;

    std::vector<float> waveform(numberOfSamples);
    series = new QLineSeries();
    QFileDialog SaveAsDialog(this);
    SaveAsDialog.setFileMode(QFileDialog::Directory);
    SaveAsDialog.setNameFilter(tr("Formats (*.csv *.bin)"));
    SaveAsDialog.setFixedSize(500, 500);

    for (unsigned i = 0; i < numberOfSamples; i++)
    {
        waveform[i] = Amplitude*sin(2*PI*F*(i/FS));
        series->append(i, waveform[i]);
    }

    for (unsigned i = 0; i < numberOfSamples; i++)
    {
        waveform[i] = Amplitude*sin(2*PI*F*(i/FS));
        series->append(i, waveform[i]);
    }

    if (this->chb_SaveToFile->isChecked())
    {
        QString filename= SaveAsDialog.getSaveFileName(this,"Save File", QDir::homePath(),tr("Binary file (*.bin);;CSV (*.csv)"));
        if (filename.contains(".bin"))
        {
            std::ofstream file((filename).toStdString().c_str(), std::ios::out | std::ios::binary);
            if (!file) qDebug() << "Cannot open " << filename;

            file.write((char *)waveform.data(), numberOfSamples* sizeof(float));
            file.close();
        }
        else if (filename.contains(".csv"))
        {
            std::ofstream file((filename).toStdString().c_str(), std::ios::out);
            if (!file) qDebug() << "Cannot open " << filename;

            for (unsigned i = 0; i < numberOfSamples; i++)
            {
                std::string temp = std::to_string(waveform[i]) + "\n";
                file.write(temp.data(), temp.length());
            }
            file.close();
        }
        else
        {
            if (filename.isEmpty())
            {
                std::cerr << "Filename is Empty\n";
            }
            else
            {
                qDebug() <<"Invalid File name\n";
            }
        }
    }

    if (this->chb_Plot->isChecked())
    {
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->setTitle("Pure Sinusoid");

        QValueAxis *axisX = new QValueAxis;
        QValueAxis *axisY = new QValueAxis;

        axisX->setTitleText("Samples");
        axisY->setTitleText("Amplitude");

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);

        series->attachAxis(axisX);
        series->attachAxis(axisY);


        QChartView *chartView = new QChartView(chart);
        chartView->setRubberBand(QChartView::HorizontalRubberBand);
        chartView->setRenderHint(QPainter::Antialiasing);

        QMainWindow *window = new QMainWindow;
        window->setCentralWidget(chartView);
        window->move(screen()->geometry().center() - window->rect().center());
        window->resize(600, 450);
        window->show();
    }
}

void PureSinusoid::on_Back_Clicked()
{
    emit Want2Close();
    this->close();
}
PureSinusoid::~PureSinusoid()
{
}

void PureSinusoid::closeEvent(QCloseEvent *bar) /*Overriding closeEvent*/
{
    emit Want2Close();
    bar->accept();
}
