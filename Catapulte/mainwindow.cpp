#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load detector
    if(!fistDetector.isOpened()){
        fistDetector.open(QFileDialog::getOpenFileName(this, tr("Open fist.xml")).toStdString());
    }
    if(!palmDetector.isOpened()){
        palmDetector.open(QFileDialog::getOpenFileName(this, tr("Open palm.xml")).toStdString());
    }

    showRealTimeVideoTimer = new QTimer();
    updateScene3DTimer = new QTimer();
    checkHandPositionTimer = new QTimer();
    updateTimeTimer = new QTimer();

    QObject::connect(updateScene3DTimer, SIGNAL(timeout()), this, SLOT(updateScene3D()));
    QObject::connect(showRealTimeVideoTimer, SIGNAL(timeout()), this, SLOT(updateRealTimeCam()));
    QObject::connect(checkHandPositionTimer, SIGNAL(timeout()), this, SLOT(checkHandPosition()));
    QObject::connect(updateTimeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    // open camera
    videoCapture.open(1);
    if(videoCapture.isOpened()){  // check if camera opened
        showMessage("using second camera !");
    }else{
        showMessage("Error opening the second camera!\nTrying openning first camera");
        videoCapture.open(0);  // check if camera opened
        if(videoCapture.isOpened()){
            showMessage("using first camera !");
        }else{
            ui->infoLabel_->setText("Error openning camera!");
            showMessage("Error opening the default camera!");
            return;
        }
    }

    ui->infoLabel_->setText("Video ok !");
    QString time = "Current throw time left:\n00:00";
    ui->timeLabel->setText(time);
    QString time2 = "Game time left:\n00:00";
    ui->timeLabel2->setText(time2);
    ui->realTimeLabel->setPixmap(welcomImage);
    const int frameHeight = 240;
    const int frameWidth = 320;
    imageSize.setHeight(frameHeight);
    imageSize.setWidth(frameWidth);
    currentPos = QPoint(0,0);
    lastPos = QPoint(0,0);
    loadData();
    updateMatchListWhenStarted();
    ui->throwButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    QSettings settings(dataToSavePath, QSettings::NativeFormat);
    QString text = settings.value("text", "").toString();
    QStringList list = text.split('\n');
    QString t1l1Name = list.at(0);
    QString t1l1Score = list.at(1);
    QString t2l1Name = list.at(2);
    QString t2l1Score = list.at(3);
    QString t3l1Name = list.at(4);
    QString t3l1Score = list.at(5);
    QString t1l2Name = list.at(6);
    QString t1l2Score = list.at(7);
    QString t2l2Name = list.at(8);
    QString t2l2Score = list.at(9);
    QString t3l2Name = list.at(10);
    QString t3l2Score = list.at(11);
    QString t1l3Name = list.at(12);
    QString t1l3Score = list.at(13);
    QString t2l3Name = list.at(14);
    QString t2l3Score = list.at(15);
    QString t3l3Name = list.at(16);
    QString t3l3Score = list.at(17);
    top1MatchLevel1.setName(t1l1Name.toStdString());
    top1MatchLevel1.setScore(t1l1Score.toFloat());
    top2MatchLevel1.setName(t2l1Name.toStdString());
    top2MatchLevel1.setScore(t2l1Score.toFloat());
    top3MatchLevel1.setName(t3l1Name.toStdString());
    top3MatchLevel1.setScore(t3l1Score.toFloat());
    top1MatchLevel2.setName(t1l2Name.toStdString());
    top1MatchLevel2.setScore(t1l2Score.toFloat());
    top2MatchLevel2.setName(t2l2Name.toStdString());
    top2MatchLevel2.setScore(t2l2Score.toFloat());
    top3MatchLevel2.setName(t3l2Name.toStdString());
    top3MatchLevel2.setScore(t3l2Score.toFloat());
    top1MatchLevel3.setName(t1l3Name.toStdString());
    top1MatchLevel3.setScore(t1l3Score.toFloat());
    top2MatchLevel3.setName(t2l3Name.toStdString());
    top2MatchLevel3.setScore(t2l3Score.toFloat());
    top3MatchLevel3.setName(t3l3Name.toStdString());
    top3MatchLevel3.setScore(t3l3Score.toFloat());
    ui->infoLabel_->setText("Load data success!");
}

