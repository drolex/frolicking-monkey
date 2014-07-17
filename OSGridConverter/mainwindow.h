#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QWidget
{
public:
    MainWindow();

public slots:
    void convert();

private:
    QPushButton *convertButton;


};


#endif // MAINWINDOW_H
