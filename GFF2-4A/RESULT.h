#pragma once
#include "AbstractScene.h"

class RESULT : public AbstractScene
{
private:
	int background_image;
	int timer;

public:
	RESULT();
	~RESULT();
	AbstractScene* Update() override;
	void Draw() const override;
};

