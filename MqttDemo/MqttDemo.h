#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MqttDemo.h"
#include "mqtt/async_client.h"

class MqttDemo : public QMainWindow
{
	Q_OBJECT

public:
	MqttDemo(QWidget *parent = Q_NULLPTR);

private:
	Ui::MqttDemoClass ui;
	void on_ConnectControlButton_clicked();
	void on_SubscribeButton_clicked();
	void on_SendButton_clicked();
};