void MainWindow::saveData()
{
    QSettings settings(dataToSavePath, QSettings::NativeFormat);

    QString t1l1Name = QString::fromStdString(top1MatchLevel1.getPlayerName());
    QString t1l1Score = QString::number(top1MatchLevel1.getTotalScore());
    QString t2l1Name = QString::fromStdString(top2MatchLevel1.getPlayerName());
    QString t2l1Score = QString::number(top2MatchLevel1.getTotalScore());
    QString t3l1Name = QString::fromStdString(top3MatchLevel1.getPlayerName());
    QString t3l1Score = QString::number(top3MatchLevel1.getTotalScore());

    QString t1l2Name = QString::fromStdString(top1MatchLevel2.getPlayerName());
    QString t1l2Score = QString::number(top1MatchLevel2.getTotalScore());
    QString t2l2Name = QString::fromStdString(top2MatchLevel2.getPlayerName());
    QString t2l2Score = QString::number(top2MatchLevel2.getTotalScore());
    QString t3l2Name = QString::fromStdString(top3MatchLevel2.getPlayerName());
    QString t3l2Score = QString::number(top3MatchLevel2.getTotalScore());

    QString t1l3Name = QString::fromStdString(top1MatchLevel3.getPlayerName());
    QString t1l3Score = QString::number(top1MatchLevel3.getTotalScore());
    QString t2l3Name = QString::fromStdString(top2MatchLevel3.getPlayerName());
    QString t2l3Score = QString::number(top2MatchLevel3.getTotalScore());
    QString t3l3Name = QString::fromStdString(top3MatchLevel3.getPlayerName());
    QString t3l3Score = QString::number(top3MatchLevel3.getTotalScore());

    QString text = t1l1Name+"\n"+t1l1Score+"\n"
            +t2l1Name+"\n"+t2l1Score+"\n"
            +t3l1Name+"\n"+t3l1Score+"\n"
            +t1l2Name+"\n"+t1l2Score+"\n"
            +t2l2Name+"\n"+t2l2Score+"\n"
            +t3l2Name+"\n"+t3l2Score+"\n"
            +t1l3Name+"\n"+t1l3Score+"\n"
            +t2l3Name+"\n"+t2l3Score+"\n"
            +t3l3Name+"\n"+t3l3Score;
    settings.setValue("text", text);
}

void MainWindow::showMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::updateMatchListWhenStarted(){
    ui->matchList->clear();
    if(top1MatchLevel1.getPlayerName() != "NULL"){
        QListWidgetItem *newItem1 = new QListWidgetItem;
        newItem1->setText(top1MatchLevel1.toQString());
        newItem1->setIcon(top1Icon);
        ui->matchList->insertItem(0,newItem1);
    }
    if(top2MatchLevel1.getPlayerName() != "NULL"){
        QListWidgetItem *newItem2 = new QListWidgetItem;
        newItem2->setText(top2MatchLevel1.toQString());
        newItem2->setIcon(top2Icon);
        ui->matchList->insertItem(1,newItem2);
    }
    if(top3MatchLevel1.getPlayerName() != "NULL"){
        QListWidgetItem *newItem3 = new QListWidgetItem;
        newItem3->setText(top3MatchLevel1.toQString());
        newItem3->setIcon(top3Icon);
        ui->matchList->insertItem(2,newItem3);
    }
    ui->matchList2->clear();
    if(top1MatchLevel2.getPlayerName() != "NULL"){
        QListWidgetItem *newItem1 = new QListWidgetItem;
        newItem1->setText(top1MatchLevel2.toQString());
        newItem1->setIcon(top1Icon);
        ui->matchList2->insertItem(0,newItem1);
    }
    if(top2MatchLevel2.getPlayerName() != "NULL"){
        QListWidgetItem *newItem2 = new QListWidgetItem;
        newItem2->setText(top2MatchLevel2.toQString());
        newItem2->setIcon(top2Icon);
        ui->matchList2->insertItem(1,newItem2);
    }
    if(top3MatchLevel2.getPlayerName() != "NULL"){
        QListWidgetItem *newItem3 = new QListWidgetItem;
        newItem3->setText(top3MatchLevel2.toQString());
        newItem3->setIcon(top3Icon);
        ui->matchList2->insertItem(2,newItem3);
    }
    ui->matchList1->clear();
    if(top1MatchLevel3.getPlayerName() != "NULL"){
        QListWidgetItem *newItem1 = new QListWidgetItem;
        newItem1->setText(top1MatchLevel3.toQString());
        newItem1->setIcon(top1Icon);
        ui->matchList1->insertItem(0,newItem1);
    }
    if(top2MatchLevel3.getPlayerName() != "NULL"){
        QListWidgetItem *newItem2 = new QListWidgetItem;
        newItem2->setText(top2MatchLevel3.toQString());
        newItem2->setIcon(top2Icon);
        ui->matchList1->insertItem(1,newItem2);
    }
    if(top3MatchLevel3.getPlayerName() != "NULL"){
        QListWidgetItem *newItem3 = new QListWidgetItem;
        newItem3->setText(top3MatchLevel3.toQString());
        newItem3->setIcon(top3Icon);
        ui->matchList1->insertItem(2,newItem3);
    }
}

