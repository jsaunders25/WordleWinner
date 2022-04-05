#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void receiveGuess(QString word, int hints[5]);
    void receiveRemainingWords(QSet<QString> words);
    void on_pushButton_reset_clicked();
    void on_listView_remaining_pressed(const QModelIndex &index);
};
#endif // MAINWINDOW_H
