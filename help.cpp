#include "help.h"

help::help(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

help::~help()
{
}

void help::on_ReturnOK_clicked()
{
	this->close();
}