void MainWindow::updateMatchList(){
    if(currentMatch->getLevel() == 1){
        if(top1MatchLevel1.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel1 = top2MatchLevel1;
            top2MatchLevel1 = top1MatchLevel1;
            top1MatchLevel1 = *currentMatch;
        }else if(top2MatchLevel1.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel1 = top2MatchLevel1;
            top2MatchLevel1 = *currentMatch;
        }else if(top3MatchLevel1.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel1 = *currentMatch;
        }
        ui->matchList->clear();
        if(top1MatchLevel1.getPlayerName() != "NULL"){
            QListWidgetItem *newItem1 = new QListWidgetItem;
            newItem1->setText(top1MatchLevel1.toQString());
            newItem1->setIcon(top1Icon);
            ui->matchList->insertItem(0,newItem1);
        }
        if(top2MatchLevel1.getPlayerName() != "NULL"){
            QListWidgetItem *newItem2 = new QListWidgetItem;
            newItem2->setText(top2MatchLevel1.toQString());
            newItem2->setIcon(top2Icon);
            ui->matchList->insertItem(1,newItem2);
        }
        if(top3MatchLevel1.getPlayerName() != "NULL"){
            QListWidgetItem *newItem3 = new QListWidgetItem;
            newItem3->setText(top3MatchLevel1.toQString());
            newItem3->setIcon(top3Icon);
            ui->matchList->insertItem(2,newItem3);
        }
    }else if(currentMatch->getLevel() == 2){
        if(top1MatchLevel2.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel2 = top2MatchLevel2;
            top2MatchLevel2 = top1MatchLevel2;
            top1MatchLevel2 = *currentMatch;
        }else if(top2MatchLevel2.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel2 = top2MatchLevel2;
            top2MatchLevel2 = *currentMatch;
        }else if(top3MatchLevel2.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel2 = *currentMatch;
        }
        ui->matchList2->clear();
        if(top1MatchLevel2.getPlayerName() != "NULL"){
            QListWidgetItem *newItem1 = new QListWidgetItem;
            newItem1->setText(top1MatchLevel2.toQString());
            newItem1->setIcon(top1Icon);
            ui->matchList2->insertItem(0,newItem1);
        }
        if(top2MatchLevel2.getPlayerName() != "NULL"){
            QListWidgetItem *newItem2 = new QListWidgetItem;
            newItem2->setText(top2MatchLevel2.toQString());
            newItem2->setIcon(top2Icon);
            ui->matchList2->insertItem(1,newItem2);
        }
        if(top3MatchLevel2.getPlayerName() != "NULL"){
            QListWidgetItem *newItem3 = new QListWidgetItem;
            newItem3->setText(top3MatchLevel2.toQString());
            newItem3->setIcon(top3Icon);
            ui->matchList2->insertItem(2,newItem3);
        }

    }else if(currentMatch->getLevel() == 3){
        if(top1MatchLevel3.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel3 = top2MatchLevel3;
            top2MatchLevel3 = top1MatchLevel3;
            top1MatchLevel3 = *currentMatch;
        }else if(top2MatchLevel3.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel3 = top2MatchLevel3;
            top2MatchLevel3 = *currentMatch;
        }else if(top3MatchLevel3.getTotalScore() <= currentMatch->getTotalScore()){
            top3MatchLevel3 = *currentMatch;
        }
        ui->matchList1->clear();
        if(top1MatchLevel3.getPlayerName() != "NULL"){
            QListWidgetItem *newItem1 = new QListWidgetItem;
            newItem1->setText(top1MatchLevel3.toQString());
            newItem1->setIcon(top1Icon);
            ui->matchList1->insertItem(0,newItem1);
        }
        if(top2MatchLevel3.getPlayerName() != "NULL"){
            QListWidgetItem *newItem2 = new QListWidgetItem;
            newItem2->setText(top2MatchLevel3.toQString());
            newItem2->setIcon(top2Icon);
            ui->matchList1->insertItem(1,newItem2);
        }
        if(top3MatchLevel3.getPlayerName() != "NULL"){
            QListWidgetItem *newItem3 = new QListWidgetItem;
            newItem3->setText(top3MatchLevel3.toQString());
            newItem3->setIcon(top3Icon);
            ui->matchList1->insertItem(2,newItem3);
        }
    }else{
        showMessage("System error: 101");
    }
    saveData();
    QListWidgetItem *newItem4 = new QListWidgetItem;
    newItem4->setText(currentMatch->toQString());
    newItem4->setIcon(playerIcon);
    ui->allPlayerList->insertItem(0,newItem4);
}


