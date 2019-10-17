#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MqttDemo.h"

class MqttDemo : public QMainWindow
{
	Q_OBJECT

public:
	MqttDemo(QWidget *parent = Q_NULLPTR);

private:
	Ui::MqttDemoClass ui;
};
