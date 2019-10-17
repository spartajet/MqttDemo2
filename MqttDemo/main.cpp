#include "MqttDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MqttDemo w;
	w.show();
	return a.exec();
}
