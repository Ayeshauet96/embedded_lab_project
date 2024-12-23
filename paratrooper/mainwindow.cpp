#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 0;
    row = 0;
    col = rand() % 8;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rescue_boat()));
    timer->setInterval(300);
    timer->start();

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(row_bubble()));
    timer1->setInterval(400);
    timer1->start();

    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(write_results_to_module()));
    timer2->setInterval(100);
    timer2->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    counter--;
    if (counter < 0){
        counter = 0;
    }

}

void MainWindow::on_pushButton_2_clicked()
{

    counter++;
    if (counter > 5){
        counter = 5;
    }

}


void MainWindow::rescue_boat(){

    int j;
    for(j=0; j<8;j++){
        bitstream[15][j]=0;
    }
    if (counter == 0){
        bitstream[15][0] = 1;
        bitstream[15][1] = 1;
        bitstream[15][2] = 1;
        tab_pos[0] = 0;
        tab_pos[1] = 1;
        tab_pos[2] = 2;
    }

    if (counter == 1){
        bitstream[15][1] = 1;
        bitstream[15][2] = 1;
        bitstream[15][3] = 1;
        tab_pos[0] = 1;
        tab_pos[1] = 2;
        tab_pos[2] = 3;
    }

    if (counter == 2){
        bitstream[15][2] = 1;
        bitstream[15][3] = 1;
        bitstream[15][4] = 1;
        tab_pos[0] = 2;
        tab_pos[1] = 3;
        tab_pos[2] = 4;
    }

    if (counter == 3){
        bitstream[15][3] = 1;
        bitstream[15][4] = 1;
        bitstream[15][5] = 1;
        tab_pos[0] = 3;
        tab_pos[1] = 4;
        tab_pos[2] = 5;
    }

    if (counter == 4){
        bitstream[15][4] = 1;
        bitstream[15][5] = 1;
        bitstream[15][6] = 1;
        tab_pos[0] = 4;
        tab_pos[1] = 5;
        tab_pos[2] = 6;
    }

    if (counter == 5){
        bitstream[15][5] = 1;
        bitstream[15][6] = 1;
        bitstream[15][7] = 1;
        tab_pos[0] = 5;
        tab_pos[1] = 6;
        tab_pos[2] = 7;
    }


}
int random(int upper, int lower){
    return ((abs(rand()) % (upper - lower + 1)) + lower);
}

int sum_arr(int arr[], int length)
{
int i,sum=0;

    for(i=0; i<length; i++)
    {
         sum+=arr[i];

    }
    return sum;
}


int MainWindow::random_col(){

   randcolgen:
    col = rand()%8;
   if (skip_row[col] == 1){
       goto randcolgen;
   }
   else{
       return col;
   }}


 void MainWindow::row_bubble(){
     memset(&bitstream[0][0], 0, sizeof(bitstream));

     int bubble_counter = 0;
     int bubble_max = 0;


     if (bubble_counter>=bubble_max){

         bitstream[row][col] = 1;
         row++;
         bubble_counter=0;}

     bubble_counter+=100;

     if (row == 15){
           if (col != tab_pos[0] && col != tab_pos[1] && col != tab_pos[2])
           {
              skip_row[col]=1;
           }

           //Detects Catch and the Miss
           else{
              score++;
           }

           if (sum_arr(skip_row, 8) >=3){
               sprintf(str, "your score is %d", score);

               ui->label->setText(QString(str));

               ui->label_2->setText(QString(str1));
               timer->stop();
               timer1->stop();
               timer2->stop();
               //terminate here
           }

           col = random_col();    //Next starting position of the paratroopers
           bubble_max =random(500, 100);
           row = 0;
        }
     }


 void MainWindow::write_results_to_module()
 {
     int i,j;
     for(i=0; i<16; i++){
         for(j=0; j<8; j++){
             temp[i*8+j]=bitstream[i][j];
             mat_em_state[i*8+j]= temp[i*8+j]+'0';
         }
     }


     QFile file("/dev/mat-em");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

     file.write(mat_em_state, qstrlen(mat_em_state));


     file.close();


 }





