#pragma once

class ASpell;

class Fwoosh: public ASpell {
  public:
    Fwoosh();
    Fwoosh& operator=(const Fwoosh& other);
    Fwoosh(const Fwoosh& other);

    ~Fwoosh();
    ASpell* clone() const;
};
