#include <gl/glew.h>

#include "Canvas.h"

#include <gl/glut.h>

#include <QKeyEvent>
#include <QMessageBox>

#include <rt/rt.h>

#include <rtu/float3.h>
#include <rtu/quat.h>
#include <rtut/rtut.h>

#include <rtl/Headlight.h>
#include <rtl/DepthMaterial.h>
#include <rtl/SimplePointLight.h>
#include <rtl/SimpleAreaLight.h>
#include <rtl/PhongMaterial.h>
#include <rtl/Texture2D.h>

#include <rtl/SingleRenderer.h>
#include <rtl/MultiThreadRenderer.h>
#include <rtl/JitteredRenderer.h>
#include <rtl/AdaptiveRenderer.h>
#include <rtl/TiledRenderer.h>
#include <rtl/PacketTiledRenderer.h>

#include <iostream>
#include <string.h>

Canvas::Canvas( QWidget* parent )
: QGLWidget( QGLFormat( QGL::NoDepthBuffer ), parent ),	_frameCounter( 0 ), _cameraMoveSpeed( 0.05f ), 
	  _cameraRotateSpeed( 0.01f ), _texId( 0 ),  _pboId( 0 )
{
	setFocusPolicy( Qt::StrongFocus );
}

Canvas::~Canvas()
{
	if( _pboId > 0 )
		glDeleteBuffers( 1, &_pboId );

	if( _texId > 0 )
		glDeleteTextures( 1, &_texId );
}

