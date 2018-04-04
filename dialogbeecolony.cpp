#include "dialogbeecolony.h"
#include "ui_dialogbeecolony.h"

DialogBeeColony::DialogBeeColony(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBeeColony)
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

DialogBeeColony::~DialogBeeColony()
{
    delete ui;
}
