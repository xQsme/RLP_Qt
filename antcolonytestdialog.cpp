#include "antcolonytestdialog.h"
#include "ui_antcolonytestdialog.h"

AntColonyTestDialog::AntColonyTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AntColonyTestDialog)
{
    ui->setupUi(this);
}

AntColonyTestDialog::~AntColonyTestDialog()
{
    delete ui;
}

void AntColonyTestDialog::on_pushButtonAccept_clicked()
{
    this->accept();
}

void AntColonyTestDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

int AntColonyTestDialog::getStartQprob()
{
    return ui->lineEditStartQprob->text().toInt();
}

int AntColonyTestDialog::getEndQprob()
{
    return ui->lineEditEndQprob->text().toInt();
}

int AntColonyTestDialog::getIncrementQprob()
{
    return ui->lineEditIncrementQprob->text().toInt();
}

int AntColonyTestDialog::getStartQ()
{
    return ui->lineEditStartQ->text().toInt();
}

int AntColonyTestDialog::getEndQ()
{
    return ui->lineEditEndQ->text().toInt();
}

int AntColonyTestDialog::getIncrementQ()
{
    return ui->lineEditIncrementQ->text().toInt();
}

int AntColonyTestDialog::getStartMods()
{
    return ui->lineEditStartMods->text().toInt();
}

int AntColonyTestDialog::getEndMods()
{
    return ui->lineEditEndMods->text().toInt();
}

int AntColonyTestDialog::getIncrementMods()
{
    return ui->lineEditIncrementMods->text().toInt();
}

int AntColonyTestDialog::getStartEvaporation()
{
    return ui->lineEditStartEvaporation->text().toInt();
}

int AntColonyTestDialog::getEndEvaporation()
{
    return ui->lineEditEndEvaporation->text().toInt();
}

int AntColonyTestDialog::getIncrementEvaporation()
{
    return ui->lineEditIncrementEvaporation->text().toInt();
}

int AntColonyTestDialog::getStartInfluence()
{
    return ui->lineEditStartInfluence->text().toInt();
}

int AntColonyTestDialog::getEndInfluence()
{
    return ui->lineEditEndInfluence->text().toInt();
}

int AntColonyTestDialog::getIncrementInfluence()
{
    return ui->lineEditIncrementInfluence->text().toInt();
}
