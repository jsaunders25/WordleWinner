#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigureDialog;
}

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureDialog(QWidget *parent = nullptr, int length = 5, int count = 1, bool suggest = true, bool survivle = false);
    ~ConfigureDialog();

signals:
    void configurationSignal(int length, int count, bool suggest, bool survivle);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConfigureDialog *ui;
};

#endif // CONFIGUREDIALOG_H
