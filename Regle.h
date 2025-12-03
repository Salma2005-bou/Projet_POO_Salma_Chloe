class Regle {
public:
    virtual bool devraitEtreAppliquee(bool etatActuel,int voisinsVivants)  = 0;
    virtual ~Regle() {}
};
class RegleConway : public Regle {
public:
        bool devraitEtreAppliquee(bool etatActuel,int voisinsVivants) override {
    if (etatActuel) {
        if (voisinsVivants < 2 || voisinsVivants > 3) {
            return false; 
        } else {
            return true;  
        }
    } else {
        return (voisinsVivants == 3); // vivante si exactement 3 voisins
    }
}
};