void MainWindow::updateScene3D()
{
    if(thrown){
        swingAngle -= 2;
        while(swingAngle > 180){
            swingAngle -= 360;
        }
        while(swingAngle < -180){
            swingAngle += 360;
        }
        float ballLength = ui->myGLWidget->trebuchet.getBallX()*cos(standAngle*PI/180);
        float targetLength = currentThrow->getTargetPoxY();
        float ballHeight = ui->myGLWidget->trebuchet.getBallZ()+1;
        float targetHeight = currentThrow->getTargetPoxZ();
        float ballWidth = ui->myGLWidget->trebuchet.getBallX()*sin(standAngle*PI/180);
        float targetWidth = currentThrow->getTargetPoxX();

        if((swingAngle < 133 && swingAngle > 47) || ballLength >= targetLength){  // end of throw
            if(ballLength < targetLength){
                float score = 0;
                int targetLeft = currentMatch->getNbThrow()-currentMatch->getThrowListSize();
                currentMatch->addScore(0);
                showMessage("score:"+QString::number(score)+"\ntargets left:"+QString::number(targetLeft));
            }else{
                float temp1 = ballHeight-targetHeight;
                float temp2 = ballWidth-targetWidth;
                float distance = temp1*temp1+temp2*temp2;
                float score = fmax(0.0f, 10-distance);
                int targetLeft = currentMatch->getNbThrow()-currentMatch->getThrowListSize();
                currentMatch->addScore(score);
                showMessage("score:"+QString::number(score)+"\ntargets left:"+QString::number(targetLeft));
            }
            QString str = "current score:"+QString::number(currentMatch->getTotalScore())+"!";
            ui->infoLabel_->setText(str);
            currentThrow = new Throw(currentMatch->getLevel());
            currentMatch->addThrow(currentThrow);
            ui->myGLWidget->floor.setTargetHeight(currentThrow->getTargetPoxZ());
            ui->myGLWidget->floor.setTargetPosLength(currentThrow->getTargetPoxY());
            ui->myGLWidget->floor.setTargetPosWidth(currentThrow->getTargetPoxX());
            if(currentMatch->getNbThrow() < currentMatch->getThrowListSize()){      // end of game
                QString str = "end of game!\nYour score:"+QString::number(currentMatch->getTotalScore())+"!";
                ui->infoLabel_->setText(str);
                showMessage(str);
                updateMatchList();
                showRealTimeVideoTimer->stop();
                updateScene3DTimer->stop();
                checkHandPositionTimer->stop();
                ui->startButton->setText("start");
                ui->realTimeLabel->setPixmap(welcomImage);
                delete currentMatch;
                delete currentThrow;
                started = false;
            }
            thrown = false;
            timeLeft = 60;
            currentPos = QPoint(0,0);
        }
    }else{
        standAngle = (float(currentPos.x())+25)*(-60)/320+30;  // +30 to 0 to -30
        swingAngle = (float(currentPos.y())+25)*47/240;
        ui->myGLWidget->trebuchet.setStandAngle(standAngle);
    }
    ui->myGLWidget->trebuchet.setSwingArmAngle(swingAngle);
    ui->myGLWidget->updateGL();
}

void MainWindow::showRealTimeLabel()
{
    QPainter painter(&srcQPixmap);
    painter.setPen(Qt::green);
    painter.drawLine(160,0,160,240);
    painter.drawLine(0,120,320,120);
    if(!detected){
        painter.setPen(Qt::red);
    }else{
        painter.setPen(Qt::blue);
    }
    painter.drawEllipse(currentPos.x(), currentPos.y(), 50, 50);
    painter.drawLine(currentPos.x()+25,0,currentPos.x()+25,240);
    painter.drawLine(0,currentPos.y()+25,320,currentPos.y()+25);
    string str = to_string(currentPos.x()+25)+","+to_string(currentPos.y()+25);
    painter.drawText(currentPos, str.c_str());
    ui->realTimeLabel->setPixmap(srcQPixmap);
}

