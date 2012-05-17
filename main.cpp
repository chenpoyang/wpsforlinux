#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

#include "wwidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	WWidget wwidget;
	wwidget.show();

	return app.exec();
	return 0;
}
