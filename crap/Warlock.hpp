#pragma once

#include <iostream>
#include <string>
#include <list>

class ASpell;
class ATarget;

class Warlock {
  private:
    std::string name;
    std::string title;
    std::list<ASpell *> spellbook;

    Warlock();
    Warlock& operator=(const Warlock& other);

  public:
    Warlock(const Warlock& other);
    const std::string& getName() const;
    const std::string& getTitle() const;

    void setTitle(const std::string& title);
    void introduce() const;

    Warlock(std::string name, std::string title);
    ~Warlock();

    void learnSpell(ASpell* spell);
    void forgetSpell(std::string spellname);
    void launchSpell(std::string spellname, ATarget& target);
};