#include "Warlock.hpp"
#include "ASpell.hpp"
#include "ATarget.hpp"

const std::string& Warlock::getName() const {
  return name;
}

const std::string& Warlock::getTitle() const {
  return title;
}

void Warlock::setTitle(const std::string& tit) {
  this->title = tit;
}

void Warlock::introduce() const {
  std::cout << this->getName() << ": I am " << this->getName() << ", " << this->getTitle() << "!" << std::endl;
}

Warlock::Warlock(std::string name, std::string title): name(name), title(title) {
  std::cout << this->getName() << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
  std::cout << this->getName() << ": My job here is done!" << std::endl;
  for (std::list<ASpell*>::iterator it = spellbook.begin(); it != spellbook.end(); it++) {
    delete *it;
  }
}

void Warlock::learnSpell(ASpell* spell) {
  if (spell) {
    std::list<ASpell*>::iterator it = spellbook.begin();
    while (it != spellbook.end()) {
      if ((*it)->getName() == spell->getName()) return;
      it++;
    }
    spellbook.push_back(spell->clone());
    }
}

void Warlock::forgetSpell(std::string spellname) {
  std::list<ASpell*>::iterator it = spellbook.begin();
  while (it != spellbook.end()) {
    if ((*it)->getName() == spellname) {
      delete *it;
      spellbook.erase(it);
      return;
    }
    it++;
  }
}

void Warlock::launchSpell(std::string spellname, ATarget& target) {
  std::list<ASpell*>::iterator it = spellbook.begin();
  while (it != spellbook.end()) {
    if ((*it)->getName() == spellname) {
      (*it)->launch(target);
    }
    it++;
  }
}

Warlock::Warlock() {}

Warlock& Warlock::operator=(const Warlock& other) {
  (void)other;
  return *this;
}

Warlock::Warlock(const Warlock& other) {
  *this = other;
}