void MainWindow::checkHandPosition()
{
    if(!thrown){
        lastPos = currentPos;
        int temp[2] = {0,0};
        fistDetector.detect(srcMat, temp);
        if(temp[0] != 0)    // fist detected
        {
            currentPos = QPoint(temp[0], temp[1]);
            detected = true;
        }else {
            palmDetector.detect(srcMat, temp);
            if(temp[0] != 0) {  // detect a fist
                float dis1 = temp[0] - lastPos.x();
                float dis2 = temp[1] - lastPos.y();
                float dis = dis1*dis1+dis2*dis2;
                if(dis < 1500){
                    throwBall();
                }
            }
            detected = false;
        }
    }
}

void MainWindow::updateRealTimeCam()
{
    if(thrown){
        ui->realTimeLabel->setPixmap(welcomImage);
    }else{
        videoCapture >> srcMat;
        if(srcMat.data){
            // basic treatment
            cv::resize(srcMat,srcMat,Size(imageSize.width(),imageSize.height()),0,0,CV_INTER_LINEAR);
            flip(srcMat,srcMat,1);
            cvtColor(srcMat, srcMat, CV_BGR2RGB);
            // get images of different formats
            srcQImage = QImage((uchar*)(srcMat.data), srcMat.cols, srcMat.rows, QImage::Format_RGB888);
            srcQPixmap = QPixmap::fromImage(srcQImage);
            showRealTimeLabel();
        }
    }
}

void MainWindow::updateTime()
{
    if(started){
        timeLeft--;
        QString time = "Current throw time left:\n00:"+QString::number(timeLeft);
        ui->timeLabel->setText(time);
        int targetLeft = currentMatch->getNbThrow()-currentMatch->getThrowListSize();
        QString time2 = "Game time left:\n0"+QString::number(targetLeft)+":"+QString::number(timeLeft);
        ui->timeLabel2->setText(time2);

        if((timeLeft <= 0)&&!thrown){
            throwBall();
            timeLeft = 60;
        }
    }else{
        QString time = "Current throw time left:\n00:00";
        ui->timeLabel->setText(time);
        QString time2 = "Game time left:\n00:00";
        ui->timeLabel2->setText(time2);
    }
}

void MainWindow::on_startButton_clicked()
{
    if(started == false){
        QString playerName = ui->nameTextLine->text();
        if(playerName == ""){
            showMessage("invalide player name");
            return;
        }
        int nbThrow = ui->numComboBox->currentIndex();
        if(nbThrow == 0){
            showMessage("invalide throw number");
            return;
        }
        int level = ui->levelComboBox->currentIndex();
        if(level <= 0 || level >= 4){
            showMessage("invalide level");
            return;
        }

        currentMatch = new Match(playerName.toStdString(), nbThrow, level);
        currentThrow = new Throw(currentMatch->getLevel());
        currentMatch->addThrow(currentThrow);
        ui->myGLWidget->floor.setTargetHeight(currentThrow->getTargetPoxZ());
        ui->myGLWidget->floor.setTargetPosLength(currentThrow->getTargetPoxY());
        ui->myGLWidget->floor.setTargetPosWidth(currentThrow->getTargetPoxX());
        showRealTimeVideoTimer->start(50);
        updateScene3DTimer->start(20);
        checkHandPositionTimer->start(200);
        updateTimeTimer->start(1000);
        ui->startButton->setText("stop");
        started = true;
    }else{
        showRealTimeVideoTimer->stop();
        updateScene3DTimer->stop();
        checkHandPositionTimer->stop();
        ui->startButton->setText("start");
        ui->realTimeLabel->setPixmap(welcomImage);
        delete currentMatch;
        delete currentThrow;
        started = false;
    }
}

void MainWindow::throwBall(){
    if(!started){
        showMessage("start game first!");
    }else{
        float maxSpeed = 1.5;
        float minSpeed = 0.3;
        float speed = currentPos.y()*(maxSpeed-minSpeed)/240+minSpeed;
        ui->myGLWidget->trebuchet.setSpeed(speed);
        thrown = true;
    }
}


void MainWindow::on_throwButton_clicked()
{
    throwBall();
}

void MainWindow::on_pushButton_clicked()
{
    if(!started){
        showMessage("start game first!");
    }else{
        ui->myGLWidget->trebuchet.setCheat();
    }
}
