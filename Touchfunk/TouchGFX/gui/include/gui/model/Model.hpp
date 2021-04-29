#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void show(uint8_t number);
    void AdminCenterScreenButtonClicked(short int button);
    void StandartScreenButtonClicked(int button);
    void showMSG(short int newText);
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
