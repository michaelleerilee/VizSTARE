/*
 * VizSTARE.h
 *
 *  Created on: Feb 7, 2019
 *      Author: mrilee
 *
 *  Copyright (C) 2019 Rilee Systems Technologies LLC
 */

#ifndef VIZSTARE_H_
#define VIZSTARE_H_

#include <iostream>


#include <QtOpenGL/QGL>
#include <QtGui/QImage>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
//#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
// #include <Inventor/nodes/SoSwitch.h>



class VizSTARE {

public:
	VizSTARE();
	virtual ~VizSTARE();

	float lineWidth = -1;

	SoSeparator* makeRoot();
	SoSeparator* makeSphere(double radius = 1);
};


#endif /* VIZSTARE_H_ */
