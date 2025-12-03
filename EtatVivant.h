#pragma once
#include "EtatCellule.h"

class EtatVivant : public EtatCellule {
public:
    bool estVivante() override {
        return true;
    }
};
