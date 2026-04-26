#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();

private slots:
  void on_btn1_clicked();
  void on_btn2_clicked();
  void on_btn3_clicked();
  void on_btn4_clicked();
  void on_btn5_clicked();
  void on_btn6_clicked();
  void on_btn7_clicked();
  void on_btn8_clicked();
  void on_btn9_clicked();
  void on_btn0_clicked();

  void on_backspaceBtn_clicked();
  void on_clearBtn_clicked();

  void on_btn_unar_minus_clicked();

  void on_commaBtn_clicked();

  void on_btnXsqr_clicked();

  void on_btn1divx_clicked();

  void on_divBtn_clicked();
  void on_plusBtn_clicked();
  void on_minusBtn_clicked();
  void on_multiplyBtn_clicked();

  void on_btnEqual_clicked();

private:
  Ui::MainWindow *ui;

  void append_digit(QString str_digit);

  struct Expression {
    double operand_1 = 0;
    double operand_2 = 0;
    double result = 0;
    char sign = 0;
    bool waitingForNext = false;
    bool isFirstEqualClick = true;

    void reset()
    {
      operand_1 = 0;
      operand_2 = 0;
      result = 0;
      sign = 0;
      waitingForNext = false;
      isFirstEqualClick = true;
    }
  };

  struct Expression expr;
};

#endif // MAINWINDOW_H
