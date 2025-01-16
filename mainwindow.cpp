#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("pushButton_%1").arg(i); // arg заменят значение %1
        QPushButton *button = findChild<QPushButton *>(buttonName);

        if (button != nullptr){
            connect(button, &QPushButton::clicked, this, &MainWindow::digit_numbers);  // conect связывает SIGNAL и SLOT
            //connect(button, SIGNAL(clicked()), this, SLOT(digit_numbers())); - old
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers()
{
    QPushButton *button = static_cast<QPushButton*>(sender()); // sender - Возвращает указатель на объект, который вызвал сигнал

    double allNumbers;
    QString new_label;

    allNumbers = (ui->output_label->text()+ button->text()).toDouble();
    new_label = QString::number(allNumbers, 'g', 15); // number - Преобразует число обратно в строку
    ui->output_label->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!ui->output_label->text().contains(".")){ // contains - проверяет, содержится ли в строке определённая подстрока или символ
        ui->output_label->setText(ui->output_label->text() + ".");
    }
}

void MainWindow::on_pushButton_plus_minus_clicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());

    double allNumbers = (ui->output_label->text().toDouble());
    allNumbers *= -1;
    QString new_label = QString::number(allNumbers, 'g', 15);
    ui->output_label->setText(new_label);
}


void MainWindow::on_pushButton_percent_clicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());

    double allNumbers = (ui->output_label->text().toDouble());
    allNumbers *= 0.01;
    QString new_label = QString::number(allNumbers, 'g', 15);
    ui->output_label->setText(new_label);
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->output_label->setText("0");
}

