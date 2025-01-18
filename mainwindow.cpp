#include "mainwindow.h"
#include "./ui_mainwindow.h"

double numFirst, numSecond;

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

    connect(ui->pushButton_plus, &QPushButton::clicked, this, &MainWindow::math_operations);
    connect(ui->pushButton_minus, &QPushButton::clicked, this, &MainWindow::math_operations);
    connect(ui->pushButton_division, &QPushButton::clicked, this, &MainWindow::math_operations);
    connect(ui->pushButton_multiplication, &QPushButton::clicked, this, &MainWindow::math_operations);

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers()
{
    QPushButton *button = static_cast<QPushButton*>(sender()); // sender - Возвращает указатель на объект, который вызвал сигнал
    QString currentText = ui->output_label->text();
    QString buttonText = button->text();

    if(currentText == "0" && buttonText != "."){
        currentText = buttonText;
    }
    else{
        currentText += buttonText;
    }

    ui->output_label->setText(currentText);
}

void MainWindow::on_pushButton_dot_clicked()
{
    QString currentText = ui->output_label->text();

    if (!currentText.contains(".")){ // contains - проверяет, содержится ли в строке определённая подстрока или символ
        ui->output_label->setText(currentText + ".");
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

    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_division->setChecked(false);
    ui->pushButton_multiplication->setChecked(false);
}

void MainWindow::math_operations()
{
    QPushButton *button = static_cast<QPushButton*>(sender());

    numFirst = ui->output_label->text().toDouble();
    ui->output_label->setText("");

    button->setChecked(true);
}


void MainWindow::on_pushButton_equally_clicked()
{
    double labelNumber;
    QString newLabel;

    numSecond = ui->output_label->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNumber = numFirst + numSecond;
        QString new_label = QString::number(labelNumber, 'g', 15);
        ui->output_label->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked()){
        labelNumber = numFirst - numSecond;
        QString new_label = QString::number(labelNumber, 'g', 15);
        ui->output_label->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_multiplication->isChecked()){
        labelNumber = numFirst * numSecond;
        QString new_label = QString::number(labelNumber, 'g', 15);
        ui->output_label->setText(new_label);
        ui->pushButton_multiplication->setChecked(false);
    }
    else if (ui->pushButton_division->isChecked()){
        if (numFirst == 0){
            ui->output_label->setText("0");
        }
        else{
            labelNumber = numFirst / numSecond;
            QString new_label = QString::number(labelNumber, 'g', 15);
            ui->output_label->setText(new_label);
            ui->pushButton_division->setChecked(false);
        }
    }
}

