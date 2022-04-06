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
    populateScoreMap();

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
 * @brief MainWindow::calculateScrabbleScore
 * Calculate Scrabble score of <word>. Return the score.
 * @param word
 * @return
 */
int MainWindow::calculateScrabbleScore(QString word)
{
    int score = 0;
    foreach(QChar letter, word)
    {
        score += scrabble_scores.value(letter);
    }
    return score;
}

/**
 * @brief MainWindow::populateScoreMap
 * Populate map matching letters to their Scrabble scores
 */
void MainWindow::populateScoreMap()
{
    scrabble_scores.insert('A', 1);
    scrabble_scores.insert('B', 3);
    scrabble_scores.insert('C', 3);
    scrabble_scores.insert('D', 2);
    scrabble_scores.insert('E', 1);
    scrabble_scores.insert('F', 4);
    scrabble_scores.insert('G', 2);
    scrabble_scores.insert('H', 4);
    scrabble_scores.insert('I', 1);
    scrabble_scores.insert('J', 8);
    scrabble_scores.insert('K', 5);
    scrabble_scores.insert('L', 1);
    scrabble_scores.insert('M', 3);
    scrabble_scores.insert('N', 1);
    scrabble_scores.insert('O', 1);
    scrabble_scores.insert('P', 3);
    scrabble_scores.insert('Q', 10);
    scrabble_scores.insert('R', 1);
    scrabble_scores.insert('S', 1);
    scrabble_scores.insert('T', 1);
    scrabble_scores.insert('U', 1);
    scrabble_scores.insert('V', 4);
    scrabble_scores.insert('W', 4);
    scrabble_scores.insert('X', 8);
    scrabble_scores.insert('Y', 4);
    scrabble_scores.insert('Z', 10);
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
    int lowscore = 30;
    foreach(QString word, words)
    {
        list << word;
        int score = calculateScrabbleScore(word);
        if(score < lowscore)
        {
            lowscore = score;
            ui->lineEdit_common->setText(word);
        }
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
    ui->lineEdit_common->clear();
    wordle_winner->reset();
    ui->wordle_widget->reset();
    model->setStringList(QStringList());
    ignored_words.clear();
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

/**
 * @brief MainWindow::on_pushButton_another_clicked
 * When "Another" button is clicked, add current word
 * to list of ignored words and find next lowest scored word
 */
void MainWindow::on_pushButton_another_clicked()
{
    ignored_words << ui->lineEdit_common->text();
    int lowscore = 30;
    foreach(QString word, model->stringList())
    {
        if(!ignored_words.contains(word))
        {
            int score = calculateScrabbleScore(word);
            if(score < lowscore)
            {
                lowscore = score;
                ui->lineEdit_common->setText(word);
            }
        }
    }
}

