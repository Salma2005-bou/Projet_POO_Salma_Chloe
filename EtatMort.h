#pragma once
#include "EtatCellule.h"

class EtatMort : public EtatCellule {
public:
    bool estVivante() override {
        return false;
    }
};
