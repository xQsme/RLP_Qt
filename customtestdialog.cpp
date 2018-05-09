#include "customtestdialog.h"
#include "ui_customtestdialog.h"

CustomTestDialog::CustomTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTestDialog)
{
    ui->setupUi(this);
}

CustomTestDialog::~CustomTestDialog()
{
    delete ui;
}

void CustomTestDialog::on_pushButtonAccept_clicked()
{
    this->accept();
}

void CustomTestDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

int CustomTestDialog::getStartElitism()
{
    return ui->lineEditStartElitism->text().toInt();
}

int CustomTestDialog::getEndElitism()
{
    return ui->lineEditEndElitism->text().toInt();
}

int CustomTestDialog::getIncrementElitism()
{
    return ui->lineEditIncrementElitism->text().toInt();
}

int CustomTestDialog::getStartMutation()
{
    return ui->lineEditStartMutation->text().toInt();
}

int CustomTestDialog::getEndMutation()
{
    return ui->lineEditEndMutation->text().toInt();
}

int CustomTestDialog::getIncrementMutation()
{
    return ui->lineEditIncrementMutation->text().toInt();
}
