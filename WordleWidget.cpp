#include "WordleWidget.h"
#include "ui_WordleWidget.h"
#include <QComboBox>
#include <QRegularExpressionValidator>

WordleWidget::WordleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldeWidget)
{
    ui->setupUi(this);
    populateComboBoxes();
}

WordleWidget::~WordleWidget()
{
    delete ui;
}

/**
 * @brief WordleWidget::reset
 * Clear text
 */
void WordleWidget::reset()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

/**
 * @brief WordleWidget::useWord
 * Populate widget with <word>
 * @param word
 */
void WordleWidget::useWord(QString word)
{
    if(word.length() == 5)
    {
        ui->lineEdit_1->setText(word.at(0));
        ui->lineEdit_2->setText(word.at(1));
        ui->lineEdit_3->setText(word.at(2));
        ui->lineEdit_4->setText(word.at(3));
        ui->lineEdit_5->setText(word.at(4));
    }
}

/**
 * @brief WordleWidget::populateComboBoxes
 * Execute populateComboBox on all comboBoxes
 */
void WordleWidget::populateComboBoxes()
{
    populateComboBox(ui->comboBox_1);
    populateComboBox(ui->comboBox_2);
    populateComboBox(ui->comboBox_3);
    populateComboBox(ui->comboBox_4);
    populateComboBox(ui->comboBox_5);
}

/**
 * @brief WordleWidget::populateComboBox
 * Populate <cb> with all hints
 * @param cb
 */
void WordleWidget::populateComboBox(QComboBox *cb)
{
    cb->addItems(hints);
}

/*
 * When a lineEdit is edited, capitalize the letter and advance focus
 * to the next lineEdit.
 */

void WordleWidget::on_lineEdit_1_textEdited(const QString &arg1)
{
    if(!validateLineEdits(arg1))
    {
        ui->lineEdit_1->clear();
    }
    else if(!arg1.isEmpty())
    {
        ui->lineEdit_1->setText(arg1.toUpper());
        ui->lineEdit_2->setFocus();
        ui->lineEdit_2->selectAll();
    }
}

void WordleWidget::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(!validateLineEdits(arg1))
    {
        ui->lineEdit_2->clear();
    }
    else if(!arg1.isEmpty())
    {
        ui->lineEdit_2->setText(arg1.toUpper());
        ui->lineEdit_3->setFocus();
        ui->lineEdit_3->selectAll();
    }
}

void WordleWidget::on_lineEdit_3_textEdited(const QString &arg1)
{
    if(!validateLineEdits(arg1))
    {
        ui->lineEdit_3->clear();
    }
    else if(!arg1.isEmpty())
    {
        ui->lineEdit_3->setText(arg1.toUpper());
        ui->lineEdit_4->setFocus();
        ui->lineEdit_4->selectAll();
    }
}

void WordleWidget::on_lineEdit_4_textEdited(const QString &arg1)
{
    if(!validateLineEdits(arg1))
    {
        ui->lineEdit_4->clear();
    }
    else if(!arg1.isEmpty())
    {
        ui->lineEdit_4->setText(arg1.toUpper());
        ui->lineEdit_5->setFocus();
        ui->lineEdit_5->selectAll();
    }
}

void WordleWidget::on_lineEdit_5_textEdited(const QString &arg1)
{
    if(!validateLineEdits(arg1))
    {
        ui->lineEdit_5->clear();
    }
    else
    {
        ui->lineEdit_5->setText(arg1.toUpper());
    }
}

/**
 * @brief WordleWidget::on_pushButton_submit_clicked
 * Send out word as a QString and all hints in
 * an int[5] via submitWord signal. Clear any letters
 * from line edits that aren't GREEN. Give focus to
 * lineEdit_1.
 */
void WordleWidget::on_pushButton_submit_clicked()
{
    QString word = ui->lineEdit_1->text() + ui->lineEdit_2->text() + ui->lineEdit_3->text() +
            ui->lineEdit_4->text() + ui->lineEdit_5->text();
    int hints[5];
    hints [0] = ui->comboBox_1->currentIndex();
    hints [1] = ui->comboBox_2->currentIndex();
    hints [2] = ui->comboBox_3->currentIndex();
    hints [3] = ui->comboBox_4->currentIndex();
    hints [4] = ui->comboBox_5->currentIndex();

    emit submitWord(word, hints);

    if(hints[0] != 0)
        ui->lineEdit_1->clear();
    if(hints[1] != 0)
        ui->lineEdit_2->clear();
    if(hints[2] != 0)
        ui->lineEdit_3->clear();
    if(hints[3] != 0)
        ui->lineEdit_4->clear();
    if(hints[4] != 0)
        ui->lineEdit_5->clear();

    ui->lineEdit_1->setFocus();
    ui->lineEdit_1->selectAll();
}

bool WordleWidget::validateLineEdits(QString str)
{
    bool ok;
    str.toInt(&ok);
    return !ok;
}


