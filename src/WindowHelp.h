#pragma once

#include <QWidget>
#include "ui_WindowHelp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WindowHelpClass; };
QT_END_NAMESPACE

class WindowHelp : public QWidget
{
	Q_OBJECT

public:
	WindowHelp(QWidget *parent = nullptr);
	~WindowHelp();

public slots:
	void open_url();

private:
	Ui::WindowHelpClass *ui;
	void init();
};