/************************************************************************/
/* Protected                                                            */
/************************************************************************/
void Canvas::initializeGL()
{
	glewInit();

	// Initialize ray tracing context
	bool ok = rtInit();
	if( !ok )
	{
		// Show error message
		int ret = QMessageBox::critical( this, tr( "RTRT" ),
			tr( "Error initializing ray tracing library." ),
			QMessageBox::Ok );
		exit( 1 );
	}

	if( !glewIsExtensionSupported( "GL_ARB_pixel_buffer_object" ) )
	{
		// Show error message
		int ret = QMessageBox::critical( this, tr( "RTRT" ),
			tr( "This application needs Pixel Buffer Object extension to work." ),
			QMessageBox::Ok );
		exit( 1 );
	}

	// General setup
	//rtSetMaxRayRecursionDepth( 3 );

	// Lights
	rtl::SimplePointLight* light = new rtl::SimplePointLight();
	//rtl::SimpleAreaLight* light = new rtl::SimpleAreaLight();
	//light->setPosition( 5.0f, 10.0f, 0.0f );
	light->setPosition( 500.0f, 1000.0f, 500.0f );
	light->setConstantAttenuation( 1.0f );
	light->setLinearAttenuation( 0.0f );
	light->setQuadraticAttenuation( 0.0f );
	//light->setCastShadows( false );

	unsigned int lightId = rtGenLights( 1 );
	rtBindLight( lightId );
	rtLightClass( light );

	//// Textures
	//rtl::Texture2D* texture2d = new rtl::Texture2D();

	//GLuint texId = rtGenTextures( 1 );
	//rtBindTexture( texId );
	//rtTextureClass( texture2d );
	//rtTextureParameter( RT_TEXTURE_FILTER, (void*)( RT_NEAREST ) );
	//rtTextureParameter( RT_TEXTURE_WRAP_S, (void*)( RT_CLAMP ) );
	//rtTextureParameter( RT_TEXTURE_WRAP_T, (void*)( RT_CLAMP ) );
	//rtTextureParameter( RT_TEXTURE_ENV_MODE, (void*)( RT_MODULATE ) );

	//unsigned int imgWidth;
	//unsigned int imgHeight;
	//unsigned char* data = loadTexture( "redbricks.jpg", imgWidth, imgHeight );
	//rtTextureImage2D( imgWidth, imgHeight, data );
	//delete [] data;

	// Materials
	rtl::Headlight* mat = new rtl::Headlight();
	//rtl::DepthMaterial* mat = new rtl::DepthMaterial();
	//rtl::PhongMaterial* mat = new rtl::PhongMaterial();
	//mat->setOpacity( 0.2f );
	//mat->setRefractionIndex( 1.1f );
	//mat->setReflexCoeff( 0.4f );

	unsigned int materialId = rtGenMaterials( 1 );
	rtBindMaterial( materialId );
	rtMaterialClass( mat );
	//rtMaterialParameter( RT_TEXTURE_ID, &texId );

	// Geometries
	unsigned int geometryId;
	geometryId = rtGenGeometries( 1 );
	rtNewGeometry( geometryId );
	rtColor3f( 0.0f, 0.0f, 1.0f );

	//rtPushMatrix();
		//rtScalef( 10.0f, 10.0f, 10.0f );
		//rtutTeapot();
	//rtPopMatrix();

	//rtNormal3f( 0.0f, 0.0f, 1.0f );
	//rtBegin( RT_TRIANGLES );
	//rtVertex3f( 0.0f, 0.0f, 0.0f );
	//rtVertex3f( 1.0f, 0.0f, 0.0f );
	//rtVertex3f( 0.0f, 1.0f, 0.0f );
	//rtEnd();

	//rtNormal3f( 0.0f, 0.0f, 1.0f );
	//rtBegin( RT_TRIANGLES );
	//rtVertex3f( 0.0f, 0.0f, 1.0f );
	//rtVertex3f( 1.0f, 0.0f, 0.0f );
	//rtVertex3f( 0.0f, 1.0f, 0.0f );

	//rtVertex3f( 2.0f, 0.0f, 0.0f );
	//rtVertex3f( 3.0f, 0.0f, 1.0f );
	//rtVertex3f( 2.0f, 1.0f, 0.0f );
	//rtEnd();

	rtutCube();
	//rtutSphere( 16, 16 );
	//rtutLogo();

  //  rtPushMatrix();
		//rtColor3f( 0.0f, 1.0f, 0.0f );
		//rtScalef( 100.0f, 0.5f, 100.0f );
		//rtTranslatef( 0.0f, -2.0f, 0.0f );
		//rtutCube();
  //  rtPopMatrix();

	//ok = rtutLoadOpenSceneGraph( "c:/projects/environ/models/p40.ive", geometryId );
	//ok = rtutLoadOpenSceneGraph( "c:/projects/environ/models/boat.ive", geometryId );

	//ok = rtutLoadRa2( "scene6.ra2" );
	//ok = rtutLoadRa2( "clown.ra2" );
	//ok = rtutLoadRa2( "kitchenTransformed.ra2" );
	//ok = rtutLoadRa2( "FairyForestF160.ra2" );
	//ok = rtutLoadRa2( "happy_buddha_vrip.ra2" );
	//ok = rtutLoadRa2( "MengerSponge_scaled_cubes.ra2" );

	if( !ok )
		exit( 1 );

	//rtNormal3f( 0.0f, 0.0f, 1.0f );
	//rtColor3f( 0.0f, 0.0f, 1.0f );

	//rtBegin( RT_TRIANGLES );
	//rtTexCoord2f( 0.0f, 0.0f );
	//rtVertex3f( 0.0f, 0.0f, 0.0f );
	//rtTexCoord2f( 1.0f, 0.0f );
	//rtVertex3f( 1.0f, 0.0f, 0.0f );
	//rtTexCoord2f( 0.0f, 1.0f );
	//rtVertex3f( 0.0f, 1.0f, 0.0f );
	//rtEnd();

	//createSphere( rtu::float3( 0.0f, 0.0f, 0.0f), 2, 64, 64, "../data/redbricks.jpg" );

	rtEndGeometry();

	// Instances
	rtLoadIdentity();
	unsigned int instanceId = rtGenInstances( 1 );
	rtInstantiate( instanceId, geometryId );
	
	// Camera setup
	rtPerspective( 60.0f, 1.0f, 100.0f );
	//rtLookAt( 0.0f, 1.0f, 35.0f, 
	//rtLookAt( 0.0f, 1.0f, 135.0f, 
	rtLookAt( 0.0f, 1.0f, 5.0f, 
			  0.0f, 1.0f, 0.0f, 
			  0.0f, 1.0f, 0.0f );

	rtViewport( width(), height() );

	// PBO setup
	glGenBuffers( 1, &_pboId );

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &_texId );
	glBindTexture( GL_TEXTURE_2D, _texId );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	// TODO: supersampling with texture filtering
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	_timer.restart();
	startTimer( 0 );
}

