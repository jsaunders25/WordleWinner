#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WordleWinner.h"
#include <algorithm>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Wordle Winner");

    wordle_winner = new WordleWinner();
    model = new QStringListModel();
    ui->listView_remaining->setModel(model);

    connect(ui->wordle_widget, &WordleWidget::submitWord, this, &MainWindow::receiveGuess);
    connect(wordle_winner, &WordleWinner::sendRemainingWords, this, &MainWindow::receiveRemainingWords);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wordle_winner;
    delete model;
}

/**
 * @brief MainWindow::receiveGuess
 * Receive guess from the Wordle Widget. Construct a WordleWord struct
 * using <word> and <hints> and send to WordleWinner.
 * Append <word> to textBrowser_guesses.
 * @param word
 * @param hints
 */
void MainWindow::receiveGuess(QString word, int hints[5])
{
    WordleWinner::WordleWord w_word;
    w_word.word = word;
    w_word.hints[0] = static_cast<WordleWinner::Hints>(hints[0]);
    w_word.hints[1] = static_cast<WordleWinner::Hints>(hints[1]);
    w_word.hints[2] = static_cast<WordleWinner::Hints>(hints[2]);
    w_word.hints[3] = static_cast<WordleWinner::Hints>(hints[3]);
    w_word.hints[4] = static_cast<WordleWinner::Hints>(hints[4]);
    wordle_winner->addGuess(w_word);
    ui->textBrowser_guesses->append(word);
}

/**
 * @brief MainWindow::receiveRemainingWords
 * Receive remaining valid words from WordleWinner.
 * Construct an alphebatized QStringList to display.
 * @param words
 */
void MainWindow::receiveRemainingWords(QSet<QString> words)
{
    QStringList list;
    foreach(QString word, words)
    {
        list << word;
    }
    std::sort(list.begin(), list.end());
    model->setStringList(list);
}

/**
 * @brief MainWindow::on_pushButton_reset_clicked
 * Reset all objects to starting point.
 */
void MainWindow::on_pushButton_reset_clicked()
{
    ui->textBrowser_guesses->clear();
    wordle_winner->reset();
    ui->wordle_widget->reset();
    model->setStringList(QStringList());
}

/**
 * @brief MainWindow::on_listView_remaining_pressed
 * When item in list is clicked, populate WordleWidget
 * with that item.
 * @param index
 */
void MainWindow::on_listView_remaining_pressed(const QModelIndex &index)
{
    QString word = model->data(index).toString();
    ui->wordle_widget->useWord(word);
}

