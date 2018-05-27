#include "genetictestdialog.h"
#include "ui_genetictestdialog.h"

GeneticTestDialog::GeneticTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneticTestDialog)
{
    ui->setupUi(this);
}

GeneticTestDialog::~GeneticTestDialog()
{
    delete ui;
}

void GeneticTestDialog::on_pushButtonAccept_clicked()
{
    this->accept();
}

void GeneticTestDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

int GeneticTestDialog::getStartElitism()
{
    return ui->lineEditStartElitism->text().toInt();
}

int GeneticTestDialog::getEndElitism()
{
    return ui->lineEditEndElitism->text().toInt();
}

int GeneticTestDialog::getIncrementElitism()
{
    return ui->lineEditIncrementElitism->text().toInt();
}

int GeneticTestDialog::getStartMutation()
{
    return ui->lineEditStartMutation->text().toInt();
}

int GeneticTestDialog::getEndMutation()
{
    return ui->lineEditEndMutation->text().toInt();
}

int GeneticTestDialog::getIncrementMutation()
{
    return ui->lineEditIncrementMutation->text().toInt();
}
