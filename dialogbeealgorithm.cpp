#include "dialogbeealgorithm.h"
#include "ui_dialogbeealgorithm.h"

DialogBeeAlgorithm::DialogBeeAlgorithm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBeeAlgorithm)
{
    ui->setupUi(this);

    chart = new QChart();
    series = new QLineSeries();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 0, 0);
}

DialogBeeAlgorithm::~DialogBeeAlgorithm()
{
    delete ui;
}
