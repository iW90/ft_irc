#include "ASpell.hpp"
#include "ATarget.hpp"

const std::string& ATarget::getType() const {
    return type;
}

ATarget::Atarget(std::string type): type(type) {}

void ATarget::getHitBySpell(const ASpell& spell) const {
    std::cout << this->getType() << " has been " << spell.getEffects() << "!" << std::endl;
}

ATarget::~ATarget() {}

ATarget& ATarget::operator=(const ATarget& other) {
    (void)other;
    return *this;    
}

ATarget::ATarget(const ATarget& other) {
    *this = other;
}