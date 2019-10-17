#include "MqttDemo.h"

MqttDemo::MqttDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MqttDemo::on_ConnectControlButton_clicked()
{
	QString ip = this->ui.IpEdit->text();
	QString port = this->ui.PortEdit->text();
	this->IpAdress = ip.append(port).toStdString();
	this->ClientId = this->ui.ClientIdEdit->text().toStdString();
	this->async_client_ = new async_client(this->IpAdress,this->ClientId);
	
}

void MqttDemo::on_SubscribeButton_clicked()
{
}

void MqttDemo::on_SendButton_clicked()
{
}
