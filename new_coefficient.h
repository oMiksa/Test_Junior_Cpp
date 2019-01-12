#ifndef NEW_COEFFICIENT_H
#define NEW_COEFFICIENT_H

#include <QDialog>
#include <QString>

namespace Ui {
class new_coefficient;
}

class new_coefficient : public QDialog
{
    Q_OBJECT

public:
    explicit new_coefficient(double *coefficient, QWidget *parent = nullptr);
    ~new_coefficient();

    double *cof;

private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::new_coefficient *ui;
};

#endif // NEW_COEFFICIENT_H
