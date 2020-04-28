/*
 * VizSTARE_TestIntervals.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: mrilee
 *
 *  Copyright (C) 2019 Rilee Systems Technologies LLC
 */




#include "VizSTARE.h"
#include "VizSTARE_TestIntervals.h"

#include <QtOpenGL/QGL>
#include <QtGui/QImage>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
//#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
//#include <Inventor/nodes/SoOrthographicCamera.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoDirectionalLight.h>

using namespace std;

int main(int argc, char **argv) {
	cout << "Hello world. Again.";

	VizSTARE viz;

	const int width = 2000, height = 1400;
	QWidget *window = SoQt::init(argv[0]);
	window->setMinimumSize(width,height);
	if (window == NULL) exit(1);


	SoSeparator* root = viz.makeRoot();

    SoDirectionalLight * light = new SoDirectionalLight;
    root->addChild(light);

    SoPerspectiveCamera *camera = new SoPerspectiveCamera;
	camera->pointAt(SbVec3f(0.,0.,0.));
    camera->nearDistance = 0.0001;

    root->addChild(camera); // perscam

	root->addChild(viz.makeSphere());

	SoQtExaminerViewer *viewer = new SoQtExaminerViewer(window);
	viewer->setSceneGraph(root);
	viewer->show();

	// window->windowTitle().clear();
	window->setWindowTitle(argv[0]);

	SoQt::show(window);
	SoQt::mainLoop();

	delete viewer;
	//	root->unref();
	return 0;
}
