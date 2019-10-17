#include "MqttDemo.h"

MqttDemo::MqttDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MqttDemo::on_ConnectControlButton_clicked()
{
	if (this->ui.ConnectControlButton->text()=="Connect")
	{
		QString ip = this->ui.IpEdit->text();
		QString port = this->ui.PortEdit->text();
		this->IpAdress = QString("tcp://").append(ip.append(":").append(port)).toStdString();
		this->ClientId = this->ui.ClientIdEdit->text().toStdString();
		this->async_client_ = new async_client(this->IpAdress, this->ClientId);
		mqtt::connect_options options;
		options.set_keep_alive_interval(20);
		options.set_clean_session(true);
		options.set_user_name("df");
		options.set_password("df");
		MqttCallback cb;
		// this->async_client_->set_callback(cb);
		try
		{
			cout << "\nConnecting..." << endl;
			token_ptr conntok = this->async_client_->connect(options);
			cout << "Waiting for the connection..." << endl;
			conntok->wait();
			cout << "  ...OK" << endl;
			this->ui.ConnectControlButton->setText("DisConnect");
		}
		catch (const mqtt::exception& exc)
		{
			cerr << exc.what() << endl;
		}
	}
	else
	{
		this->async_client_->disconnect();
		this->async_client_ = nullptr;
		this->ui.ConnectControlButton->setText("Connect");

	}
}

void MqttDemo::on_SubscribeButton_clicked()
{
	std::string topic = this->ui.TopicEdit->text().toStdString();
	this->async_client_->subscribe(topic,0);
}

void MqttDemo::on_SendButton_clicked()
{
	std::string topic = this->ui.TopicEdit->text().toStdString();
	std::string payload = this->ui.SendMessageEdit->text().toStdString();
	mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
	pubmsg->set_qos(0);
	this->async_client_->publish(pubmsg)->wait_for(1000);
}
