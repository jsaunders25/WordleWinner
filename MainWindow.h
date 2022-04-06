#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class WordleWinner;
class QStringListModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WordleWinner *wordle_winner;
    QStringListModel *model;
    QMap<QChar, int> scrabble_scores;
    QStringList ignored_words;

    int calculateScrabbleScore(QString word);
    void populateScoreMap();

private slots:
    void receiveGuess(QString word, int hints[5]);
    void receiveRemainingWords(QSet<QString> words);
    void on_pushButton_reset_clicked();
    void on_listView_remaining_pressed(const QModelIndex &index);
    void on_pushButton_another_clicked();
};
#endif // MAINWINDOW_H
