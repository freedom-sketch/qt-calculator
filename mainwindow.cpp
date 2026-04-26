#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSizePolicy>
#include <QString>
#include <QTextEdit>

#define ERR_OVERFLOW "Переполнение"

const int MAX_DIGITS = 15;

MainWindow::MainWindow (QWidget *parent) : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->outTextEdit->setText("0");
  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow () { delete ui; }

/* Функция для добавления цифры в конец числа */
void MainWindow::append_digit(QString str_digit)
{
  if (this->expr.waitingForNext) {
      ui->outTextEdit->clear();
      if (!this->expr.isFirstEqualClick) {
          this->expr.sign = 0;
          this->expr.isFirstEqualClick = true;
        }
      this->expr.waitingForNext = false;
    }

  QString cur_txt = ui->outTextEdit->toPlainText();

  if (cur_txt.length() < MAX_DIGITS) {
      if (cur_txt == "0")
        ui->outTextEdit->setText(str_digit);
      else
        ui->outTextEdit->setText(cur_txt + str_digit);
    }
  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

/* Кнопки ввода цифр */
void MainWindow::on_btn1_clicked() {append_digit("1");}
void MainWindow::on_btn2_clicked() {append_digit("2");}
void MainWindow::on_btn3_clicked() {append_digit("3");}
void MainWindow::on_btn4_clicked() {append_digit("4");}
void MainWindow::on_btn5_clicked() {append_digit("5");}
void MainWindow::on_btn6_clicked() {append_digit("6");}
void MainWindow::on_btn7_clicked() {append_digit("7");}
void MainWindow::on_btn8_clicked() {append_digit("8");}
void MainWindow::on_btn9_clicked() {append_digit("9");}
void MainWindow::on_btn0_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt == "0") return;
  append_digit("0");
}

/* Кнопка удаления последней цифры */
void MainWindow::on_backspaceBtn_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt == ERR_OVERFLOW) {
      ui->outTextEdit->setText("0");
      ui->outTextEdit->setAlignment(Qt::AlignRight);
      return;
    }
  cur_txt.chop(1);
  ui->outTextEdit->setText(cur_txt);
  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_clearBtn_clicked()
{
  ui->outTextEdit->setText("0");
  ui->outTextEdit->setAlignment(Qt::AlignRight);
  this->expr.reset();
}

void MainWindow::on_btn_unar_minus_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();

  if (cur_txt.isEmpty()) {
      cur_txt = "0";
    }

  if (cur_txt[0] == '-') {
      cur_txt.remove(0, 1);
      if (cur_txt.isEmpty()) {
          cur_txt = "0";
        }
    } else {
      if (cur_txt.toDouble() != 0.0) cur_txt.prepend('-');
    }

  ui->outTextEdit->setText(cur_txt);
  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_commaBtn_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt.contains(".")) return;

  ui->outTextEdit->setText(cur_txt + ".");
  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_btnXsqr_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt.isEmpty()) return;

  bool ok;
  double num = cur_txt.toDouble(&ok);

  if (!ok) return;

  double result = num*num;

  if (std::isinf(result)) {
      ui->outTextEdit->setText(ERR_OVERFLOW);
    } else {
      ui->outTextEdit->setText(QString::number(result, 'g', 6));
    }

  ui->outTextEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_divBtn_clicked()
{
  if (ui->outTextEdit->toPlainText().isEmpty()) return;

  if (this->expr.waitingForNext && this->expr.sign != 0) {
      this->expr.sign = '/';
      return;
    }

  if (this->expr.sign != 0) {
      on_btnEqual_clicked();
    }

  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt.isEmpty()) return;

  this->expr.operand_1 = cur_txt.toDouble();
  this->expr.sign = '/';

  this->expr.waitingForNext = true;
  this->expr.isFirstEqualClick = true;
}

void MainWindow::on_btn1divx_clicked()
{
  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt.isEmpty()) return;

  bool ok;
  double num = cur_txt.toDouble(&ok);

  if (!ok || num == 0) {
      ui->outTextEdit->setText("Ошибка");
      ui->outTextEdit->setAlignment(Qt::AlignRight);
      return;
    }

  double result = 1.0 / num;

  ui->outTextEdit->setText(QString::number(result, 'g', 6));
  ui->outTextEdit->setAlignment(Qt::AlignRight);

  this->expr.operand_1 = result;
  this->expr.waitingForNext = true;
}

void MainWindow::on_plusBtn_clicked()
{
  if (ui->outTextEdit->toPlainText().isEmpty()) return;

  if (this->expr.waitingForNext && this->expr.sign != 0) {
      this->expr.sign = '+';
      return;
    }

  if (this->expr.sign != 0) {
      on_btnEqual_clicked();
    }

  QString cur_txt = ui->outTextEdit->toPlainText();
  this->expr.operand_1 = cur_txt.toDouble();
  this->expr.sign = '+';

  this->expr.waitingForNext = true;
  this->expr.isFirstEqualClick = true;
}

void MainWindow::on_minusBtn_clicked()
{
  if (ui->outTextEdit->toPlainText().isEmpty()) return;

  if (this->expr.waitingForNext && this->expr.sign != 0) {
      this->expr.sign = '-';
      return;
    }

  if (this->expr.sign != 0) {
      on_btnEqual_clicked();
    }

  QString cur_txt = ui->outTextEdit->toPlainText();
  this->expr.operand_1 = cur_txt.toDouble();
  this->expr.sign = '-';

  this->expr.waitingForNext = true;
  this->expr.isFirstEqualClick = true;
}

void MainWindow::on_multiplyBtn_clicked()
{
  if (ui->outTextEdit->toPlainText().isEmpty()) return;

  if (this->expr.waitingForNext && this->expr.sign != 0) {
      this->expr.sign = '*';
      return;
    }

  if (this->expr.sign != 0) {
      on_btnEqual_clicked();
    }

  QString cur_txt = ui->outTextEdit->toPlainText();
  this->expr.operand_1 = cur_txt.toDouble();
  this->expr.sign = '*';

  this->expr.waitingForNext = true;
  this->expr.isFirstEqualClick = true;
}

void MainWindow::on_btnEqual_clicked()
{
  if (this->expr.sign == 0) return;

  QString cur_txt = ui->outTextEdit->toPlainText();
  if (cur_txt.isEmpty()) return;

  if (!this->expr.waitingForNext) {
      this->expr.operand_2 = cur_txt.toDouble();
    }

  double result = 0;
  switch (this->expr.sign)
    {
    case '+':
      result = this->expr.operand_1 + this->expr.operand_2;
      break;
    case '-':
      result = this->expr.operand_1 - this->expr.operand_2;
      break;
    case '*':
      result = this->expr.operand_1 * this->expr.operand_2;
      break;
    case '/':
      if (this->expr.operand_2 == 0) {
          ui->outTextEdit->setText("Ошибка деления на ноль");
          ui->outTextEdit->setAlignment(Qt::AlignRight);
          this->expr.reset();
          return;
        }
      result = this->expr.operand_1 / this->expr.operand_2;
      break;
    }

  if (std::isinf(result)) {
      ui->outTextEdit->setText(ERR_OVERFLOW);
      this->expr.reset();
      return;
    }

  ui->outTextEdit->setText(QString::number(result, 'g', 6));
  ui->outTextEdit->setAlignment(Qt::AlignRight);

  this->expr.operand_1 = result;
  this->expr.waitingForNext = true;
}