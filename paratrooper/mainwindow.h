#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimer>
#include <string>
#include <QFile>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int bitstream[16][8] = {{0}};
    int counter = 0;
    int skip_row[8] = {0};
    int tab_pos[3] = {0};
    int row;
    int col;
    int score=0;
    char	str[25];
    char    str1[12] = "Game Over!";
    int temp[128];
    char buffer[20];
    char mat_em_state [128];
    QString string;
    QTimer * timer;
    QTimer * timer1;
    QTimer * timer2;
    explicit MainWindow(QWidget *parent = 0);
    int random_col();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void rescue_boat();

    void row_bubble();

    void write_results_to_module();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
