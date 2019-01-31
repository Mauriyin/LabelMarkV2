#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_chooseInsulator.h"
#include <QFileDialog>
//#include <QDebug>
#include<QTextStream>
#include<QTreeView>
#include<QDirModel>
#include<QMouseEvent>
#include<QPainter>
#include<QToolTip>
#include<QMessageBox>
#include<help.h>

class chooseInsulator : public QMainWindow
{
	Q_OBJECT

public:
	chooseInsulator(QWidget *parent = Q_NULLPTR);
	//bool FindFile(const QString & path);

	bool findImage(const QString & path);
	help* helper;

private:
	Ui::chooseInsulatorClass ui;
	QString srcDirPath;

	int nFiles;
	bool isFindFile;

	int totalImage;
	int currentImage;
	QString TotalImageShow;
	QString currentImageShow;
	QVector<QString> imageName;

	QVector<QString> insulatorX1;
	QVector<QString> insulatorY1;
	QVector<QString> insulatorX2;
	QVector<QString> insulatorY2;

	int imageNo;

	QImage image;

	QPainter painter;

	int mousepress_x;
	int mousepress_y;

	int mousemove_x;
	int mousemove_y;

	int mouserelease_x;
	int mouserelease_y;
	int Rectw;
	int Recth;
	//double Length;


protected:
	void paintEvent(QPaintEvent *e);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void on_actionOpen_triggered();
	void on_chooseDir_clicked();
	void on_nextImage_clicked();
	void on_upperImage_clicked();
	void keyPressEvent(QKeyEvent *event);
	
};
