#include "beecolonytestdialog.h"
#include "ui_beecolonytestdialog.h"

BeeColonyTestDialog::BeeColonyTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BeeColonyTestDialog)
{
    ui->setupUi(this);
}

BeeColonyTestDialog::~BeeColonyTestDialog()
{
    delete ui;
}

void BeeColonyTestDialog::on_pushButtonAccept_clicked()
{
    this->accept();
}

void BeeColonyTestDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

int BeeColonyTestDialog::getSelectStart()
{
    return ui->lineEditSelectStart->text().toInt();
}

int BeeColonyTestDialog::getSelectEnd()
{
    return ui->lineEditSelectEnd->text().toInt();
}

int BeeColonyTestDialog::getSelectIncrement()
{
    return ui->lineEditSelectIncrement->text().toInt();
}

int BeeColonyTestDialog::getBestStart()
{
    return ui->lineEditBestStart->text().toInt();
}

int BeeColonyTestDialog::getBestEnd()
{
    return ui->lineEditBestEnd->text().toInt();
}

int BeeColonyTestDialog::getBestIncrement()
{
    return ui->lineEditBestIncrement->text().toInt();
}

int BeeColonyTestDialog::getChangeStart()
{
    return ui->lineEditChangeStart->text().toInt();
}

int BeeColonyTestDialog::getChangeEnd()
{
    return ui->lineEditChangeEnd->text().toInt();
}

int BeeColonyTestDialog::getChangeIncrement()
{
    return ui->lineEditChangeIncrement->text().toInt();
}
