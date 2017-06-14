#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ToolOpenGL.h"
#include "myglwidget.h"
#include "trebuchet.h"
#include "floor.h"
#include "toolimage.h"
#include "detector.h"
#include "string"
#include "match.h"
#include "throw.h"
#include "math.h"

#include <QTimer>
#include <QSettings>
#include <QTime>
#include <QMainWindow>
#include <QPainter>
#include <QTime>
#include <QString>
#include <QListWidgetItem>
#include <QListWidget>
#include <QStringList>
#include "opencv2/opencv.hpp"

#define PI 3.14159265

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer * showRealTimeVideoTimer;
    QTimer * updateScene3DTimer;
    QTimer * checkHandPositionTimer;
    QTimer * updateTimeTimer;
    VideoCapture videoCapture;
    ToolImage toolImage;
    const QString fistDetectorPath = "fist.xml";
    Detector fistDetector = Detector(fistDetectorPath.toStdString());
    const QString palmDetectorPath = "palm.xml";
    Detector palmDetector = Detector(palmDetectorPath.toStdString());
    Mat srcMat;
    QImage srcQImage;
    QPixmap srcQPixmap;
    QSize imageSize;
    QPixmap welcomImage = QPixmap("./img/tse.png");
    void showMessage(QString message);
    void showRealTimeLabel();
    QPoint currentPos;
    QPoint lastPos;
    float standAngle = 360;
    float swingAngle = 360;
    bool detected = false;
    bool thrown = false;
    bool started = false;
    Match * currentMatch;
    Throw * currentThrow;
    void throwBall();
    Match top1MatchLevel1;
    Match top2MatchLevel1;
    Match top3MatchLevel1;
    Match top1MatchLevel2;
    Match top2MatchLevel2;
    Match top3MatchLevel2;
    Match top1MatchLevel3;
    Match top2MatchLevel3;
    Match top3MatchLevel3;
    const QIcon top1Icon = QIcon("./img/1.png");
    const QIcon top2Icon = QIcon("./img/2.png");
    const QIcon top3Icon = QIcon("./img/3.png");
    const QIcon playerIcon = QIcon(":/img/p.png");
    void updateMatchList();
    void updateMatchListWhenStarted();
    int timeLeft = 60;
    void loadData();
    void saveData();
    const QString dataToSavePath = "data.txt";


public slots:
    void updateScene3D();
    void updateRealTimeCam();
    void checkHandPosition();
    void updateTime();

private slots:
    void on_startButton_clicked();
    void on_pushButton_clicked();
    void on_throwButton_clicked();
};

#endif // MAINWINDOW_H
