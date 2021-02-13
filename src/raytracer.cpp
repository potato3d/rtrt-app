#include "raytracer.h"

raytracer::raytracer( QWidget *parent, Qt::WFlags flags )
: QMainWindow( parent, flags ), _canvas( new Canvas( this ) ), _fpsLabel( new QLabel( QString::number( 0.0 ), this ) )//,
// TODO: //_raysPerSecond( new QLabel( QString::number( 0.0 ), this ) )
{
	ui.setupUi( this );
	_fpsLabel->setFixedWidth( 80 );
	_fpsLabel->setAlignment( Qt::AlignRight );
	// TODO: 
	//_raysPerSecond->setFixedWidth( 120 );
	//_raysPerSecond->setAlignment( Qt::AlignRight );
	ui.statusBar->addPermanentWidget( _fpsLabel );
	// TODO: correct primary, secondary, shadow ray counters
	//ui.statusBar->addPermanentWidget( _raysPerSecond );
	setCentralWidget( _canvas );
	connect( _canvas, SIGNAL( updateFps( double ) ), this, SLOT( updateFps( double ) ) );

	// Hide stupid context menu to show/hide main toolbar.
	setContextMenuPolicy( Qt::NoContextMenu );
}

void raytracer::keyPressEvent( QKeyEvent* e )
{
	if( e->key() == Qt::Key_Escape )
		close();
	else
		e->ignore();
}

void raytracer::updateFps( double fps )
{
	_fpsLabel->setText( QString::number( fps, 'g', 4 ) + " fps" );
	// TODO: correct primary, secondary, shadow ray counters
	//_raysPerSecond->setText( QString::number( fps * _canvas->width() * _canvas->height(), 'g', 3 ) + " ray/s" );
}