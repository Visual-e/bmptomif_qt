#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QDebug>


QByteArray picture;
unsigned int pic_width=0, pic_height=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Открываем BMP файл
void MainWindow::on_pushButton_clicked()
{
    QGraphicsScene *scene = new QGraphicsScene;
    QString width,height;
    QString path;
    path = QFileDialog::getOpenFileName(0,"Open BMP", QApplication::applicationDirPath()+"/files", "*.bmp");
    QFile fileIn(path);

    if(fileIn.open(QIODevice::ReadOnly))
        {
        picture = fileIn.readAll(); //читаем файл
        fileIn.close(); //закрываем файл
        scene->addPixmap(QPixmap(path)); //добавляем картинку
        pic_height=scene->height(); //определяем размеры
        pic_width=scene->width();
        height="Heigth="+QString::number(scene->height());
        width="Width="+QString::number(scene->width());
        ui->label->setText(height);
        ui->label_2->setText(width);
        ui->graphicsView->setGeometry(10,40,scene->width(),scene->height());
        ui->graphicsView->setScene(scene); //выводим картинку на форму
        }
}
//Формируем MIF файл
void MainWindow::on_pushButton_2_clicked()
{
    QString mif,adr_str,rgb_str;
    unsigned long adr1,adr2,rgb;
    unsigned char R,G,B;

    if(pic_height*pic_width!=0)
        {
        mif.append("-- Copyright (C) 1991-2015 Altera Corporation. All rights reserved\n");
        mif.append("-- Your use of Altera Corporation's design tools, logic functions\n");
        mif.append("-- and other software and tools, and its AMPP partner logic\n");
        mif.append("-- functions, and any output files from any of the foregoing\n");
        mif.append("-- (including device programming or simulation files), and any\n");
        mif.append("-- associated documentation or information are expressly subject\n");
        mif.append("-- to the terms and conditions of the Altera Program License\n");
        mif.append("-- Subscription Agreement, the Altera Quartus II License Agreement,\n");
        mif.append("-- the Altera MegaCore Function License Agreement, or other\n");
        mif.append("-- applicable license agreement, including, without limitation,\n");
        mif.append("-- that your use is for the sole purpose of programming logic\n");
        mif.append("-- devices manufactured by Altera and sold by Altera or its\n");
        mif.append("-- authorized distributors.  Please refer to the applicable\n");
        mif.append("-- agreement for further details.\n");
        mif.append("                                 \n");
        mif.append("-- Quartus II generated Memory Initialization File (.mif)\n");
        mif.append("                                 \n");
        mif.append("WIDTH=24;\n");
        mif.append("DEPTH="+QString::number(pic_height*pic_width)+";\n");
        mif.append("                                 \n");
        mif.append("ADDRESS_RADIX=UNS;\n");
        mif.append("DATA_RADIX=UNS;\n");
        mif.append("                                 \n");
        mif.append("CONTENT BEGIN\n");

        //Перебираем пиксели bmp файла
        for(unsigned int dy=0;dy<pic_height;dy++)
          {
           for(unsigned int dx=0;dx<pic_width;dx++)
            {
            adr1=pic_width*dy+dx;
            adr2=pic_width*(pic_height-dy-1)+dx;
            R=picture.data()[54+adr2*3];
            G=picture.data()[54+adr2*3+1];
            B=picture.data()[54+adr2*3+2];
            rgb=R*65536 + G*256 + B;
            adr_str=QString::number(adr1);
            rgb_str=QString::number(rgb);
            mif.append(adr_str);
            mif.append(":");
            mif.append(rgb_str);
            mif.append(";\n");
            }
           }

    mif.append("END;\n");

    //Сораняем файл
    QString path;
    path = QFileDialog::getSaveFileName(0,"Save MIF", QApplication::applicationDirPath()+"/files", "*.mif");
    QFile fileOut(path);
    if(fileOut.open(QIODevice::WriteOnly))
       {
        QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
        // и передаем ему адрес объекта fileOut
        writeStream << mif; // Посылаем строку в поток для записи
        fileOut.close(); // Закрываем файл
       }
    }
}
