#pragma once
#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <QtOpenGL/QGLWidget>

#include <rtu/Timer.h>
#include <rtu/float3.h>

class Canvas : public QGLWidget
{
	Q_OBJECT

public:
	Canvas( QWidget* parent );
	~Canvas();

signals:
	void updateFps( double fps );

protected:
	virtual void initializeGL();
	virtual void resizeGL( int w, int h );
	virtual void paintGL();

protected slots:
	virtual void timerEvent( QTimerEvent* e );
	virtual void keyPressEvent( QKeyEvent* e );
	virtual void mousePressEvent( QMouseEvent* e );
	virtual void mouseMoveEvent( QMouseEvent* e );

private:
	rtu::Timer _timer;
	unsigned int _frameCounter;

	unsigned int _texId;

	unsigned int _pboId;

	float _cameraMoveSpeed;
	float _cameraRotateSpeed;
	QPoint _previousMousePos;

	unsigned char* loadTexture( const std::string& filename, unsigned int& width, unsigned int& height );
	void createSphere( const rtu::float3& pos, unsigned int radius, unsigned int slices, unsigned int stacks, char* texFile = 0 );
};

#endif
