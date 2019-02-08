
#include "VizSTARE.h"

using namespace std;

VizSTARE::VizSTARE() { }

VizSTARE::~VizSTARE() { }

SoSeparator* VizSTARE::makeRoot() {

	SoSeparator *root = new SoSeparator;

	if(lineWidth != -1) {
		SoDrawStyle *style = new SoDrawStyle;
		style->lineWidth.setValue(lineWidth);
		root->addChild(style);
	}

	// root->unrefNoDelete();
	return root;

}

SoSeparator* VizSTARE::makeSphere(double radius) {

	SoSeparator *sphereNode = new SoSeparator;

	SoSphere *sp = new SoSphere();
	sp->radius = radius;
	sphereNode->addChild(sp);

	return sphereNode;

}


