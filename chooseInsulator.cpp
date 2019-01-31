#include "chooseInsulator.h"

chooseInsulator::chooseInsulator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(this->width(), this->height());  //�̶����ڴ�С��

	totalImage = 0;
	imageNo = 0;
	currentImage = 0;
	nFiles = 0;


	mousepress_x=0;
	mousepress_y=0;

	mousemove_x=0;
	mousemove_y=0;

	mouserelease_x=0;
	mouserelease_y=0;

	Rectw=0;
	Recth=0;
}



void chooseInsulator::on_chooseDir_clicked()
{
	srcDirPath = QFileDialog::getExistingDirectory(
		this, "choose src Directory",
		"/");

	if (srcDirPath.isEmpty())
	{
		QMessageBox::information(NULL, tr("warning"), tr("Directory cannot be empty"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		return;
	}
	else
	{
		//qDebug() << "srcDirPath=" << srcDirPath;

		ui.comboBox_dir->addItem(srcDirPath);
		//srcDirPath += "/";
		//imageList = getFileNames(srcDirPath);


		QDirModel *model = new QDirModel();
		ui.treeView->setModel(model);
		ui.treeView->setRootIndex(model->index(srcDirPath));

	}
	isFindFile = findImage(srcDirPath);


	
}

//
//bool chooseInsulator::FindFile(const QString & path)
//{
//	QString format;
//	QDir dir(path);/* Windowsϵͳ�ϻὫWindows���ļ�·���ϵ�/ת��Ϊ\  */
//	if (!dir.exists())
//		return false;
//	dir.setFilter(QDir::Dirs | QDir::Files);/*��Ϊ���õݹ飬���Ա�����Ŀ¼���ļ����ֹ�����*/
//	dir.setSorting(QDir::DirsFirst);/*QDir::DirsFirst	0x04	Put the directories first, then the files.*/
//	QFileInfoList list = dir.entryInfoList();  //����ļ����µ������ļ��б�ʵ�ʻ�ȡ�Ķ�2��
//
//	if (list.empty())
//		return false;
//	/*
//	QFileInfoList QDir::entryInfoList(const QStringList &nameFilters, QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const
//
//	Returns a list of QFileInfo objects for all the files and directories in the directory, ordered according to the name
//
//	and attribute filters previously set with setNameFilters() and setFilter(), and sorted according to the flags set with setSorting().
//
//	The name filter, file attribute filter, and sorting specification can be overridden using the nameFilters, filters, and sort arguments.
//
//	Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.
//
//	See also entryList(), setNameFilters(), setSorting(), setFilter(), isReadable(), and exists().
//	*/
//
//	int i = 0;
//	do{
//
//		QFileInfo fileInfo = list.at(i);
//		/*	.����ǰĿ¼��Ҳ������Ŀǰ�򿪵��Ǹ��ļ��У�
//		.. ������һ��Ŀ¼*/
//		if (fileInfo.fileName() == "." | fileInfo.fileName() == "..")   //ȥ����õ�2��fileInfo.fileName�еĲ�����ļ����ļ��У�
//		{
//			i++;
//			continue;
//		}
//		bool bisDir = fileInfo.isDir();
//		if (bisDir)
//		{
//			nFiles++;
//			//qDebug() << fileInfo.path() + fileInfo.fileName();       //��ӡ�����ļ���
//			chooseInsulator::FindFile(fileInfo.filePath());         //�ݹ���ã���ȡ�ļ����е��ļ�
//		}
//		else{
//			nFiles++;
//			QStringList filters;
//			format = fileInfo.fileName().right(3);
//			/*�������ַ����˲�����ͨ����Ƚ���ʽ��*/
//			if (format == "jpg" || format == "png" || format == "bmp")//ֻȡ���ļ����ַ�������3λ��ֻ������Сд��ĸ
//			{
//				QString imageFilePath = fileInfo.path() + "/" + fileInfo.fileName();
//				qDebug() << "nFiles=" << nFiles<<"," << "imageFilePath=" << imageFilePath << endl;
//				//ui.imageFileListWidget->addItem(imageFilePath);
//
//				QPixmap pixmap;
//				QImage image;
//				image.load(imageFilePath);
//				image = image.scaled(ui.imageLable->size());//��ͼ̫��resize�������ϵ�imageLable�ĳߴ�
//
//				/* static QPixmap fromImage(const QImage &image, Qt::ImageConversionFlags flags = Qt::AutoColor);
//				fromImage()�������ص���QPixmap��������Ҫ��pixmap����ö���*/
//				pixmap = pixmap.fromImage(image);
//
//				ui.imageLable->setPixmap(pixmap);
//				ui.imageLable->show();
//				//imageLabel->setPixmap(pixmap);
//
//				
//			}
//		}
//		i++;
//	} while (i < list.size());
//
//	return true;
//}



bool chooseInsulator::findImage(const QString & path)
{
	QString format;
	QDir dir(path);/* Windowsϵͳ�ϻὫWindows���ļ�·���ϵ�/ת��Ϊ\  */
	if (!dir.exists())
		return false;
	dir.setFilter(QDir::Dirs | QDir::Files);/*��Ϊ���õݹ飬���Ա�����Ŀ¼���ļ����ֹ�����*/
	dir.setSorting(QDir::DirsFirst);/*QDir::DirsFirst	0x04	Put the directories first, then the files.*/
	QFileInfoList list = dir.entryInfoList();  //����ļ����µ������ļ��б�ʵ�ʻ�ȡ�Ķ�2��

	if (list.empty())
		return false;


	for (int i = 0; i < list.size() ; i++)
	{
		QFileInfo fileInfo = list.at(i);
		QStringList filters;
		format = fileInfo.fileName().right(3);

		//qDebug() << "fileInfo.fileName()=" << fileInfo.fileName() << endl;

        if (format == "jpg" || format == "png" || format == "bmp" || format == "jpeg")//ֻȡ���ļ����ַ�������3λ��ֻ������Сд��ĸ
		{
			totalImage++;
			imageName.push_back(fileInfo.fileName());
		}
	}
	//qDebug() << "totalImage=" << totalImage << endl;
	if (totalImage == 0)
	{
		QMessageBox::information(NULL, tr("warning"), tr("There are no image data under this folder!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}

	TotalImageShow = QString::number(totalImage, 10);
	ui.TotalImage->setText(TotalImageShow);

	//for (int j = 0; j < imageName.size(); j++)
	//{
	//	qDebug() << "imageName[" << j << "]="<<imageName[j] << endl;
	//}

	currentImage = 1;
	imageNo = 0;

	currentImageShow = QString::number(currentImage, 10);

	ui.imageNoLabel->setText(currentImageShow);

	QString imageFilePath = srcDirPath + "/" + imageName[imageNo];
	QPixmap pixmap;
	
	if (!image.load(imageFilePath))
	{
		QMessageBox::information(NULL, tr("warning"), tr("Loading image file failed!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}
	

	/*������ͼ��ߴ磺 
	6600*4400  ��С8������825*550
	4920*3280  ��С6������820*546   3280/6=546.66666
	*/
	ui.oriImageW->setText(QString::number(image.width(), 10));
	ui.oriImageH->setText(QString::number(image.height(), 10));

    if (image.width() == 6600)
    {
        //image = image.scaled(825, 550);//��ͼ̫��resizeһ��
        ui.resizeImageW->setText(QString::number(image.width(), 10));
        ui.resizeImageH->setText(QString::number(image.height(), 10));
    }
    else if (image.width() == 4920)
    {
        //image = image.scaled(820, 546);
        ui.resizeImageW->setText(QString::number(image.width(), 10));
        ui.resizeImageH->setText(QString::number(image.height(), 10));
    }
    else/*����ͼ��ߴ��Ҳ����һ�������С��*/
    {
        //image = image.scaled(825, 550);//��ͼ̫��resizeһ��
        ui.resizeImageW->setText(QString::number(image.width(), 10));
        ui.resizeImageH->setText(QString::number(image.height(), 10));

        //QMessageBox::information(NULL, tr("warning"), tr("The width of the image is not 6600 or 4920,we also resize it to the width of 820 pixels,please continue!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }


	/* static QPixmap fromImage(const QImage &image, Qt::ImageConversionFlags flags = Qt::AutoColor);
	fromImage()�������ص���QPixmap��������Ҫ��pixmap����ö���*/
    //pixmap = pixmap.fromImage(image);

    //ui.imageLable->setPixmap(pixmap);
    //ui.imageLable->show();
	

}



void chooseInsulator::mousePressEvent(QMouseEvent *event)
{
	if (event->pos().x() >= 440 && event->pos().x() <= 440 + 825 && event->pos().y() >= 70 && event->pos().y() <= 70+550)
	{
		mousepress_x = event->pos().x();
		mousepress_y = event->pos().y();
		//this->update();
	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("The mouse area is not in the image area!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}


}



void chooseInsulator::mouseMoveEvent(QMouseEvent *event)
{
	if (event->pos().x() >= 440 && event->pos().x() <= 440 + 825 && event->pos().y() >= 70 && event->pos().y() <= 70 + 550)
	{

		mousemove_x = event->pos().x();
		mousemove_y = event->pos().y();

		Rectw = abs(mousepress_x - mousemove_x);
		Recth = abs(mousepress_y - mousemove_y);

		QString pos = QString("topLeft=(%1,%2),width=%3,height=%4.").arg(mousepress_x).arg(mousepress_y).arg(Rectw).arg(Recth);
		//QString pos = QString("%1,%2").arg(event->pos().x() - 20).arg(event->pos().y() - 40);
		QToolTip::showText(event->globalPos(), pos, this);



		QString topleftPos = QString("(%1,%2)").arg(mousepress_x).arg(mousepress_y);
		ui.TopLeftLabel->setText(topleftPos);

		QString RectWShow = QString("%1").arg(Rectw);
		QString RectHShow = QString("%2").arg(Recth);

		ui.RectWLabel->setText(RectWShow);
		ui.RectHLabel->setText(RectHShow);

		this->update();
	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("The mouse area is not in the image area!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}


}

void chooseInsulator::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->pos().x() >= 440 && event->pos().x() <= 440 + 825 && event->pos().y() >= 70 && event->pos().y() <= 70 + 550)
	{

		mouserelease_x = event->pos().x();
		mouserelease_y = event->pos().y();


		insulatorX1.push_back(QString::number(mousepress_x-440, 10));
		insulatorY1.push_back(QString::number(mousepress_y-70, 10));
		insulatorX2.push_back(QString::number(mouserelease_x-440, 10));
		insulatorY2.push_back(QString::number(mouserelease_y-70, 10));


		//this->update();
	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("The mouse area is not in the image area!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}


}


void chooseInsulator::paintEvent(QPaintEvent *e)
{

	QPen pen;
	pen.setWidth(3);
	pen.setBrush(Qt::red);

	//QPainter painter(ui.imageLable);
	QPainter painter(this);
	painter.setPen(pen);

	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawImage(QPoint(440,70), image);

	QPoint x1(mousepress_x, mousepress_y);
	QPoint x2(mousemove_x, mousemove_y);
	QPoint x3(mouserelease_x, mouserelease_y);

	
	//painter.drawLine(x1, x2);
	//painter.drawLine(x1, x3);
	painter.drawRect(x1.rx(),x1.ry(), Rectw, Recth);


	//this->update();//��Ҫ��paintEvent()�����е���update()����repaint()

}


void chooseInsulator::on_nextImage_clicked()
{
	if (!srcDirPath.isEmpty())
	{
		QString result;
		result += imageName[imageNo];
		result += "\n";
		result += QString::number(image.width(), 10);
		result += "_";
		result += QString::number(image.height(), 10);
		result += "\n";
		if (insulatorX1.size() == 0)
		{
			result += "0";
			result += "_";
			result += "0";
			result += "_";
			result += "0";
			result += "_";
			result += "0";
			result += "\n";
		}
		else
		{
			for (int i = 0; i < insulatorX1.size(); i++)
			{
				result += insulatorX1[i];
				result += "_";
				result += insulatorY1[i];
				result += "_";
				result += insulatorX2[i];
				result += "_";
				result += insulatorY2[i];
				result += "\n";
			}
		}

		QString imageFilePath = srcDirPath + "/" + imageName[imageNo];

		QString resultSaveFileName = imageFilePath;
		resultSaveFileName.replace(QString("jpg"), QString("txt"));

		QFile data(resultSaveFileName);
		if (!data.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&data);

		out << result;

		data.close();
		result.clear();

		insulatorX1.clear();
		insulatorY1.clear();
		insulatorX2.clear();
		insulatorY2.clear();

		Rectw = 0;
		Recth = 0;
		mouserelease_x = 0;
		mouserelease_y = 0;
		mousepress_x = 0;
		mousepress_y = 0;


		if (currentImage < totalImage)
		{

			imageNo++;
			currentImage++;

			currentImageShow = QString::number(currentImage, 10);
			ui.imageNoLabel->setText(currentImageShow);

			QString imageFilePath = srcDirPath + "/" + imageName[imageNo];
			QPixmap pixmap;

			image.load(imageFilePath);


			ui.oriImageW->setText(QString::number(image.width(), 10));
			ui.oriImageH->setText(QString::number(image.height(), 10));
            ui.resizeImageW->setText(QString::number(image.width(), 10));
            ui.resizeImageH->setText(QString::number(image.height(), 10));

			this->update();
		}
		else if (currentImage == totalImage)
		{

		}
		else
		{
			QMessageBox::information(NULL, tr("warning"), tr("This is the last image!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		}
	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("Directory folder not selected!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	}


}


void chooseInsulator::on_upperImage_clicked()
{
	if (!srcDirPath.isEmpty())
	{
		if (currentImage > 1)
		{
			imageNo--;
			currentImage--;

			currentImageShow = QString::number(currentImage, 10);

			ui.imageNoLabel->setText(currentImageShow);

			QString imageFilePath = srcDirPath + "/" + imageName[imageNo];
			QPixmap pixmap;

			image.load(imageFilePath);

			ui.oriImageW->setText(QString::number(image.width(), 10));
			ui.oriImageH->setText(QString::number(image.height(), 10));

            ui.resizeImageW->setText(QString::number(image.width(), 10));
            ui.resizeImageH->setText(QString::number(image.height(), 10));

			Rectw = 0;
			Recth = 0;
			mouserelease_x = 0;
			mouserelease_y = 0;
			mousepress_x = 0;
			mousepress_y = 0;
			this->update();
		}
		else
		{
			QMessageBox::information(NULL, tr("warning"), tr("This is the first image!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		}

	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("Directory folder not selected!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	}



}



void chooseInsulator::keyPressEvent(QKeyEvent *event)
{
	if (!srcDirPath.isEmpty())
	{
		QString result;
		result += imageName[imageNo];
		result += "\n";
		result += QString::number(image.width(), 10);
		result += "_";
		result += QString::number(image.height(), 10);
		result += "\n";
		if (insulatorX1.size() == 0)
		{
			result += "0";
			result += "_";
			result += "0";
			result += "_";
			result += "0";
			result += "_";
			result += "0";
			result += "\n";
		}
		else{
			for (int i = 0; i < insulatorX1.size(); i++)
			{
				result += insulatorX1[i];
				result += "_";
				result += insulatorY1[i];
				result += "_";
				result += insulatorX2[i];
				result += "_";
				result += insulatorY2[i];
				result += "\n";
			}
		}

		QString imageFilePath = srcDirPath + "/" + imageName[imageNo];
		QString resultSaveFileName = imageFilePath;
		resultSaveFileName.replace(QString("jpg"), QString("txt"));

		QFile data(resultSaveFileName);
		if (!data.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&data);

		out << result;

		data.close();

		result.clear();
		insulatorX1.clear();
		insulatorY1.clear();
		insulatorX2.clear();
		insulatorY2.clear();


		Rectw = 0;
		Recth = 0;
		mouserelease_x = 0;
		mouserelease_y = 0;
		mousepress_x = 0;
		mousepress_y = 0;

		if (currentImage < totalImage)
		{
			if (event->key() == Qt::Key_Return)
			{
				imageNo++;
				currentImage++;

				currentImageShow = QString::number(currentImage, 10);

				ui.imageNoLabel->setText(currentImageShow);

				QString imageFilePath = srcDirPath + "/" + imageName[imageNo];
				QPixmap pixmap;

				image.load(imageFilePath);



				ui.oriImageW->setText(QString::number(image.width(), 10));
				ui.oriImageH->setText(QString::number(image.height(), 10));

                ui.resizeImageW->setText(QString::number(image.width(), 10));
                ui.resizeImageH->setText(QString::number(image.height(), 10));



				this->update();
			}
			else
			{
				//QMessageBox::information(NULL, tr("warning"), tr("Please press Enter to process the next image"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

			}
		}
		else
		{
			QMessageBox::information(NULL, tr("warning"), tr("This is the last image!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		}
	}
	else
	{
		QMessageBox::information(NULL, tr("warning"), tr("Directory folder not selected!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	}

}

void chooseInsulator::on_actionOpen_triggered()
{
	helper = new help();
	helper->show();
}

