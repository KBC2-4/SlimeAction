#pragma once
#include "AbstractScene.h"

class RESULT : public AbstractScene
{
private:

	int background_image;

public:
	RESULT();
	AbstractScene* Update() override;
	virtual void Draw() const override;
};

