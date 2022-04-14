#include "ConfigureDialog.h"
#include "ui_ConfigureDialog.h"

ConfigureDialog::ConfigureDialog(QWidget *parent, int length, int count, bool suggest, bool survivle) :
    QDialog(parent),
    ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);
    setWindowTitle("Configure");

    ui->spinBox_length->setValue(length);
    ui->spinBox_count->setValue(count);
    ui->checkBox_suggestions->setChecked(suggest);
    ui->checkBox_survivle->setChecked(survivle);
    ui->checkBox_survivle->setToolTip("Not Implemented");

    connect(ui->checkBox_suggestions, &QCheckBox::clicked, ui->checkBox_survivle, &QCheckBox::setEnabled);
}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

void ConfigureDialog::on_buttonBox_accepted()
{
    emit configurationSignal(ui->spinBox_length->value(),
                             ui->spinBox_count->value(),
                             ui->checkBox_suggestions->isChecked(),
                             ui->checkBox_survivle->isChecked() && ui->checkBox_survivle->isEnabled());
}

