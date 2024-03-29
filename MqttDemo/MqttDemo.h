#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MqttDemo.h"
#include "mqtt/async_client.h"
#include "mqtt/types.h"

using namespace std;
using namespace mqtt;

class MqttCallback;
class action_listener;
class delivery_action_listener;

class MqttDemo : public QMainWindow
{
Q_OBJECT

public:
	MqttDemo(QWidget* parent = Q_NULLPTR);

private:
	Ui::MqttDemoClass ui;
	std::string Topic = "";
	std::string IpAdress = "";
	std::string ClientId = "";
	mqtt::async_client *async_client_=nullptr;
	// int TIMEOUT = std::chrono::seconds(10);
public slots:
	void on_ConnectControlButton_clicked();
	void on_SubscribeButton_clicked();
	void on_SendButton_clicked();
};

class MqttCallback : public virtual mqtt::callback
{
public:
	void connection_lost(const string& cause) override
	{
		cout << "\nConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override
	{
		cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
	}
};
/**
 * A base action listener.
 */
class action_listener : public virtual iaction_listener
{
protected:
	void on_failure(const mqtt::token& tok) override {
		cout << "\tListener failure for token: "
			<< tok.get_message_id() << endl;
	}

	void on_success(const mqtt::token& tok) override {
		cout << "\tListener success for token: "
			<< tok.get_message_id() << endl;
	}
};

/**
 * A derived action listener for publish events.
 */
class delivery_action_listener : public action_listener
{
	atomic<bool> done_;

	void on_failure(const mqtt::token& tok) override {
		action_listener::on_failure(tok);
		done_ = true;
	}

	void on_success(const mqtt::token& tok) override {
		action_listener::on_success(tok);
		done_ = true;
	}

public:
	delivery_action_listener() : done_(false) {}
	bool is_done() const { return done_; }
};