void Canvas::resizeGL( int w, int h )
{
	glViewport( 0, 0, w, h );

	// TODO: supersampling with texture filtering
	int sw = w;// * 2;
	int sh = h;// * 2;

	rtViewport( sw, sh );

	// Reallocate texture and buffer object
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, _pboId );
	glBufferData( GL_PIXEL_UNPACK_BUFFER_ARB, sw*sh*3*sizeof(float), NULL, GL_STREAM_DRAW );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, sw, sh, 0, GL_RGB, GL_FLOAT, NULL );
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, 0 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0.0, w, 0.0, h );
}

void Canvas::paintGL()
{
	++_frameCounter;

	int w = width();
	int h = height();

	// TODO: supersampling with texture filtering
	int sw = w;// * 2;
	int sh = h;// * 2;

	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, _pboId );
	void* deviceMem = glMapBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY );

	rtFrameBuffer( static_cast<float*>( deviceMem ) );
	rtRenderFrame();

	glUnmapBuffer( GL_PIXEL_UNPACK_BUFFER_ARB );
	glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, sw, sh, GL_RGB, GL_FLOAT, NULL );
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, 0 );

	glBegin(GL_QUADS);
		glTexCoord2f( 0.0f, 0.0f ); glVertex2f( 0.0f, 0.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex2f(    w, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex2f(    w,    h );
		glTexCoord2f( 0.0f, 1.0f ); glVertex2f( 0.0f,    h );
	glEnd();

	double elapsed = _timer.elapsed();
	if( elapsed >= 1.0 )
	{
		emit updateFps( _frameCounter / elapsed );
		_frameCounter = 0;
		_timer.restart();
	}
}

/************************************************************************/
/* Slots                                                                */
/************************************************************************/
void Canvas::timerEvent( QTimerEvent* e )
{
	updateGL();
}

void Canvas::keyPressEvent( QKeyEvent* e )
{
	switch( e->key() )
	{
	case Qt::Key_1:
		rtRendererClass( new rtl::SingleRenderer() );
		break;

	case Qt::Key_2:
		rtRendererClass( new rtl::MultiThreadRenderer() );
		break;

	case Qt::Key_3:
		rtRendererClass( new rtl::TiledRenderer() );
		break;

	case Qt::Key_4:
		rtRendererClass( new rtl::PacketTiledRenderer() );
		break;

	case Qt::Key_5:
		rtRendererClass( new rtl::JitteredRenderer() );
		break;

	case Qt::Key_6:
		rtRendererClass( new rtl::AdaptiveRenderer() );
		break;

	case Qt::Key_Space:
		// Reset viewer
		rtLookAt( 0.0f, 1.0f, 5.0f, 
			      0.0f, 1.0f, 0.0f, 
			      0.0f, 1.0f, 0.0f );
		break;

	case Qt::Key_Comma:
		rtSetRayEpsilon( rtGetRayEpsilon() - 1e-4f );
		if( rtGetRayEpsilon() < 0.0f )
			rtSetRayEpsilon( 1e-4f );
		break;

	case Qt::Key_Period:
		rtSetRayEpsilon( rtGetRayEpsilon() + 1e-4f );
		break;

	// Animated object control
	case Qt::Key_I:
		rtPushMatrix();
		rtLoadMatrixfv( rtGetInstanceTransform( 1 ) );
		rtTranslatef( 0.1f, 0.0f, 0.0f );

		rtInstantiate( 1, 1 );

		rtPopMatrix();
		break;

	case Qt::Key_K:
		rtPushMatrix();
		rtLoadMatrixfv( rtGetInstanceTransform( 1 ) );
		rtTranslatef( -0.1f, 0.0f, 0.0f );

		rtInstantiate( 1, 1 );

		rtPopMatrix();
		break;

	default:
		e->ignore();
	    return;
	}

	// Update state
	e->accept();
	updateGL();
}

void Canvas::mousePressEvent( QMouseEvent* e )
{
	_previousMousePos = e->globalPos();
	e->accept();
}

void Canvas::mouseMoveEvent( QMouseEvent* e )
{
	int dx = e->globalPos().x() - _previousMousePos.x();
	int dy = e->globalPos().y() - _previousMousePos.y();
	Qt::MouseButtons buttonMask = e->buttons();

	if( buttonMask & Qt::LeftButton )
	{
		// Rotate in Y axis
		float angle = -dx * _cameraRotateSpeed;
		rtCameraParameter( RT_ROTATE_Y, &angle );

		// Rotate in X axis
		angle = -dy * _cameraRotateSpeed;
		rtCameraParameter( RT_ROTATE_X, &angle );
	}
	else if( buttonMask & Qt::RightButton )
	{
		// Translate in X axis
		rtCameraParameter( RT_TRANSLATE, &rtu::float3( dx * _cameraMoveSpeed, 0.0f, 0.0f ) );

		// Translate in Y axis
		rtCameraParameter( RT_TRANSLATE, &rtu::float3( 0.0f, -dy * _cameraMoveSpeed, 0.0f ) );
	}
	else if( buttonMask & Qt::MidButton )
	{
		// Translate in Z axis
		rtCameraParameter( RT_TRANSLATE, &rtu::float3( 0.0f, 0.0f, -dy * _cameraMoveSpeed ) );
	}
	else
	{
		e->ignore();
		return;
	}

	// Update state
	_previousMousePos = e->globalPos();
	e->accept();
	updateGL();
}

unsigned char* Canvas::loadTexture( const std::string& filename, unsigned int& width, unsigned int& height )
{
	QImage q( filename.c_str() );
	if( q.isNull() )
		return 0;

	width = q.width();
	height = q.height();

	unsigned char* data = new unsigned char[q.width()*q.height()*3];
	unsigned int dest = 0;
	for( unsigned int h = 0; h < q.height(); ++h )
	{
		for( unsigned int w = 0; w < q.width(); ++w )
		{
			QRgb p = q.pixel( w, h );
			data[dest++] = qRed( p );
			data[dest++] = qGreen( p );
			data[dest++] = qBlue( p );
		}
	}

	return data;
}

void Canvas::createSphere( const rtu::float3& pos, unsigned int radius, unsigned int slices, unsigned int stacks, char* texFile /*= 0 */ )
{
	// creating texture
	if( texFile )
	{
		rtl::Texture2D* texture2d = new rtl::Texture2D();

		GLuint texId = rtGenTextures( 1 );
		rtBindTexture( texId );
		rtTextureClass( texture2d );
		rtTextureParameter( RT_TEXTURE_FILTER, (void*)( RT_NEAREST ) );
		rtTextureParameter( RT_TEXTURE_WRAP_S, (void*)( RT_CLAMP ) );
		rtTextureParameter( RT_TEXTURE_WRAP_T, (void*)( RT_CLAMP ) );
		rtTextureParameter( RT_TEXTURE_ENV_MODE, (void*)( RT_MODULATE ) );

		unsigned int imgWidth;
		unsigned int imgHeight;
		unsigned char* data = loadTexture( texFile, imgWidth, imgHeight );
		rtTextureImage2D( imgWidth, imgHeight, data );
		delete [] data;

		// Creating Material
		rtl::PhongMaterial* mat = new rtl::PhongMaterial();
		//mat->setOpacity( 0.2f );
		//mat->setRefractionIndex( 1.1f );
		//mat->setReflexCoeff( 0.4f );

		unsigned int materialId = rtGenMaterials( 1 );
		rtBindMaterial( materialId );
		rtMaterialClass( mat );
		rtMaterialParameter( RT_TEXTURE_ID, &texId );
	}

	rtPushMatrix();
		rtScalef( radius, radius, radius );
		rtTranslatef( pos.x, pos.y, pos.z );
		rtutSphere( slices, stacks );
	rtPopMatrix();
}
