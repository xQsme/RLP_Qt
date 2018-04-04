#include "dialogantcolony.h"
#include "ui_dialogantcolony.h"

DialogAntColony::DialogAntColony(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAntColony)
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

DialogAntColony::~DialogAntColony()
{
    delete ui;
}
