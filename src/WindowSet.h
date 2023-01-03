#pragma once

#include <QWidget>
#include <QJsonObject > // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include <QFile>
#include <QFileInfo>

#include "ui_WindowSet.h"
// #include "WinowMain.h"



QT_BEGIN_NAMESPACE
namespace Ui { class WindowSetClass; };
QT_END_NAMESPACE

// extern QJsonObject rootObj;

class WindowSet : public QWidget
{
	Q_OBJECT

public:
	WindowSet(QWidget *parent = nullptr);
	~WindowSet();
	QTreeWidgetItem* pCurrentset;

signals:


public slots:
	void lineEdit_set();
	void read_json();
	void create_json();
	void change_json();
	void save_json();

private:
	Ui::WindowSetClass *ui;
	void init();

};
