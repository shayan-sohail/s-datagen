#include "utils.h"
#include <QWidget>
#include "guicomponents.h"
#define __UTILS_VAR

void saveToFile(QString filename, float* waveform, unsigned numberOfSamples)
{
    if (filename.contains(".bin"))
    {
        std::ofstream file((filename).toStdString().c_str(), std::ios::out | std::ios::binary);
        if (!file) qDebug() << "Cannot open " << filename;

        file.write((char *)waveform, numberOfSamples* sizeof(float));
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

void plotChart(float* waveform, unsigned numberOfSamples, QPoint Center)
{
    QLineSeries *series = new QLineSeries();
    for (unsigned i = 0; i < numberOfSamples; i++)
    {
        series->append(i, waveform[i]);
    }
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
    window->move(Center - window->rect().center());
    window->resize(600, 450);
    window->show();
}
