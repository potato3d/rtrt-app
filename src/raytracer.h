#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QtGui/QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include "ui_raytracer.h"
#include "Canvas.h"

class raytracer : public QMainWindow
{
    Q_OBJECT

public:
    raytracer(QWidget *parent = 0, Qt::WFlags flags = 0);

protected slots:
	virtual void keyPressEvent( QKeyEvent* e );
	void updateFps( double fps );

private:
    Ui::raytracerClass ui;
	Canvas* _canvas;
	QLabel* _fpsLabel;
	QLabel* _raysPerSecond;
};

#endif // RAYTRACER_H
