#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    if (ui->lineEdit_x1->text().isEmpty() || ui->lineEdit_x2->text().isEmpty())
    {
        QMessageBox::information(this, "Error", QString("X1 and X2 cant be empty"));
        return;
    }

    try{
        double x1, x2;

        x1 = std::stod(ui->lineEdit_x1->text().toStdString());
        x2 = std::stod(ui->lineEdit_x2->text().toStdString());

        Function f1, f2;

        f1 = Function(x1);
        f2 = Function(x2);

        double y1, y2;
        y1 = f1.get_y();
        y2 = f2.get_y();


        ui->textEdit->setText(QString::fromStdString(
            "Y1: " + std::to_string(y1) +
            "\nY2: " + std::to_string(y2) +
            "\nMax: (" + ((y1 >= y2)? std::to_string(x1) + ", " + std::to_string(y1) : std::to_string(x2) + ", " + std::to_string(y2)) + ")"
        ));
    } catch (LogWrongArgument exception){
        QMessageBox::information(this, "Error", QString::fromStdString(exception.what()));
    } catch (LogArgumentZero exception){
        QMessageBox::information(this, "Error", QString::fromStdString(exception.what()));
    } catch (std::invalid_argument) {
        QMessageBox::information(this, "Error", QString("X1 and X2 must be numbers"));
    }



}

