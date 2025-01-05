#include "ASpell.hpp"
#include "ATarget.hpp"

const std::string& ASpell::getName() const {
    return name;
}

const std::string& ASpell::getEffects() const {
    return effects;
}

ASpell::ASpell(std::string name, std::string effects): name(name), effects(effects) {}

void ASpell::launch(const ATarget& target) const {
    target.getHitBySpell(*this);
}

ASpell::~ASpell() {}

ASpell::ASpell() {}

ASpell& ASpell::operator=(const ASpell& other) {
    (void) other;
    return *this;
}

ASpell::ASpell(const ASpell& other) {
    *this = other;
}